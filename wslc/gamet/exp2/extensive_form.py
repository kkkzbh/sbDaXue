"""博弈树（扩展式博弈）解析与可视化模块。"""

from __future__ import annotations

import json
from dataclasses import dataclass
from itertools import product
from pathlib import Path
from typing import Any, Iterable, Mapping, Sequence

import matplotlib.pyplot as plt
from matplotlib import patches
from matplotlib import patheffects
from matplotlib import font_manager as fm


def _pick(mapping: Mapping[str, Any], *candidates: str, default: Any = None) -> Any:
    for key in candidates:
        if key in mapping:
            return mapping[key]
    return default


def _setup_chinese_fonts() -> None:
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


@dataclass
class TreeAction:
    label: str
    child: "TreeNode"


@dataclass
class TreeNode:
    node_id: str
    node_type: str  # decision or terminal
    player: str | None
    actions: list[TreeAction]
    payoff: tuple[float, ...] | None

    def is_terminal(self) -> bool:
        return self.node_type == "terminal"


@dataclass
class PlayerStrategy:
    label: str
    mapping: dict[str, str]


@dataclass
class StrategyProfile:
    choices: dict[str, PlayerStrategy]
    payoff: tuple[float, ...]


@dataclass
class ExtensiveFormGame:
    title: str
    players: list[str]
    root: TreeNode

    def decision_nodes_by_player(self) -> dict[str, list[TreeNode]]:
        buckets: dict[str, list[TreeNode]] = {player: [] for player in self.players}

        def _walk(node: TreeNode) -> None:
            if node.node_type == "decision" and node.player in buckets:
                buckets[node.player].append(node)
            for action in node.actions:
                _walk(action.child)

        _walk(self.root)
        return buckets

    def player_strategies(self) -> dict[str, list[PlayerStrategy]]:
        decision_nodes = self.decision_nodes_by_player()
        strategies: dict[str, list[PlayerStrategy]] = {}
        for player, nodes in decision_nodes.items():
            if not nodes:
                strategies[player] = [PlayerStrategy(label="（无须行动）", mapping={})]
                continue
            action_lists = [[action.label for action in node.actions] for node in nodes]
            combos = product(*action_lists)
            player_strategies: list[PlayerStrategy] = []
            for combo in combos:
                mapping = {node.node_id: choice for node, choice in zip(nodes, combo)}
                label_parts = [f"{node.node_id}:{choice}" for node, choice in zip(nodes, combo)]
                label = " | ".join(label_parts)
                player_strategies.append(PlayerStrategy(label=label, mapping=mapping))
            strategies[player] = player_strategies
        return strategies

    def _strategy_spaces(self) -> tuple[list[str], list[list[PlayerStrategy]]]:
        strategy_spaces = self.player_strategies()
        player_order = self.players
        spaces = [strategy_spaces[player] for player in player_order]
        return player_order, spaces

    def iter_strategy_profiles(self) -> Iterable[StrategyProfile]:
        player_order, spaces = self._strategy_spaces()
        for combo in product(*spaces):
            choice_map = {player: strategy for player, strategy in zip(player_order, combo)}
            payoff = self._evaluate_profile(choice_map)
            yield StrategyProfile(choices=choice_map, payoff=payoff)

    def _evaluate_profile(self, choice_map: dict[str, PlayerStrategy]) -> tuple[float, ...]:
        terminal_node, _ = self._resolve_path(choice_map)
        if terminal_node.payoff is None:
            raise ValueError(f"叶子节点 {terminal_node.node_id} 缺少收益向量")
        return terminal_node.payoff

    def _resolve_path(
        self, choice_map: dict[str, PlayerStrategy]
    ) -> tuple[TreeNode, tuple[tuple[str, str], ...]]:
        node = self.root
        traversed: list[tuple[str, str]] = []
        while not node.is_terminal():
            current_id = node.node_id
            if node.node_type != "decision":
                raise ValueError(f"暂不支持的节点类型: {node.node_type}")
            strategy = choice_map[node.player]
            action_label = strategy.mapping.get(node.node_id)
            if action_label is None:
                action_label = node.actions[0].label
            for action in node.actions:
                if action.label == action_label:
                    traversed.append((current_id, action.label))
                    node = action.child
                    break
            else:
                raise ValueError(f"策略未定义动作: 节点 {node.node_id}，动作 {action_label}")
        return node, tuple(traversed)

    def pure_nash_equilibria(self) -> list[StrategyProfile]:
        player_order, spaces = self._strategy_spaces()
        if not spaces:
            return []
        profiles: list[StrategyProfile] = []
        profile_indices: list[tuple[int, ...]] = []
        for combo in product(*spaces):
            choice_map = {player: strategy for player, strategy in zip(player_order, combo)}
            payoff = self._evaluate_profile(choice_map)
            profiles.append(StrategyProfile(choices=choice_map, payoff=payoff))
        for index_tuple in product(*[range(len(space)) for space in spaces]):
            profile_indices.append(index_tuple)
        if not profiles:
            return []
        best_payoffs: list[dict[tuple[int, ...], float]] = [{} for _ in player_order]
        best_responses: list[dict[tuple[int, ...], set[int]]] = [{} for _ in player_order]
        for profile_idx, profile in zip(profile_indices, profiles):
            payoff = profile.payoff
            for player_idx, player in enumerate(self.players):
                other_key = profile_idx[:player_idx] + profile_idx[player_idx + 1 :]
                current_best = best_payoffs[player_idx].get(other_key, float("-inf"))
                value = payoff[player_idx]
                if value > current_best:
                    best_payoffs[player_idx][other_key] = value
                    best_responses[player_idx][other_key] = {profile_idx[player_idx]}
                elif value == current_best:
                    best_responses[player_idx][other_key].add(profile_idx[player_idx])
        equilibria: list[StrategyProfile] = []
        for profile_idx, profile in zip(profile_indices, profiles):
            is_equilibrium = True
            for player_idx in range(len(self.players)):
                other_key = profile_idx[:player_idx] + profile_idx[player_idx + 1 :]
                if profile_idx[player_idx] not in best_responses[player_idx][other_key]:
                    is_equilibrium = False
                    break
            if is_equilibrium:
                equilibria.append(profile)
        return equilibria


