from __future__ import annotations

import random

from exp4.model import GameConfig
from exp4.simulate import run_game


def test_single_game_runs_and_terminates():
    """基本回归测试：单局博弈应在有限轮数内结束，不抛异常。"""
    cfg = GameConfig(max_rounds=30)
    rng = random.Random(123)
    res = run_game(cfg, rng)

    assert res.rounds <= cfg.max_rounds
    assert res.payoff_A >= 0.0
    assert res.payoff_B >= 0.0


def test_multiple_games_show_reasonable_success_rate():
    """跑多局，至少有部分博弈能达成成交。"""
    cfg = GameConfig(max_rounds=40)
    rng = random.Random(456)

    successes = 0
    for _ in range(50):
        res = run_game(cfg, rng)
        if res.success:
            successes += 1

    assert successes > 0

