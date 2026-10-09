from __future__ import annotations

import csv
import random
from dataclasses import asdict
from pathlib import Path

import pandas as pd

from .model import GameConfig
from .simulate import run_game
from .theory import rubinstein_equilibrium


def run_experiments(
    n_games: int,
    seed: int,
    output_dir: Path,
) -> tuple[pd.DataFrame, pd.DataFrame]:
    rng = random.Random(seed)
    output_dir.mkdir(parents=True, exist_ok=True)

    config = GameConfig()
    results = []
    for _ in range(n_games):
        res = run_game(config, rng)
        results.append(asdict(res))

    df_exp = pd.DataFrame(results)
    exp_csv = output_dir / "results_experiment.csv"
    df_exp.to_csv(exp_csv, index=False)

    # 理论基准：遍历离散折现因子组合
    theory_rows = []
    discount_values = [round(0.1 * i, 1) for i in range(1, 10)]
    for dA in discount_values:
        for dB in discount_values:
            outcome = rubinstein_equilibrium(dA, dB, config.total_amount)
            theory_rows.append(
                {
                    "delta_A": dA,
                    "delta_B": dB,
                    "share_A": outcome.share_A,
                    "share_B": outcome.share_B,
                    "payoff_A": outcome.payoff_A_first,
                    "payoff_B": outcome.payoff_B_first,
                }
            )

    df_theory = pd.DataFrame(theory_rows)
    theory_csv = output_dir / "results_theory.csv"
    df_theory.to_csv(theory_csv, index=False)

    # 简易备份（纯 CSV 写出，避免无 pandas 环境时也能阅读）
    with open(output_dir / "results_experiment_simple.csv", "w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=list(results[0].keys()))
        writer.writeheader()
        writer.writerows(results)

    return df_exp, df_theory

