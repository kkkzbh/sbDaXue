

import torch
import torch.nn as nn
import torch.optim as optim
import matplotlib.pyplot as plt
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
from data import make_two_moons
import mglearn

features,labels = make_two_moons(n_samples = 200, noise = 0.15, random_state = 0)

X_train,X_test,y_train,y_test = train_test_split (
    features,
    labels,
    test_size = 0.2,
    random_state=0
)

scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

X_train = torch.tensor(X_train, dtype=torch.float32)
X_test = torch.tensor(X_test, dtype=torch.float32)
y_train = torch.tensor(y_train, dtype=torch.long)
y_test = torch.tensor(y_test, dtype=torch.long)

class mlp(nn.Module):
    def __init__(self,input_dim):
        super().__init__()
        self.layers = nn.Sequential (
            nn.Linear(input_dim,10),
            nn.Tanh(),
            nn.Linear(10,10),
            nn.Tanh(),
            nn.Linear(10,2),
        )

    def forward(self,x):
        return self.layers(x)
    
    def predict_proba(self, x):
        """为 mglearn 兼容性添加 predict_proba 方法"""
        if not isinstance(x, torch.Tensor):
            x = torch.tensor(x, dtype=torch.float32)
        self.eval()
        with torch.no_grad():
            outputs = self.forward(x)
            probabilities = torch.softmax(outputs, dim=1)
            return probabilities.numpy()
    
    def decision_function(self, x):
        """为 mglearn 兼容性添加 decision_function 方法"""
        if not isinstance(x, torch.Tensor):
            x = torch.tensor(x, dtype=torch.float32)
        self.eval()
        with torch.no_grad():
            outputs = self.forward(x)
            # 对于二分类，返回第二类的 logits
            return outputs[:, 1].numpy()

model = mlp(input_dim = 2)

criterion = nn.CrossEntropyLoss()
optimizer = optim.Adam(model.parameters(), lr = 0.01)

num_epochs = 1000
model.train()
for epoch in range(num_epochs):
    optimizer.zero_grad()

    outputs = model(X_train)
    loss = criterion(outputs, y_train)
    loss.backward()
    optimizer.step()

    if (epoch + 1) % 100 == 0:
        print(f'Epoch [{epoch + 1}/{num_epochs}], Loss: {loss.item():.4f}')

model.eval()

with torch.no_grad():
    outputs = model(X_test)
    preds = outputs.argmax(dim = 1)
    accuracy = (preds == y_test).float().mean()
    print(f'Accuracy: {accuracy:.4f}')

mglearn.plots.plot_2d_separator(model,X_train.numpy(),fill = True,alpha = .3)
mglearn.discrete_scatter(X_train[:,0].numpy(),X_train[:,1].numpy(),y_train.numpy())
plt.xlabel('Feature 0')
plt.ylabel('Feature 1')

plt.show()