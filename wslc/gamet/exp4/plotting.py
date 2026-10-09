from __future__ import annotations

from pathlib import Path

import matplotlib.pyplot as plt
from matplotlib import font_manager as fm
import pandas as pd


def _ensure_dir(path: Path) -> None:
    path.mkdir(parents=True, exist_ok=True)


def _setup_chinese_fonts() -> None:
    """
    参考 exp2 中的字体设置：优先使用文泉驿字体，避免中文缺字。
    """
    font_path = Path("/usr/share/fonts/truetype/wqy/wqy-microhei.ttc")
    if not font_path.exists():
        return

    fm.fontManager.addfont(str(font_path))
    plt.rcParams.update(
        {
            "font.family": "sans-serif",
            "font.sans-serif": ["WenQuanYi Micro Hei"],
            "axes.unicode_minus": False,
        }
    )


def plot_from_csv(exp_csv: Path, theory_csv: Path, output_dir: Path) -> None:
    _ensure_dir(output_dir)
    _setup_chinese_fonts()
    df_exp = pd.read_csv(exp_csv)
    df_theory = pd.read_csv(theory_csv)

    # 折现因子 vs 平均收益
    grouped_A = df_exp.groupby("delta_A")["payoff_A"].mean()
    grouped_B = df_exp.groupby("delta_B")["payoff_B"].mean()

    plt.figure()
    grouped_A.sort_index().plot(marker="o", label="实验：A 平均收益")
    plt.xlabel("delta_A")
    plt.ylabel("A payoff")
    plt.title("折现因子与 A 的平均收益")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.savefig(output_dir / "payoff_A_vs_delta_A.png")
    plt.close()

    plt.figure()
    grouped_B.sort_index().plot(marker="o", label="实验：B 平均收益", color="orange")
    plt.xlabel("delta_B")
    plt.ylabel("B payoff")
    plt.title("折现因子与 B 的平均收益")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.savefig(output_dir / "payoff_B_vs_delta_B.png")
    plt.close()

    # 折现因子 vs 平均轮数
    grouped_rounds_A = df_exp.groupby("delta_A")["rounds"].mean()

    plt.figure()
    grouped_rounds_A.sort_index().plot(marker="o", label="实验：平均轮数")
    plt.xlabel("delta_A")
    plt.ylabel("平均轮数")
    plt.title("折现因子与博弈轮数（按 A 折现因子分组）")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.savefig(output_dir / "rounds_vs_delta_A.png")
    plt.close()

    # 猜测误差
    grouped_guess_A = df_exp.groupby("delta_A")["guess_error_A"].mean()
    plt.figure()
    grouped_guess_A.sort_index().plot(marker="o", label="A 对 B 折现因子猜测误差")
    plt.xlabel("delta_A")
    plt.ylabel("平均误差")
    plt.title("A 折现因子与其对 B 的猜测误差")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.savefig(output_dir / "guess_error_A_vs_delta_A.png")
    plt.close()

    # 理论 vs 实验（按 delta_A 聚合）
    theory_A = df_theory.groupby("delta_A")["payoff_A"].mean()
    plt.figure()
    theory_A.sort_index().plot(marker="o", label="理论：A 收益", color="green")
    grouped_A.sort_index().plot(marker="x", label="实验：A 平均收益", color="red")
    plt.xlabel("delta_A")
    plt.ylabel("A payoff")
    plt.title("理论 vs 实验：折现因子对 A 收益的影响")
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.savefig(output_dir / "theory_vs_experiment_A.png")
    plt.close()
