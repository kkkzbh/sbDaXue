from __future__ import annotations

from dataclasses import dataclass

from .model import Discount, GameConfig, Money, PlayerConfig, PlayerName


@dataclass
class HeuristicBelief:
    """
    简单区间型信念：认为对方折现因子在 [low, high] 内均匀分布。
    我们用区间中心作为“当前估计”，并在博弈过程中根据对方报价收缩区间。
    """

    low: Discount
    high: Discount

    def point_estimate(self) -> Discount:
        return 0.5 * (self.low + self.high)


def initial_belief(player: PlayerConfig) -> HeuristicBelief:
    return HeuristicBelief(low=player.belief_min, high=player.belief_max)


def propose_offer(
    proposer: PlayerConfig,
    opponent: PlayerConfig,
    belief_about_opponent: HeuristicBelief,
    config: GameConfig,
    round_index: int,
) -> tuple[Money, Money]:
    """
    启发式出价：
    - 先根据理论 Rubinstein 模型（在对方折现因子估计值下）计算提议者在 t=0 时的“理想份额”
    - 认为对方可能更有耐心一些，因此在估计值上加一个 safety_margin
    - 根据轮次折现，将当前时点的金额进行调整（简化：仍按总额分配）
    """
    from .theory import rubinstein_equilibrium

    total = config.total_amount
    est_opponent_delta = min(
        max(belief_about_opponent.point_estimate() + config.safety_margin, 0.01), 0.99
    )

    # 在 Rubinstein 模型中，“先出价者”获得 share_A 这一份额。
    # 因此无论是 A 还是 B，只要当前是提议方，都将其视为理论模型中的先手。
    delta_self = proposer.discount
    delta_opp = est_opponent_delta
    outcome = rubinstein_equilibrium(delta_self, delta_opp, total)
    share_self = outcome.share_A

    offer_self = max(0.0, min(total, share_self * total))
    offer_opp = total - offer_self

    if proposer.name == "A":
        return offer_self, offer_opp
    return offer_opp, offer_self


def decide_accept(
    responder: PlayerConfig,
    opponent: PlayerConfig,
    belief_about_opponent: HeuristicBelief,
    config: GameConfig,
    round_index: int,
    offer_to_responder: Money,
) -> bool:
    """
    接受策略（简化版本）：
    - 将对方视为“最不耐心”的可能值（belief.low），据此计算如果拒绝，再下一轮自己预期能拿到的份额。
    - 如果当前报价 ≥ 该预期值（折现后），则接受。
    """
    from .theory import rubinstein_equilibrium

    total = config.total_amount
    # 对对方“偏悲观”：假设对方折现因子是区间下界 -> 对自己不利
    pessimistic_delta_opp = max(belief_about_opponent.low - config.safety_margin, 0.01)

    if responder.name == "A":
        delta_self = responder.discount
        delta_opp = pessimistic_delta_opp
        outcome = rubinstein_equilibrium(delta_opp, delta_self, total)
        expected_future_share = outcome.share_B
    else:
        delta_self = responder.discount
        delta_opp = pessimistic_delta_opp
        outcome = rubinstein_equilibrium(delta_opp, delta_self, total)
        expected_future_share = outcome.share_B

    expected_future_amount = expected_future_share * total * (delta_self ** 1)

    return offer_to_responder >= expected_future_amount


def update_belief_after_reject(
    belief: HeuristicBelief,
    player_name: PlayerName,
    total_amount: Money,
    offer_to_opponent: Money,
) -> HeuristicBelief:
    """
    非常粗糙的启发式信念更新：
    - 如果对方拒绝了“给他更少”的出价，则认为对方可能更有耐心 -> 提高 low
    - 否则略微降低 high
    更新幅度按对方被提供的份额偏离 0.5 的程度来调整。
    """
    offered_share = offer_to_opponent / total_amount
    # 相对于 0.5 的偏离程度
    deviation = offered_share - 0.5
    step = 0.05 * abs(deviation)

    if deviation < 0:
        # 我给对方偏少，对方还拒绝 -> 认为对方很有耐心
        new_low = min(0.99, belief.low + step)
        return HeuristicBelief(low=new_low, high=belief.high)
    else:
        # 我已经给对方偏多，对方还拒绝 -> 认为对方也许没那么有耐心
        new_high = max(0.01, belief.high - step)
        if new_high < belief.low:
            new_high = belief.low
        return HeuristicBelief(low=belief.low, high=new_high)
