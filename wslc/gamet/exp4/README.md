# 实验四：讨价还价博弈模型（纯 Python）

本目录实现了课程实验四的要求：通过计算机模拟和数据分析，研究折现因子对讨价还价博弈的影响，并与理论结果对比。

## 功能概览

- 完全信息 Rubinstein 模型的理论解（`theory.py`）
- 不完全信息 + 启发式信念更新的讨价还价模拟（`simulate.py`, `strategy.py`）
- 大规模实验与数据汇总（`experiment.py`）
- Matplotlib 图表绘制（`plotting.py`）
- 简单回归测试（`tests/test_basic.py`）

## 运行环境

建议在项目根目录的虚拟环境中运行（参考仓库 `AGENTS.md`）：

```bash
source .venv/bin/activate
pip install matplotlib pandas
```

## 一键运行实验

在仓库根目录执行：

```bash
python -m exp4.main --games 5000 --seed 42
```

参数说明：

- `--games`：模拟的博弈局数，越大结果越平滑（默认 5000）
- `--seed`：随机种子，保证可复现（默认 42）
- `--output`：结果输出目录（默认 `exp4/output`）

运行结束后，将在 `exp4/output/` 中生成：

- `results_experiment.csv`：每局实验结果数据
- `results_theory.csv`：理论 Rubinstein 模型结果
- 若干 PNG 图表，如：
  - `payoff_A_vs_delta_A.png`
  - `payoff_B_vs_delta_B.png`
  - `rounds_vs_delta_A.png`
  - `guess_error_A_vs_delta_A.png`
  - `theory_vs_experiment_A.png`

这些图表可以直接用于实验报告中，展示折现因子对得益、轮数、猜测误差等的影响，并对比理论与实验结果。

## 测试

在虚拟环境中安装 `pytest` 后，可在仓库根目录运行：

```bash
pytest exp4/tests
```

用于快速回归测试，确认模拟模型在常规参数下能正常收敛并产生合理结果。

## 独立打包与运行

如果你收到了单独打包的 `exp4` 文件夹，请按照以下步骤运行：

1.  **安装依赖**：
    在 `exp4` 目录下打开终端，运行：
    ```bash
    pip install -r requirements.txt
    ```

2.  **运行实验**：
    直接运行目录下的 `run_experiment.py` 脚本：
    ```bash
    python run_experiment.py
    ```
    或者在 `exp4` 的**上级目录**中运行：
    ```bash
    python -m exp4.main
    ```

3.  **查看结果**：
    运行完成后，结果文件和图表将保存在 `output` 子目录中。

