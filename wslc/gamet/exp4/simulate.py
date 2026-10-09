from __future__ import annotations

import random
from typing import Tuple

from .model import GameConfig, GameResult, PlayerConfig, RoundRecord
from .strategy import (
    HeuristicBelief,
    decide_accept,
    initial_belief,
    propose_offer,
    update_belief_after_reject,
)


def _random_discount(rng: random.Random) -> float:
    """在 {0.1, 0.2, ..., 0.9} 中均匀抽取一个折现因子（使用局部 RNG，避免污染全局）。"""
    choices = [round(0.1 * i, 1) for i in range(1, 10)]
    return rng.choice(choices)


def _init_players(rng: random.Random) -> Tuple[PlayerConfig, PlayerConfig]:
    delta_A = _random_discount(rng)
    delta_B = _random_discount(rng)
    player_A = PlayerConfig(name="A", discount=delta_A)
    player_B = PlayerConfig(name="B", discount=delta_B)
    return player_A, player_B


def run_game(config: GameConfig, rng: random.Random) -> GameResult:
    # 所有随机性都通过传入的 rng 控制，避免复用全局 random 状态导致每局完全相同。
    A, B = _init_players(rng)
    belief_A: HeuristicBelief = initial_belief(A)
    belief_B: HeuristicBelief = initial_belief(B)

    records: list[RoundRecord] = []

    proposer = "A"
    success = False
    accepted_by = None

    for t in range(config.max_rounds):
        if proposer == "A":
            proposer_cfg, responder_cfg = A, B
            belief_proposer, belief_responder = belief_A, belief_B
        else:
            proposer_cfg, responder_cfg = B, A
            belief_proposer, belief_responder = belief_B, belief_A

        offer_to_A, offer_to_B = propose_offer(
            proposer_cfg,
            responder_cfg,
            belief_proposer,
            config,
            round_index=t,
        )

        offer_to_responder = offer_to_B if responder_cfg.name == "B" else offer_to_A

        accept = decide_accept(
            responder=responder_cfg,
            opponent=proposer_cfg,
            belief_about_opponent=belief_responder,
            config=config,
            round_index=t,
            offer_to_responder=offer_to_responder,
        )

        record = RoundRecord(
            round_index=t,
            proposer=proposer_cfg.name,
            offer_to_A=offer_to_A,
            offer_to_B=offer_to_B,
            accepted_by=responder_cfg.name if accept else None,
        )
        records.append(record)

        if accept:
            success = True
            accepted_by = responder_cfg.name
            break

        # 否则拒绝，出价者更新对对方的信念
        if proposer_cfg.name == "A":
            belief_A = update_belief_after_reject(
                belief_A,
                player_name="A",
                total_amount=config.total_amount,
                offer_to_opponent=offer_to_B,
            )
        else:
            belief_B = update_belief_after_reject(
                belief_B,
                player_name="B",
                total_amount=config.total_amount,
                offer_to_opponent=offer_to_A,
            )

        proposer = "B" if proposer == "A" else "A"

    # 统计结果
    if success and records:
        last = records[-1]
        payoff_A = last.offer_to_A * (A.discount ** last.round_index)
        payoff_B = last.offer_to_B * (B.discount ** last.round_index)
        rounds = last.round_index + 1
    else:
        payoff_A = 0.0
        payoff_B = 0.0
        rounds = config.max_rounds

    guess_A = belief_A.point_estimate()
    guess_B = belief_B.point_estimate()

    return GameResult(
        delta_A=A.discount,
        delta_B=B.discount,
        payoff_A=payoff_A,
        payoff_B=payoff_B,
        accepted_by=accepted_by,
        rounds=rounds,
        success=success,
        guess_A_about_B=guess_A,
        guess_B_about_A=guess_B,
        guess_error_A=abs(guess_A - B.discount),
        guess_error_B=abs(guess_B - A.discount),
    )
