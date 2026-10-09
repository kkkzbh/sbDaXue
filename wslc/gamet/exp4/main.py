from __future__ import annotations

import argparse
from pathlib import Path

from .experiment import run_experiments
from .plotting import plot_from_csv


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="实验四：讨价还价博弈模型的设计（纯 Python）",
    )
    parser.add_argument(
        "--games",
        type=int,
        default=5000,
        help="模拟博弈局数，越大结果越平滑（默认：5000）",
    )
    parser.add_argument(
        "--seed",
        type=int,
        default=42,
        help="随机种子（默认：42）",
    )
    parser.add_argument(
        "--output",
        type=str,
        default="exp4/output",
        help="结果输出目录（默认：exp4/output）",
    )
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    output_dir = Path(args.output)
    df_exp, df_theory = run_experiments(
        n_games=args.games,
        seed=args.seed,
        output_dir=output_dir,
    )

    print(f"实验完成：共模拟 {len(df_exp)} 局，输出目录：{output_dir}")
    print("部分统计：")
    print(df_exp[["delta_A", "delta_B", "payoff_A", "payoff_B", "rounds"]].head())

    exp_csv = output_dir / "results_experiment.csv"
    theory_csv = output_dir / "results_theory.csv"

    plot_from_csv(exp_csv, theory_csv, output_dir=output_dir)
    print("图表已生成，可直接用于实验报告截图：")
    for name in sorted(p.name for p in output_dir.glob("*.png")):
        print(" -", name)


if __name__ == "__main__":
    main()

