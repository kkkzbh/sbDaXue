#!/usr/bin/env python3
"""正规式博弈收益矩阵演示脚本。"""

from __future__ import annotations

import argparse
import re
from pathlib import Path
from typing import Any, Iterable, Tuple

import matplotlib.pyplot as plt

from normal_form import load_normal_form_game, visualise_payoff_matrix

MATRIX_INPUT_DIR = Path(__file__).resolve().parent / "matrix_input"
MATRIX_OUTPUT_DIR = Path(__file__).resolve().parent / "matrix_output"


def parse_args(argv: list[str] | None = None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="从 JSON 描述载入正规式博弈，生成策略组合并可视化收益矩阵。"
    )
    parser.add_argument(
        "input",
        nargs="?",
        default=None,
        help="输入 JSON，可提供完整路径，也可以只给位于 matrix_input/ 下的文件名，或直接粘贴 JSON。",
    )
    parser.add_argument(
        "--output",
        type=Path,
        help="可选：输出图像路径（默认写入 matrix_output/）。",
    )
    parser.add_argument(
        "--show",
        action="store_true",
        help="可选：使用交互式窗口显示绘图。",
    )
    return parser.parse_args(argv)


def resolve_source(argument: str | Path) -> Tuple[Any, Path | None]:
    if isinstance(argument, Path):
        candidate_path = argument
        if candidate_path.exists():
            return candidate_path, candidate_path
        text = candidate_path.name
    else:
        text = argument.strip()
        candidate_path = Path(text)
        if candidate_path.exists():
            return candidate_path, candidate_path

    within_input = MATRIX_INPUT_DIR / text
    if within_input.exists():
        return within_input, within_input

    if within_input.suffix != ".json":
        json_candidate = within_input.with_suffix(".json")
        if json_candidate.exists():
            return json_candidate, json_candidate

    if isinstance(argument, str) and (text.startswith("{") or text.startswith("[")):
        return text, None

    msg = (
        f"未找到输入 '{argument}'。请放置于 {MATRIX_INPUT_DIR} 中，"
        "或提供完整路径 / 直接粘贴 JSON。"
    )
    raise FileNotFoundError(msg)


def _safe_name(name: str) -> str:
    sanitized = re.sub(r"[\\/:*?\"<>|]+", "_", name.strip())
    return sanitized or "matrix"


def _iter_default_inputs() -> Iterable[Path]:
    MATRIX_INPUT_DIR.mkdir(parents=True, exist_ok=True)
    return sorted(MATRIX_INPUT_DIR.glob("*.json"))


def _ensure_output_dir() -> None:
    MATRIX_OUTPUT_DIR.mkdir(parents=True, exist_ok=True)


def _process_single(argument: str | Path, *, explicit_output: Path | None, show: bool) -> int:
    try:
        source, source_path = resolve_source(argument)
    except FileNotFoundError as exc:
        print(exc)
        return 1

    game = load_normal_form_game(source)

    print(f"已载入博弈：{game.title}")
    print("参与者策略集：")
    for player, strategies in game.strategy_sets().items():
        print(f"  {player}: {', '.join(strategies)}")

    profiles = list(game.iter_strategy_profiles())
    equilibria = game.pure_nash_equilibria()
    equilibrium_indices = {equilibrium.indices for equilibrium in equilibria}

    print("全部策略组合：")
    for ordinal, (index_tuple, payoff_vector) in enumerate(profiles, start=1):
        strategy_desc = "; ".join(
            f"{player.name}={player.strategies[strategy_index].label}"
            for player, strategy_index in zip(game.players, index_tuple)
        )
        payoff_desc = ", ".join(
            f"{player.name}: {payoff_vector[player_idx]:g}"
            for player_idx, player in enumerate(game.players)
        )
        equilibrium_flag = "是" if index_tuple in equilibrium_indices else "否"
        print(
            f"  [{ordinal}] {strategy_desc} | 收益=({payoff_desc}) | 均衡：{equilibrium_flag}"
        )

    if equilibria:
        print("纯策略纳什均衡：")
        for equilibrium in equilibria:
            profile_desc = "; ".join(
                f"{player} → {strategy}"
                for player, strategy in equilibrium.strategies.items()
            )
            payoff_desc = ", ".join(
                f"{player}: {value:g}"
                for player, value in equilibrium.payoffs.items()
            )
            print(f"  组合=({profile_desc}) | 收益=({payoff_desc})")
    else:
        print("未发现纯策略纳什均衡。")

    figure = visualise_payoff_matrix(game)

    if explicit_output:
        output_path = explicit_output
        if not output_path.is_absolute():
            output_path = MATRIX_OUTPUT_DIR / output_path
    else:
        if source_path is not None:
            base_name = source_path.stem
        else:
            base_name = _safe_name(game.title)
        output_path = MATRIX_OUTPUT_DIR / f"{base_name}.png"

    _ensure_output_dir()
    output_path.parent.mkdir(parents=True, exist_ok=True)
    figure.savefig(output_path, dpi=220, bbox_inches="tight")
    print(f"收益矩阵已写出至 {output_path}")

    if show:
        plt.show()
    else:
        plt.close(figure)

    return 0


def main(argv: list[str] | None = None) -> int:
    args = parse_args(argv)

    if args.input is None:
        inputs = list(_iter_default_inputs())
        if not inputs:
            print(f"目录 {MATRIX_INPUT_DIR} 中未找到任何 JSON 输入文件。")
            print("请将博弈描述放入该目录后重新运行，或手动指定输入。")
            return 1

        if args.show and len(inputs) > 1:
            print("提示：批量处理时忽略 --show 参数。")

        exit_code = 0
        for path in inputs:
            print("-" * 60)
            result = _process_single(path, explicit_output=None, show=args.show and len(inputs) == 1)
            exit_code = result or exit_code
        return exit_code

    return _process_single(args.input, explicit_output=args.output, show=args.show)


if __name__ == "__main__":  # pragma: no cover - manual entry point
    raise SystemExit(main())
