"""博弈矩阵解析与可视化模块，配合实验二使用。

该模块聚焦策略式（正规式）博弈：支持从 JSON 输入描述读取博弈要素，
生成策略组合，辨识纯策略纳什均衡，并用 Matplotlib 绘制收益矩阵。
"""

from __future__ import annotations

import json
from dataclasses import dataclass
from itertools import product
from pathlib import Path
from typing import Any, Iterable, Mapping, Sequence

import matplotlib.pyplot as plt
from matplotlib import font_manager as fm


def _pick(mapping: Mapping[str, Any], *candidates: str, default: Any = None) -> Any:
    """按照候选键顺序返回第一个存在的取值。"""

    for key in candidates:
        if key in mapping:
            return mapping[key]
    return default


def _setup_chinese_fonts() -> None:
    """尝试启用文泉驿等中文字体以避免缺字。"""

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


@dataclass(frozen=True)
class Strategy:
    """策略描述对象，出现在正规式博弈中。"""

    key: str
    label: str

    @staticmethod
    def from_raw(raw: Any, fallback_key: str) -> "Strategy":
        """将 JSON 中的策略条目规范化为 :class:`Strategy` 实例。"""

        if isinstance(raw, str):
            key = raw
            label = raw
        elif isinstance(raw, Mapping):
            key = str(
                _pick(raw, "id", "key", "name", "编号", "键", "名称", default=fallback_key)
            )
            label = str(_pick(raw, "label", "name", "标签", "名称", default=key))
        else:
            msg = f"策略定义不受支持: {raw!r}"
            raise TypeError(msg)
        return Strategy(key=key, label=label)


@dataclass
class Player:
    """博弈参与者及其可选策略。"""

    key: str
    name: str
    strategies: list[Strategy]

    @staticmethod
    def from_raw(raw: Any, ordinal: int) -> "Player":
        if not isinstance(raw, Mapping):
            msg = "参与者应以对象形式描述并包含策略集合"
            raise TypeError(msg)

        key = str(
            _pick(raw, "id", "key", "name", "编号", "标签", default=f"p{ordinal+1}")
        )
        name = str(_pick(raw, "name", "label", "名称", "标签", default=key))
        strategies_raw = _pick(raw, "strategies", "strategy", "策略", "策略集")
        if not isinstance(strategies_raw, Sequence) or not strategies_raw:
            msg = f"参与者 {name} 需要非空的'策略'列表"
            raise ValueError(msg)

        strategies = [
            Strategy.from_raw(item, fallback_key=f"s{idx+1}")
            for idx, item in enumerate(strategies_raw)
        ]
        return Player(key=key, name=name, strategies=strategies)


@dataclass(frozen=True)
class PureEquilibrium:
    """纯策略纳什均衡记录。"""

    indices: tuple[int, ...]
    strategies: dict[str, str]
    payoffs: dict[str, float]


