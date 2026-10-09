from __future__ import annotations

from dataclasses import dataclass
from typing import Literal, Optional


Money = float
Discount = float


@dataclass
class PlayerConfig:
    """单个玩家配置。"""

    name: str  # "A" or "B"
    discount: Discount  # 折现因子 ∈ [0.1, 0.9]
    belief_min: Discount = 0.1
    belief_max: Discount = 0.9


@dataclass
class GameConfig:
    """单局讨价还价博弈配置。"""

    total_amount: Money = 1000.0
    max_rounds: int = 50
    # 启发式策略参数：对“对方更有耐心”的安全边际
    safety_margin: float = 0.05


@dataclass
class RoundRecord:
    """单轮出价记录。"""

    round_index: int
    proposer: str
    offer_to_A: Money
    offer_to_B: Money
    accepted_by: Optional[str] = None


@dataclass
class GameResult:
    """单局博弈结果汇总。"""

    delta_A: Discount
    delta_B: Discount
    payoff_A: Money
    payoff_B: Money
    accepted_by: Optional[str]
    rounds: int
    success: bool
    guess_A_about_B: Optional[Discount]
    guess_B_about_A: Optional[Discount]
    guess_error_A: Optional[float]
    guess_error_B: Optional[float]


PlayerName = Literal["A", "B"]

