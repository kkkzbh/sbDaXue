"""
机器学习实验用数据生成工具。

此模块提供了生成机器学习研究和教学中常用合成数据集的函数。
"""

import numpy as np
from typing import Tuple, Optional, Union


def make_two_moons(
    n_samples: int = 100,
    *,
    noise: float = 0.1,
    random_state: Optional[Union[int, np.random.RandomState, np.random.Generator]] = None,
    shuffle: bool = True
) -> Tuple[np.ndarray, np.ndarray]:
    """
    生成用于二分类的两个月亮形状数据集。
    
    该函数创建两个交错的半圆（月亮），形成经典的非线性可分的二分类问题。
    
    参数
    ----------
    n_samples : int, 默认=100
        生成的点的总数。将在两个月亮之间平均分配
        （每个月亮获得 n_samples // 2 个点）。
        
    noise : float, 默认=0.1
        添加到数据的高斯噪声的标准差。
        值越高，问题越困难。
        
    random_state : int、RandomState实例或None, 默认=None
        控制随机种子以确保结果可重现。
        - 如果是int：random_state被用作随机数生成器的种子
        - 如果是RandomState或Generator实例：直接使用
        - 如果是None：使用全局numpy随机状态
        
    shuffle : bool, 默认=True
        是否混洗样本。如果为False，样本按类别顺序排列
        （先第一个月亮，然后第二个月亮）。
        
    返回值
    -------
    X : 形状为 (n_samples, 2) 的ndarray
        生成的样本。每行代表2D空间中的一个点。
        
    y : 形状为 (n_samples,) 的ndarray
        类别成员的整数标签（0或1）。
        类别0对应底部月亮，类别1对应顶部月亮。
        
    示例
    --------
    >>> from data import make_two_moons
    >>> X, y = make_two_moons(n_samples=200, noise=0.15, random_state=42)
    >>> print(f"数据形状: {X.shape}, 标签形状: {y.shape}")
    数据形状: (200, 2), 标签形状: (200,)
    >>> print(f"类别: {np.unique(y)}")
    类别: [0 1]
    
    >>> # 生成噪声更少的数据，便于分类
    >>> X_easy, y_easy = make_two_moons(n_samples=150, noise=0.05, random_state=123)
    
    注意
    -----
    两个月亮数据集是测试非线性分类算法的流行合成数据集。线性分类器
    通常在此数据集上表现不佳，因此它非常适合演示更复杂模型（如神经
    网络、带非线性核的SVM或集成方法）的能力。
    
    数据集包含：
    - 底部月亮（类别0）：向上开口的半圆
    - 顶部月亮（类别1）：向下开口的半圆，位于底部月亮的上方和右侧
    """
    # 处理不同类型的random_state
    if isinstance(random_state, (int, type(None))):
        rng = np.random.RandomState(random_state)
    elif isinstance(random_state, np.random.RandomState):
        rng = random_state
    elif isinstance(random_state, np.random.Generator):
        # 支持新版numpy的Generator接口
        rng = random_state
    else:
        raise ValueError(
            f"random_state必须是int、RandomState实例、Generator实例或None。"
            f"得到了{type(random_state)}"
        )
    
    # 计算每个月亮的样本数
    n_samples_per_moon = n_samples // 2
    n_samples_moon1 = n_samples_per_moon
    n_samples_moon2 = n_samples - n_samples_per_moon  # 处理奇数情况
    
    # 生成第一个月亮（底部，类别0）
    # 从0到π的半圆
    angles1 = rng.uniform(0, np.pi, n_samples_moon1) if hasattr(rng, 'uniform') else np.random.uniform(0, np.pi, n_samples_moon1)
    X1 = np.column_stack([
        np.cos(angles1),
        np.sin(angles1)
    ])
    y1 = np.zeros(n_samples_moon1, dtype=int)
    
    # 生成第二个月亮（顶部，类别1）
    # 从π到2π的半圆，然后翻转并平移
    angles2 = rng.uniform(0, np.pi, n_samples_moon2) if hasattr(rng, 'uniform') else np.random.uniform(0, np.pi, n_samples_moon2)
    X2 = np.column_stack([
        1 - np.cos(angles2),
        1 - np.sin(angles2) - 0.5
    ])
    y2 = np.ones(n_samples_moon2, dtype=int)
    
    # 合并两个月亮
    X = np.vstack([X1, X2])
    y = np.hstack([y1, y2])
    
    # 添加噪声
    if noise > 0:
        if hasattr(rng, 'normal'):
            X += rng.normal(0, noise, X.shape)
        else:
            X += np.random.normal(0, noise, X.shape)
    
    # 如果需要则混洗数据
    if shuffle:
        if hasattr(rng, 'permutation'):
            indices = rng.permutation(n_samples)
        else:
            indices = np.random.permutation(n_samples)
        X = X[indices]
        y = y[indices]
    
    return X, y


def make_classification_data(
    dataset_type: str = "moons",
    **kwargs
) -> Tuple[np.ndarray, np.ndarray]:
    """
    工厂函数，用于生成各种类型的分类数据集。
    
    参数
    ----------
    dataset_type : str, 默认="moons"
        要生成的数据集类型。目前支持：
        - "moons": 两个交错的半圆
        
    **kwargs
        传递给特定数据集生成器的额外关键字参数。
        
    返回值
    -------
    X : ndarray
        生成的样本。
        
    y : ndarray  
        目标标签。
        
    示例
    --------
    >>> X, y = make_classification_data("moons", n_samples=100, noise=0.1)
    """
    if dataset_type == "moons":
        return make_two_moons(**kwargs)
    else:
        raise ValueError(f"未知的数据集类型: {dataset_type}")


if __name__ == "__main__":
    # 演示使用方法
    import matplotlib.pyplot as plt
    
    # 生成示例数据
    X, y = make_two_moons(n_samples=300, noise=0.1, random_state=42)
    
    # 创建简单的可视化
    plt.figure(figsize=(10, 8))
    
    # 用不同颜色绘制两个类别
    colors = ['red', 'blue']
    for i, color in enumerate(colors):
        mask = y == i
        plt.scatter(X[mask, 0], X[mask, 1], c=color, label=f'类别 {i}', 
                   alpha=0.7, s=50, edgecolors='black', linewidth=0.5)
    
    plt.title('两个月亮数据集', fontsize=16, fontweight='bold')
    plt.xlabel('特征 1', fontsize=12)
    plt.ylabel('特征 2', fontsize=12)
    plt.legend(fontsize=12)
    plt.grid(True, alpha=0.3)
    plt.axis('equal')
    
    # 添加一些统计信息
    plt.figtext(0.02, 0.02, f'样本数: {len(X)}, 噪声: 0.1', 
                fontsize=10, style='italic')
    
    plt.tight_layout()
    plt.show()
    
    print(f"生成了 {len(X)} 个样本")
    print(f"数据形状: {X.shape}")
    print(f"标签形状: {y.shape}")
    print(f"类别分布: {np.bincount(y)}")
    print(f"数据范围 - X: [{X[:, 0].min():.3f}, {X[:, 0].max():.3f}], "
          f"Y: [{X[:, 1].min():.3f}, {X[:, 1].max():.3f}]")