@dataclass
class NormalFormGame:
    """正规式博弈的内存表达。由于太庞大，不多展示"""

    title: str
    players: list[Player]
    payoffs: list[Any]
    metadata: dict[str, Any]

    @property
    def shape(self) -> tuple[int, ...]:
        return tuple(len(player.strategies) for player in self.players)

    def iter_strategy_profiles(self) -> Iterable[tuple[tuple[int, ...], tuple[float, ...]]]:
        """枚举全部策略组合及对应收益向量。"""

        index_ranges = [range(len(player.strategies)) for player in self.players]
        for index_tuple in product(*index_ranges):
            yield index_tuple, self.payoff_at(index_tuple)

    def payoff_at(self, indices: Sequence[int]) -> tuple[float, ...]:
        """根据策略下标返回对应的收益向量。"""

        node: Any = self.payoffs
        for depth, index in enumerate(indices):
            try:
                node = node[index]
            except (IndexError, TypeError) as exc:  # pragma: no cover - defensive
                msg = f"收益张量形状不匹配，深度 {depth}，索引 {indices}"
                raise IndexError(msg) from exc
        if not isinstance(node, Sequence) or len(node) != len(self.players):
            msg = "末端收益应为与参与者数量相等的序列"
            raise ValueError(msg)
        return tuple(float(value) for value in node)

    def strategy_sets(self) -> dict[str, list[str]]:
        """列出每个参与者可选策略标签。"""

        return {
            player.name: [strategy.label for strategy in player.strategies]
            for player in self.players
        }

    def pure_nash_equilibria(self) -> list[PureEquilibrium]:
        """通过最佳响应检验枚举纯策略纳什均衡。"""

        if not self.players:
            return []

        index_ranges = [range(len(player.strategies)) for player in self.players]
        profiles = list(product(*index_ranges))
        if not profiles:
            return []

        best_payoffs: list[dict[tuple[int, ...], float]] = [{} for _ in self.players]
        best_responses: list[dict[tuple[int, ...], set[int]]] = [
            {} for _ in self.players
        ]

        for profile in profiles:
            payoff_vector = self.payoff_at(profile)
            for player_idx, value in enumerate(payoff_vector):
                other_key = profile[:player_idx] + profile[player_idx + 1 :]
                current_best = best_payoffs[player_idx].get(other_key, float("-inf"))
                if value > current_best:
                    best_payoffs[player_idx][other_key] = value
                    best_responses[player_idx][other_key] = {profile[player_idx]}
                elif value == current_best:
                    best_responses[player_idx][other_key].add(profile[player_idx])

        equilibria: list[PureEquilibrium] = []
        for profile in profiles:
            if all(
                profile[player_idx]
                in best_responses[player_idx][profile[:player_idx] + profile[player_idx + 1 :]]
                for player_idx in range(len(self.players))
            ):
                strategies = {
                    player.name: player.strategies[index].label
                    for player, index in zip(self.players, profile)
                }
                payoff_vector = self.payoff_at(profile)
                payoffs = {
                    player.name: payoff_vector[idx]
                    for idx, player in enumerate(self.players)
                }
                equilibria.append(
                    PureEquilibrium(indices=profile, strategies=strategies, payoffs=payoffs)
                )
        return equilibria

    @staticmethod
    def from_dict(payload: Mapping[str, Any]) -> "NormalFormGame":
        if not isinstance(payload, Mapping):
            msg = "JSON 根节点必须是对象"
            raise TypeError(msg)

        title = str(
            _pick(payload, "title", "name", "标题", "名称", default="正规式博弈")
        )
        players_raw = _pick(payload, "players", "参与者", "玩家", "局中人")
        if not isinstance(players_raw, Sequence) or len(players_raw) < 2:
            msg = "策略式博弈矩阵当前至少需要两名参与者"
            raise ValueError(msg)

        players = [Player.from_raw(item, idx) for idx, item in enumerate(players_raw)]
        payoffs = _pick(payload, "payoffs", "收益", "收益矩阵", "支付")
        if payoffs is None:
            msg = "描述缺少'收益'张量"
            raise ValueError(msg)

        NormalFormGame._validate_payoffs(payoffs, tuple(len(p.strategies) for p in players), len(players))

        metadata = {
            key: value
            for key, value in payload.items()
            if key
            not in {
                "title",
                "name",
                "players",
                "payoffs",
                "标题",
                "名称",
                "参与者",
                "玩家",
                "局中人",
                "收益",
                "收益矩阵",
                "支付",
            }
        }
        return NormalFormGame(title=title, players=players, payoffs=payoffs, metadata=metadata)

    @staticmethod
    def _validate_payoffs(node: Any, shape: tuple[int, ...], player_count: int, depth: int = 0) -> None:
        if depth == len(shape):
            if not isinstance(node, Sequence) or len(node) != player_count:
                msg = "末端收益必须与参与者数量一致"
                raise ValueError(msg)
            return

        if not isinstance(node, Sequence) or len(node) != shape[depth]:
            msg = (
                f"收益张量在深度 {depth} 处长度应为 {shape[depth]}，"
                f"实际为 {len(node) if isinstance(node, Sequence) else type(node)}"
            )
            raise ValueError(msg)

        for child in node:
            NormalFormGame._validate_payoffs(child, shape, player_count, depth + 1)


def load_normal_form_game(source: Any) -> NormalFormGame:
    """从 JSON 字符串、文件路径或字典载入 :class:`NormalFormGame`。"""

    if isinstance(source, NormalFormGame):
        return source

    if isinstance(source, Mapping):
        payload = source
    elif isinstance(source, Path):
        payload = json.loads(source.read_text(encoding="utf-8"))
    elif isinstance(source, str):
        candidate_path = Path(source)
        if candidate_path.exists():
            payload = json.loads(candidate_path.read_text(encoding="utf-8"))
        else:
            payload = json.loads(source)
    else:
        msg = f"不支持的数据来源类型: {type(source)!r}"
        raise TypeError(msg)

    return NormalFormGame.from_dict(payload)


