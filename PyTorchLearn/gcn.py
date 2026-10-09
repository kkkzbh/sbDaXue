

import torch
import torch.nn.functional as F
from torch_geometric.datasets import Planetoid
from torch_geometric.nn import GCNConv

dataset = Planetoid(root = 'data/Cora',name = 'Cora')
data = dataset[0]

print("节点数量:", data.num_nodes)
print("边数量:", data.num_edges)
print("特征维度:", data.num_node_features)
print("类别数量:", dataset.num_classes)

class gcn(torch.nn.Module):
    def __init__(self,in_channels,hidden_channels,out_channels):
        super(gcn,self).__init__()
        self.conv1 = GCNConv(in_channels,hidden_channels)
        self.conv2 = GCNConv(hidden_channels,out_channels)

    def forward(self,x,edge_index):
        x = self.conv1(x,edge_index)
        x = F.relu(x)

        x = self.conv2(x,edge_index)
        return x

model = gcn (
    in_channels = dataset.num_node_features,
    hidden_channels = 16,
    out_channels = dataset.num_classes
)

optimizer = torch.optim.Adam(model.parameters(), lr = 0.01,weight_decay = 5e-4)
criterion = torch.nn.CrossEntropyLoss()

def train():
    model.train()
    optimizer.zero_grad()
    out = model(data.x, data.edge_index)
    loss = criterion(out[data.train_mask], data.y[data.train_mask])
    loss.backward()
    optimizer.step()
    return loss.item()

def test():
    model.eval()
    out = model(data.x,data.edge_index)
    pred = out.argmax(dim = 1)

    accs = []
    for mask in [data.train_mask,data.val_mask,data.test_mask]:
        correct = pred[mask].eq(data.y[mask]).sum().item()
        acc = correct / mask.sum().item()
        accs.append(acc)
    return accs

for epoch in range(1,201):
    loss = train()
    train_acc,val_acc,test_acc = test()
    if epoch % 20 == 0:
        print(f'Epoch: {epoch:03d}, Loss: {loss:.4f}, '
              f'Train Acc: {train_acc:.4f}, Val Acc: {val_acc:.4f}, Test Acc: {test_acc:.4f}')

train_acc,val_acc,test_acc = test()
print(f"最终测试准确率 :{test_acc:.4f}")