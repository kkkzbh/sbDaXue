
import matplotlib.pyplot as plt
import matplotlib.patches as patches
import numpy as np
import os
import matplotlib.font_manager as fm

# Configure Chinese Font
# Try to find a valid CJK font from the system
def configure_font():
    # List of preferred fonts
    preferred_fonts = ['Noto Sans CJK SC', 'WenQuanYi Zen Hei', 'SimHei', 'Microsoft YaHei', 'PingFang SC', 'Heiti TC']
    
    found_font = None
    # Check system fonts
    system_fonts = fm.findSystemFonts()
    
    # Try to set font family
    plt.rcParams['font.family'] = 'sans-serif'
    plt.rcParams['font.sans-serif'] = preferred_fonts + plt.rcParams['font.sans-serif']
    
    # Also fix minus sign
    plt.rcParams['axes.unicode_minus'] = False

configure_font()

# Ensure output directory exists
os.makedirs('img', exist_ok=True)

# ---------------------------------------------------------
# Plot 1: Model Downgrade Attack Scenario (Schematic)
# ---------------------------------------------------------
def plot_scenario():
    fig, ax = plt.subplots(figsize=(10, 6))
    ax.set_xlim(0, 12)
    ax.set_ylim(0, 8)
    ax.axis('off')

    # Styles
    box_style = dict(boxstyle="round,pad=0.3", ec="black", lw=2)
    
    # 1. Buyer
    ax.add_patch(patches.Rectangle((0.5, 3), 2, 2, facecolor='#4A90E2', edgecolor='black', alpha=0.9, zorder=2))
    ax.text(1.5, 4, "买家\n(开发者)", ha='center', va='center', fontsize=14, color='white', fontweight='bold')

    # 2. Intermediary (Black Box)
    ax.add_patch(patches.Rectangle((4.5, 2.5), 3, 3, facecolor='#333333', edgecolor='black', alpha=1.0, zorder=2))
    ax.text(6, 4.8, "API 中转站/卖家", ha='center', va='center', fontsize=12, color='white', fontweight='bold')
    # Switch/Logic internal
    ax.text(6, 3.5, "路由判定\n(欺诈/开关)", ha='center', va='center', fontsize=10, color='#DDDDDD')
    
    # 3. Models (Right side)
    # High Model
    ax.add_patch(patches.Rectangle((9.5, 4.5), 2.5, 2, facecolor='#2ECC71', edgecolor='black', alpha=0.9, zorder=2))
    ax.text(10.75, 5.5, "高端模型\n(Claude 3.5/GPT-4)", ha='center', va='center', fontsize=10, color='white', fontweight='bold')
    
    # Low Model
    ax.add_patch(patches.Rectangle((9.5, 1.5), 2.5, 2, facecolor='#F39C12', edgecolor='black', alpha=0.9, zorder=2))
    ax.text(10.75, 2.5, "低端模型\n(Llama/GPT-3.5)", ha='center', va='center', fontsize=10, color='white', fontweight='bold')

    # Arrows
    # Buyer -> Seller
    ax.annotate("", xy=(4.5, 4), xytext=(2.5, 4), arrowprops=dict(arrowstyle="->", lw=3, color='black'))
    
    # Seller -> High (Dashed - Claimed/Honest)
    ax.annotate("", xy=(9.5, 5.5), xytext=(7.5, 4.2), arrowprops=dict(arrowstyle="->", lw=2, color='green', linestyle='dashed'))
    ax.text(8.5, 5.2, "声称路径", ha='center', va='center', fontsize=10, color='green', rotation=15)
    
    # Seller -> Low (Solid - Actual Fraud)
    ax.annotate("", xy=(9.5, 2.5), xytext=(7.5, 3.8), arrowprops=dict(arrowstyle="->", lw=3, color='#C0392B'))
    ax.text(8.5, 2.8, "实际路径\n(降级)", ha='center', va='center', fontsize=10, color='#C0392B', rotation=-15)

    plt.tight_layout()
    plt.savefig('img/scenario.png', dpi=150, bbox_inches='tight')
    plt.close()
    print("Generated img/scenario.png")