def visualise_payoff_matrix(game: NormalFormGame, *, figsize: tuple[float, float] | None = None) -> plt.Figure:
    """将正规式博弈绘制为收益矩阵图。"""

    if len(game.players) != 2:
        msg = "矩阵可视化目前仅支持两名参与者"
        raise ValueError(msg)

    row_player, col_player = game.players
    _setup_chinese_fonts()

    # 根据策略数量动态调整图片大小
    n_rows = len(row_player.strategies)
    n_cols = len(col_player.strategies)
    
    if figsize is None:
        # 基础尺寸 + 根据策略数量调整
        base_width = 6 + n_cols * 1.5
        base_height = 4 + n_rows * 1.2
        figsize = (base_width, base_height)

    fig = plt.figure(figsize=figsize, facecolor='white')
    
    # 创建网格布局
    gs = fig.add_gridspec(3, 1, height_ratios=[0.8, 6, 0.8], hspace=0.1)
    
    # 标题区域
    title_ax = fig.add_subplot(gs[0])
    title_ax.text(0.5, 0.5, game.title, ha='center', va='center', 
                  fontsize=18, fontweight='bold', transform=title_ax.transAxes)
    title_ax.set_xlim(0, 1)
    title_ax.set_ylim(0, 1)
    title_ax.axis('off')
    
    # 主矩阵区域
    matrix_ax = fig.add_subplot(gs[1])
    matrix_ax.set_xlim(0, n_cols + 1)
    matrix_ax.set_ylim(0, n_rows + 1)
    matrix_ax.axis('off')
    
    # 准备数据
    payoff_cache = {
        indices: payoff for indices, payoff in game.iter_strategy_profiles()
    }
    equilibria_indices = {
        equilibrium.indices for equilibrium in game.pure_nash_equilibria()
    }
    
    # 绘制表格边框和背景
    # 表头背景色
    header_color = '#E8EDF7'
    nash_color = '#FFF2CC'  # 纳什均衡高亮色
    
    # 绘制所有单元格
    for i in range(n_rows + 1):  # +1 for header
        for j in range(n_cols + 1):  # +1 for left column
            x, y = j, n_rows - i
            width, height = 1, 1
            
            # 确定背景色
            if i == 0 or j == 0:  # 表头
                facecolor = header_color
            elif (i-1, j-1) in equilibria_indices:  # 纳什均衡
                facecolor = nash_color
            else:
                facecolor = 'white'
            
            # 绘制单元格背景
            rect = plt.Rectangle((x, y), width, height, 
                               facecolor=facecolor, edgecolor='black', linewidth=1.2)
            matrix_ax.add_patch(rect)
            
            # 添加文本内容
            if i == 0 and j == 0:
                # 左上角表头
                text = f"{row_player.name} 策略 / {col_player.name} 策略"
                matrix_ax.text(x + 0.5, y + 0.5, text, ha='center', va='center',
                             fontsize=12, fontweight='bold', wrap=True)
            elif i == 0 and j > 0:
                # 列表头 (Bob的策略)
                text = col_player.strategies[j-1].label
                matrix_ax.text(x + 0.5, y + 0.5, text, ha='center', va='center',
                             fontsize=14, fontweight='bold')
            elif i > 0 and j == 0:
                # 行表头 (Alice的策略)
                text = row_player.strategies[i-1].label
                matrix_ax.text(x + 0.5, y + 0.5, text, ha='center', va='center',
                             fontsize=14, fontweight='bold')
            elif i > 0 and j > 0:
                # 收益矩阵内容
                payoff_vector = payoff_cache[(i-1, j-1)]
                text = f"[{payoff_vector[0]:g}, {payoff_vector[1]:g}]"
                matrix_ax.text(x + 0.5, y + 0.5, text, ha='center', va='center',
                             fontsize=13)
    
    # 底部标签区域
    label_ax = fig.add_subplot(gs[2])
    player_order_label = ", ".join(player.name for player in game.players)
    label_text = f"收益向量顺序: [{player_order_label}]"
    label_ax.text(0.95, 0.5, label_text, ha='right', va='center',
                  fontsize=12, transform=label_ax.transAxes)
    label_ax.set_xlim(0, 1)
    label_ax.set_ylim(0, 1)
    label_ax.axis('off')
    
    # 调整整体布局，去除多余空白
    fig.subplots_adjust(left=0.02, right=0.98, top=0.95, bottom=0.05)
    
    return fig


