# Data Module

一个现代化的数据生成工具模块，用于机器学习实验和教学。

## 功能特性

- 🌙 **Two Moons Dataset**: 生成经典的两个月亮形状数据集
- 🔧 **简洁的API**: 简单易用的接口设计
- 🎛️ **参数可控**: 支持噪声控制、随机种子、数据混洗等
- 🔄 **可重现性**: 通过random_state确保结果可重现
- 📊 **现代化设计**: 遵循现代Python编程规范

## 安装和导入

将`data.py`文件放在你的项目目录中，然后导入：

```python
from data import make_two_moons, make_classification_data
```

## 基本用法

### 生成Two Moons数据集

```python
from data import make_two_moons
import numpy as np

# 基本用法
X, y = make_two_moons(n_samples=200, noise=0.1, random_state=42)

print(f"数据形状: {X.shape}")  # (200, 2)
print(f"标签形状: {y.shape}")  # (200,)
print(f"类别: {np.unique(y)}")  # [0 1]
```

### 参数说明

- `n_samples` (int, 默认=100): 生成的样本总数
- `noise` (float, 默认=0.1): 添加到数据的噪声标准差
- `random_state` (int/RandomState/None, 默认=None): 随机种子
- `shuffle` (bool, 默认=True): 是否混洗样本

### 使用工厂函数

```python
from data import make_classification_data

# 通过工厂函数生成
X, y = make_classification_data("moons", n_samples=300, noise=0.15)
```

## 高级用法

### 1. 控制噪声水平

```python
# 低噪声 - 更容易分类
X_easy, y_easy = make_two_moons(n_samples=200, noise=0.05, random_state=42)

# 高噪声 - 更具挑战性
X_hard, y_hard = make_two_moons(n_samples=200, noise=0.25, random_state=42)
```

### 2. 确保可重现性

```python
# 相同的random_state产生相同的结果
X1, y1 = make_two_moons(n_samples=100, random_state=123)
X2, y2 = make_two_moons(n_samples=100, random_state=123)

assert np.allclose(X1, X2)  # True
assert np.array_equal(y1, y2)  # True
```

### 3. 机器学习准备

```python
# 生成训练和测试数据
X_train, y_train = make_two_moons(n_samples=800, noise=0.1, random_state=42)
X_test, y_test = make_two_moons(n_samples=200, noise=0.1, random_state=123)

# 特征缩放
from sklearn.preprocessing import StandardScaler

scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)
X_test_scaled = scaler.transform(X_test)
```

## 数据集特性

Two Moons数据集具有以下特点：

- **非线性可分**: 线性分类器无法很好地分离两个类别
- **二分类问题**: 包含两个类别 (0和1)
- **2D特征空间**: 易于可视化和理解
- **平衡数据**: 两个类别的样本数量相等

## 可视化示例

```python
import matplotlib.pyplot as plt

# 生成数据
X, y = make_two_moons(n_samples=300, noise=0.1, random_state=42)

# 绘制
plt.figure(figsize=(10, 8))
colors = ['red', 'blue']
for i in [0, 1]:
    mask = y == i
    plt.scatter(X[mask, 0], X[mask, 1], c=colors[i], 
               label=f'Class {i}', alpha=0.7)

plt.title('Two Moons Dataset')
plt.xlabel('Feature 1')
plt.ylabel('Feature 2')
plt.legend()
plt.grid(True, alpha=0.3)
plt.show()
```

## 测试和验证

运行测试脚本验证功能：

```bash
python test_data.py
```

查看使用示例：

```bash
python examples.py
```

## 与scikit-learn对比

我们的实现与scikit-learn的`make_moons`兼容，但提供了：

- 更详细的文档和类型提示
- 更现代的API设计
- 更全面的参数验证
- 中文注释和说明

```python
# 本模块
from data import make_two_moons
X, y = make_two_moons(n_samples=100, noise=0.1, random_state=42)

# scikit-learn
from sklearn.datasets import make_moons
X_sk, y_sk = make_moons(n_samples=100, noise=0.1, random_state=42)

# 结果相似但不完全相同（由于实现细节差异）
```

## 扩展性

模块设计支持未来添加更多数据集类型：

```python
# 未来可能添加的数据集
# X, y = make_classification_data("circles", ...)  
# X, y = make_classification_data("blobs", ...)
```

## 贡献

欢迎提交Issue和Pull Request来改进这个模块！

## 许可证

MIT License
