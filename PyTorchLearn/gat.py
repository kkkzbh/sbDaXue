

import torch
import torch.nn.functional as F
from torch_geometric.datasets import Planetoid
from torch_geometric.nn import GCNConv, GATConv
import random

# ========== 可重复性 ==========
def set_seed(seed=42):
    random.seed(seed)
    torch.manual_seed(seed)
    torch.cuda.manual_seed_all(seed)
set_seed(42)

# ========== 数据 ==========
dataset = Planetoid(root='data/Cora', name='Cora')
data = dataset[0]

device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
data = data.to(device)

print("节点数量:", data.num_nodes)
print("边数量:", data.num_edges)
print("特征维度:", data.num_node_features)
print("类别数量:", dataset.num_classes)
print("用CUDA:", torch.cuda.is_available())

# ========== 模型 ==========
class GCN(torch.nn.Module):
    def __init__(self, in_channels, hidden_channels, out_channels, dropout=0.5):
        super().__init__()
        self.conv1 = GCNConv(in_channels, hidden_channels)
        self.conv2 = GCNConv(hidden_channels, out_channels)
        self.dropout = dropout

    def forward(self, x, edge_index):
        x = self.conv1(x, edge_index)
        x = F.relu(x)
        x = F.dropout(x, p=self.dropout, training=self.training)
        x = self.conv2(x, edge_index)
        return x

class GAT(torch.nn.Module):
    """
    按论文设置：
      - 1层：8个头，每头隐藏维度=8，concat -> 输出 8*8 = 64 维
      - 2层：1个头到 num_classes，concat=False（做平均/不拼接）
      - 特征/注意力 Dropout 都设为 0.6
      - LeakyReLU slope=0.2（GATConv 默认 negative_slope=0.2）
    """
    def __init__(self, in_channels, hidden_channels, out_channels,
                 heads=8, feat_dropout=0.6, attn_dropout=0.6):
        super().__init__()
        self.gat1 = GATConv(
            in_channels,
            hidden_channels,
            heads=heads,
            dropout=attn_dropout,   # 注意力权重的dropout
            concat=True             # 拼接多头
        )
        self.gat2 = GATConv(
            hidden_channels * heads,
            out_channels,
            heads=1,
            dropout=attn_dropout,
            concat=False            # 最后一层不拼接
        )
        self.feat_dropout = feat_dropout

    def forward(self, x, edge_index):
        x = F.dropout(x, p=self.feat_dropout, training=self.training)
        x = self.gat1(x, edge_index)
        x = F.elu(x)
        x = F.dropout(x, p=self.feat_dropout, training=self.training)
        x = self.gat2(x, edge_index)
        return x

# ========== 训练/评估 ==========
def train_one_model(model, optimizer, data, epochs=200, tag="model"):
    model = model.to(device)
    best_val = 0.0
    best_test_at_val = 0.0

    for epoch in range(1, epochs + 1):
        model.train()
        optimizer.zero_grad()
        out = model(data.x, data.edge_index)
        loss = F.cross_entropy(out[data.train_mask], data.y[data.train_mask])
        loss.backward()
        optimizer.step()

        # eval
        model.eval()
        with torch.no_grad():
            logits = model(data.x, data.edge_index)
            pred = logits.argmax(dim=1)
            def acc(mask):
                return (pred[mask] == data.y[mask]).float().mean().item()
            train_acc = acc(data.train_mask)
            val_acc   = acc(data.val_mask)
            test_acc  = acc(data.test_mask)

        if val_acc > best_val:
            best_val = val_acc
            best_test_at_val = test_acc

        if epoch % 20 == 0:
            print(f"[{tag}] Epoch {epoch:03d} | "
                  f"Loss {loss.item():.4f} | "
                  f"Train {train_acc:.4f} | Val {val_acc:.4f} | Test {test_acc:.4f}")

    print(f"[{tag}] Done. Best Val={best_val:.4f}, Test@BestVal={best_test_at_val:.4f}\n")
    return best_val, best_test_at_val

# ========== 跑 GCN ==========
gcn = GCN(
    in_channels=dataset.num_node_features,
    hidden_channels=16,
    out_channels=dataset.num_classes,
    dropout=0.5
)
opt_gcn = torch.optim.Adam(gcn.parameters(), lr=0.01, weight_decay=5e-4)
print("=== Training GCN ===")
train_one_model(gcn, opt_gcn, data, epochs=200, tag="GCN")

# ========== 跑 GAT ==========
gat = GAT(
    in_channels=dataset.num_node_features,
    hidden_channels=8,       # 每个头8维，8头 -> 64维
    out_channels=dataset.num_classes,
    heads=8,
    feat_dropout=0.6,
    attn_dropout=0.6
)
# 参考论文设置：lr=0.005, weight_decay=0.0005
opt_gat = torch.optim.Adam(gat.parameters(), lr=0.005, weight_decay=5e-4)
print("=== Training GAT ===")
train_one_model(gat, opt_gat, data, epochs=200, tag="GAT")