# ---------------------------------------------------------
# Plot 2: Game Flow Timeline
# ---------------------------------------------------------
def plot_game_flow():
    fig, ax = plt.subplots(figsize=(12, 4))
    ax.set_xlim(0, 12)
    ax.set_ylim(0, 4)
    ax.axis('off')

    # Nodes
    steps = [
        (1.5, "1. 报价与声明", "#3498DB"),
        (4.5, "2. 试探性测试\n(含陷阱题)", "#F1C40F"),
        (7.5, "3. 信念更新\n(贝叶斯)", "#9B59B6"),
        (10.5, "4. 决策\n(签约/封禁)", "#E74C3C")
    ]

    for i, (x, label, col) in enumerate(steps):
        # Time points
        circle = patches.Circle((x, 2), radius=0.6, facecolor=col, edgecolor='black', zorder=3)
        ax.add_patch(circle)
        # Icons (Simple Text inside)
        ax.text(x, 2, str(i+1), ha='center', va='center', color='white', fontweight='bold', fontsize=16)
        # Labels below
        ax.text(x, 0.8, label, ha='center', va='top', fontsize=12, fontweight='bold', backgroundcolor='white')

    # Connecting Arrows
    for i in range(len(steps) - 1):
        x_start = steps[i][0] + 0.8
        x_end = steps[i+1][0] - 0.8
        ax.annotate("", xy=(x_end, 2), xytext=(x_start, 2), arrowprops=dict(arrowstyle="->", lw=3, color='gray'))

    # Annotations
    ax.text(6, 3.5, "时间 $t$", ha='center', va='center', fontsize=14, fontstyle='italic')
    ax.annotate("", xy=(11.5, 3.5), xytext=(0.5, 3.5), arrowprops=dict(arrowstyle="->", lw=1.5, color='black'))

    plt.tight_layout()
    plt.savefig('img/timeline.png', dpi=150, bbox_inches='tight')
    plt.close()
    print("Generated img/timeline.png")


# ---------------------------------------------------------
# Plot 3: Equilibrium Analysis
# ---------------------------------------------------------
def plot_equilibrium():
    fig, ax = plt.subplots(figsize=(10, 6))
    
    # Data Simulation
    alpha = np.linspace(0, 0.1, 100) # Audit intensity 0% to 10%
    
    # Honest Payoff (Constant)
    # R - CH + Future Value (high)
    pi_honest = np.ones_like(alpha) * 6.0 
    
    # Malicious Payoff (Decreasing with alpha)
    # (R - CH) + Delta_C + P(pass)*Future_Risk_Adj
    # Assume simplified curve: Start high, drop exponentially or linearly
    # pi_mal = 8.0 - 50 * alpha  (Linear approx for visualization)
    pi_mal = 4.0 + 5.0 * np.exp(-30 * alpha)

    # Plot
    ax.plot(alpha, pi_honest, label='诚实策略收益 (Honest)', color='#2980B9', linewidth=3)
    ax.plot(alpha, pi_mal, label='欺诈策略收益 (Malicious)', color='#C0392B', linewidth=3)

    # Intersection
    idx = np.argwhere(np.diff(np.sign(pi_honest - pi_mal))).flatten()
    if len(idx) > 0:
        cross_x = alpha[idx[0]]
        cross_y = pi_honest[idx[0]]
        ax.plot(cross_x, cross_y, 'ko', markersize=8)
        ax.annotate(f'威慑阈值 $\\alpha^*$', xy=(cross_x, cross_y), xytext=(cross_x + 0.02, cross_y + 1),
                    arrowprops=dict(facecolor='black', shrink=0.05), fontsize=12)
        
        # Shade regions
        ax.fill_between(alpha, 0, 10, where=(alpha < cross_x), color='#E74C3C', alpha=0.1)
        ax.text(cross_x/2, 2, "欺诈盈利区\n(Fraud Zone)", ha='center', fontsize=12, color='#C0392B', fontweight='bold')
        
        ax.fill_between(alpha, 0, 10, where=(alpha > cross_x), color='#2980B9', alpha=0.1)
        ax.text(cross_x + (0.1-cross_x)/2, 2, "诚实盈利区\n(Honest Zone)", ha='center', fontsize=12, color='#2980B9', fontweight='bold')

    # Styling
    ax.set_title('审计强度与卖家策略均衡分析', fontsize=16, fontweight='bold', pad=20)
    ax.set_xlabel('审计强度/陷阱题比例 ($\\alpha$)', fontsize=12)
    ax.set_ylabel('卖家期望效用 (Utility)', fontsize=12)
    ax.set_xlim(0, 0.1)
    ax.set_ylim(0, 9.5)
    
    # Format x-axis as percentage
    vals = ax.get_xticks()
    ax.set_xticklabels(['{:,.0%}'.format(x) for x in vals])

    ax.legend(loc='upper right', fontsize=12)
    ax.grid(True, linestyle='--', alpha=0.5)

    plt.tight_layout()
    plt.savefig('img/equilibrium.png', dpi=150, bbox_inches='tight')
    plt.close()
    print("Generated img/equilibrium.png")

if __name__ == "__main__":
    plot_scenario()
    plot_game_flow()
    plot_equilibrium()
