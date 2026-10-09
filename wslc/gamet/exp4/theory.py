from __future__ import annotations

from dataclasses import dataclass

from .model import Discount, Money


@dataclass
class RubinsteinOutcome:
    """完全信息 Rubinstein 模型的均衡结果（无限期、交替出价）。"""

    delta_A: Discount
    delta_B: Discount
    share_A: float  # A 在 t=0 时点的金额份额（相对于总额 1）
    share_B: float

    payoff_A_first: Money
    payoff_B_first: Money


def rubinstein_equilibrium(
    delta_A: Discount,
    delta_B: Discount,
    total_amount: Money,
) -> RubinsteinOutcome:
    """
    Rubinstein (1982) 完全信息交替出价模型的标准解：
    - A 先出价
    - 折现因子为 δ_A, δ_B
    - 标准结果：A 在 t=0 的分配份额为 (1 - δ_B) / (1 - δ_A * δ_B)，
      B 的份额为 (1 - δ_A) / (1 - δ_A * δ_B)。
    """
    if not (0.0 < delta_A < 1.0 and 0.0 < delta_B < 1.0):
        raise ValueError("discount factors must be in (0, 1)")

    denom = 1.0 - delta_A * delta_B
    if denom <= 0.0:
        raise ValueError("invalid discount factors: 1 - delta_A * delta_B <= 0")

    share_A = (1.0 - delta_B) / denom
    share_B = 1.0 - share_A

    # 数值安全处理，避免极端情况下越界
    share_A = max(0.0, min(1.0, share_A))
    share_B = max(0.0, min(1.0, share_B))

    payoff_A_first = share_A * total_amount
    payoff_B_first = share_B * total_amount

    return RubinsteinOutcome(
        delta_A=delta_A,
        delta_B=delta_B,
        share_A=share_A,
        share_B=share_B,
        payoff_A_first=payoff_A_first,
        payoff_B_first=payoff_B_first,
    )