def load_extensive_form_game(source: Any) -> ExtensiveFormGame:
    if isinstance(source, ExtensiveFormGame):
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
        raise TypeError(f"不支持的数据来源类型: {type(source)!r}")

    return _game_from_payload(payload)


def _game_from_payload(payload: Mapping[str, Any]) -> ExtensiveFormGame:
    if not isinstance(payload, Mapping):
        raise TypeError("JSON 根节点必须是对象")
    title = str(_pick(payload, "title", "name", "标题", "名称", default="扩展式博弈"))
    players_raw = _pick(payload, "players", "参与者", "玩家", "局中人")
    if not isinstance(players_raw, Sequence) or len(players_raw) < 1:
        raise ValueError("扩展式博弈需要至少一名参与者")
    players = [str(item) for item in players_raw]
    root_raw = _pick(payload, "root", "根节点", "树")
    if root_raw is None:
        raise ValueError("缺少根节点定义")
    root = _parse_node(root_raw, players, node_id="root")
    return ExtensiveFormGame(title=title, players=players, root=root)


def _parse_node(raw: Mapping[str, Any], players: Sequence[str], node_id: str) -> TreeNode:
    if not isinstance(raw, Mapping):
        raise TypeError(f"节点 {node_id} 应为对象")
    node_type = str(_pick(raw, "type", "类型", default="decision"))
    node_type = node_type.lower()
    if node_type not in {"decision", "terminal"}:
        raise ValueError(f"节点 {node_id} 使用了暂不支持的类型 {node_type}")
    player = None
    actions: list[TreeAction] = []
    payoff: tuple[float, ...] | None = None
    if node_type == "decision":
        player = str(_pick(raw, "player", "参与者", "玩家"))
        if player not in players:
            raise ValueError(f"节点 {node_id} 指定的参与者 {player} 不在玩家列表中")
        actions_raw = _pick(raw, "actions", "行动", "选择", "边")
        if not isinstance(actions_raw, Sequence) or not actions_raw:
            raise ValueError(f"节点 {node_id} 缺少至少一个可选行动")
        for idx, action_raw in enumerate(actions_raw):
            if not isinstance(action_raw, Mapping):
                raise TypeError(f"节点 {node_id} 的行动需要对象描述")
            label = str(_pick(action_raw, "label", "名称", "动作", default=f"a{idx+1}"))
            child_raw = _pick(action_raw, "child", "子节点")
            if child_raw is None:
                raise ValueError(f"节点 {node_id} 的行动 {label} 缺少子节点")
            child = _parse_node(child_raw, players, node_id=f"{node_id}.{idx}")
            actions.append(TreeAction(label=label, child=child))
    else:
        payoff_raw = _pick(raw, "payoff", "收益", "结果", "支付")
        if not isinstance(payoff_raw, Sequence) or len(payoff_raw) != len(players):
            raise ValueError(f"叶子节点 {node_id} 的收益向量应与参与者数量一致")
        payoff = tuple(float(value) for value in payoff_raw)
    return TreeNode(node_id=node_id, node_type=node_type, player=player, actions=actions, payoff=payoff)


