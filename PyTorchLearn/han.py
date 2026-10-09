

import torch
import torch.nn.functional as F
from torch_geometric.nn import GATConv, HeteroConv
from torch_geometric.datasets import OGB_MAG
from torch_geometric.loader import NeighborLoader

# -----------------------------
# 1. 准备异构图数据集
# -----------------------------
dataset = OGB_MAG(root='data/OGB_MAG')
data = dataset[0]  # 异构图对象
# 选择论文节点作为分类目标
target_node_type = 'paper'
num_classes = dataset.num_classes[target_node_type]

# -----------------------------
# 2. HAN 模型定义
# -----------------------------
class HAN(torch.nn.Module):
    def __init__(self, in_channels_dict, hidden_channels, out_channels,
                 metadata, heads=2, feat_dropout=0.5, attn_dropout=0.5):
        super().__init__()
        self.feat_dropout = feat_dropout

        # 节点级 GAT 聚合
        self.hetero_conv1 = HeteroConv({
            edge_type: GATConv(in_channels_dict[edge_type[0]],
                               hidden_channels,
                               heads=heads,
                               dropout=attn_dropout,
                               concat=True)
            for edge_type in metadata[1]  # metadata[1] 是边类型列表
        }, aggr='sum')  # 节点级聚合用 sum

        # 第二层输出最终表示
        self.hetero_conv2 = HeteroConv({
            edge_type: GATConv(hidden_channels * heads,
                               out_channels,
                               heads=1,
                               dropout=attn_dropout,
                               concat=False)
            for edge_type in metadata[1]
        }, aggr='sum')

    def forward(self, x_dict, edge_index_dict):
        # 输入特征做 dropout
        x_dict = {k: F.dropout(x, p=self.feat_dropout, training=self.training)
                  for k, x in x_dict.items()}

        # 节点级注意力 + 汇总
        x_dict = self.hetero_conv1(x_dict, edge_index_dict)
        x_dict = {k: F.elu(x) for k, x in x_dict.items()}

        # 第二层
        x_dict = self.hetero_conv2(x_dict, edge_index_dict)
        return x_dict

# -----------------------------
# 3. 创建模型
# -----------------------------
in_channels_dict = {k: v.size(1) for k, v in data.x_dict.items()}
model = HAN(in_channels_dict, hidden_channels=64, out_channels=num_classes,
            metadata=data.metadata(), heads=2)

optimizer = torch.optim.Adam(model.parameters(), lr=0.005, weight_decay=5e-4)
criterion = torch.nn.CrossEntropyLoss()

# -----------------------------
# 4. 训练函数
# -----------------------------
def train():
    model.train()
    optimizer.zero_grad()
    out_dict = model(data.x_dict, data.edge_index_dict)
    out = out_dict[target_node_type]
    loss = criterion(out[data.train_mask[target_node_type]],
                     data.y_dict[target_node_type][data.train_mask[target_node_type]])
    loss.backward()
    optimizer.step()
    return loss.item()

# -----------------------------
# 5. 测试函数
# -----------------------------
@torch.no_grad()
def test():
    model.eval()
    out_dict = model(data.x_dict, data.edge_index_dict)
    out = out_dict[target_node_type].argmax(dim=1)
    accs = []
    for split in ['train', 'valid', 'test']:
        mask = data[f'{split}_mask'][target_node_type]
        correct = out[mask].eq(data.y_dict[target_node_type][mask]).sum().item()
        accs.append(correct / mask.sum().item())
    return accs

# -----------------------------
# 6. 训练主循环
# -----------------------------
for epoch in range(1, 201):
    loss = train()
    train_acc, val_acc, test_acc = test()
    if epoch % 20 == 0:
        print(f"Epoch {epoch:03d}, Loss: {loss:.4f}, "
              f"Train: {train_acc:.4f}, Val: {val_acc:.4f}, Test: {test_acc:.4f}")