def visualise_game_tree(game: ExtensiveFormGame, *, figsize: tuple[float, float] | None = None) -> plt.Figure:
    if figsize is None:
        figsize = (12.0, 8.0)
    _setup_chinese_fonts()
    fig, ax = plt.subplots(figsize=figsize)
    ax.set_axis_off()
    ax.set_title(game.title, fontsize=20, pad=6)

    positions: dict[str, tuple[float, float]] = {}
    layers: dict[int, list[TreeNode]] = {}

    def _assign(node: TreeNode, depth: int = 0) -> None:
        layers.setdefault(depth, []).append(node)
        for action in node.actions:
            _assign(action.child, depth + 1)

    _assign(game.root)
    max_width = max(len(nodes) for nodes in layers.values())
    for depth, nodes in layers.items():
        y = 1.0 - depth / max(max(layers.keys()), 1) if layers else 1.0
        count = len(nodes)
        for idx, node in enumerate(nodes):
            x = (idx + 1) / (count + 1)
            positions[node.node_id] = (x, y)

    def _draw(node: TreeNode) -> None:
        x, y = positions[node.node_id]
        if node.is_terminal():
            box = patches.FancyBboxPatch(
                (x - 0.05, y - 0.02),
                0.1,
                0.04,
                boxstyle="round,pad=0.02",
                linewidth=1,
                facecolor="#f5f5f5",
                edgecolor="#333333",
            )
            ax.add_patch(box)
            ax.text(
                x,
                y,
                "[" + ", ".join(f"{value:g}" for value in node.payoff or []) + "]",
                fontsize=11,
                ha="center",
                va="center",
            )
        else:
            ax.text(
                x,
                y,
                node.player,
                fontsize=12,
                ha="center",
                va="center",
                bbox=dict(boxstyle="round", facecolor="#e8f1ff", edgecolor="#7da0c8"),
            )
        for action in node.actions:
            child = action.child
            cx, cy = positions[child.node_id]
            ax.plot([x, cx], [y - 0.02, cy + 0.02], color="#555555", linewidth=1.2)
            label_x = (x + cx) / 2
            label_y = (y + cy) / 2
            ax.text(
                label_x,
                label_y,
                action.label,
                fontsize=11,
                ha="center",
                va="center",
                path_effects=[patheffects.withStroke(linewidth=3, foreground="white")],
            )
            _draw(child)

    _draw(game.root)

    player_order_label = ", ".join(game.players)
    fig.text(
        0.95,
        0.04,
        f"收益向量顺序: [{player_order_label}]",
        ha="right",
        va="bottom",
        fontsize=14,
    )

    plt.subplots_adjust(left=0.05, right=0.95, top=0.9, bottom=0.1)

    return fig
