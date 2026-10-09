LIBRARY ieee;                                       -- 引入IEEE标准库
USE ieee.std_logic_1164.ALL;                        -- 使用标准逻辑数据类型库
USE ieee.numeric_std.ALL;                           -- 使用标准数值运算库

ENTITY exp14_top IS
  PORT (
    clk     : IN  STD_LOGIC;                        -- 50MHz/24MHz 时钟输入 (PIN_210)
    reset   : IN  STD_LOGIC;                        -- 复位信号输入 (PIN_151，高电平有效)

    key_r   : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);     -- 矩阵键盘行扫描输出 (PIN_18..21，低电平有效)
    key_c   : IN  STD_LOGIC_VECTOR(3 DOWNTO 0);     -- 矩阵键盘列输入 (PIN_9,6,5,4)

    row     : OUT STD_LOGIC_VECTOR(15 DOWNTO 0);    -- LED点阵行选信号 (低电平有效)
    col     : OUT STD_LOGIC_VECTOR(15 DOWNTO 0);    -- LED点阵列选信号 (低电平有效)

    seg     : OUT STD_LOGIC_VECTOR(7 DOWNTO 0);     -- 7段数码管段选信号 (active low)
    dig     : OUT STD_LOGIC_VECTOR(5 DOWNTO 0);     -- 7段数码管位选信号 (active low)

    ldd     : OUT STD_LOGIC_VECTOR(7 DOWNTO 0);     -- LED灯条 (低电平有效)
    buzzer  : OUT STD_LOGIC                         -- 蜂鸣器输出 (可选，PIN_174)
  );
END ENTITY;

ARCHITECTURE rtl OF exp14_top IS
  -- 定义内部信号
  SIGNAL k_stb : STD_LOGIC;                         -- 按键选通信号 (strobe)，表示有按键按下
  SIGNAL k_val : STD_LOGIC_VECTOR(3 DOWNTO 0);      -- 按下的键值 (0-15)

  SIGNAL edit_is_a_s, in_single_s, in_result_s : STD_LOGIC; -- 状态信号：正在编辑A/单矩阵模式/显示结果模式
  SIGNAL cursor_idx_s : UNSIGNED(1 DOWNTO 0);       -- 当前光标位置索引 (0-3)

  -- 矩阵数据信号 (A矩阵、B矩阵、M显示矩阵)
  SIGNAL a11_s, a12_s, a21_s, a22_s : SIGNED(15 DOWNTO 0); -- 矩阵A的元素
  SIGNAL b11_s, b12_s, b21_s, b22_s : SIGNED(15 DOWNTO 0); -- 矩阵B的元素
  SIGNAL m11_s, m12_s, m21_s, m22_s : SIGNED(15 DOWNTO 0); -- 当前显示的矩阵元素 (M)

  SIGNAL scalar_ok_s : STD_LOGIC;                   -- 标量结果有效标志 (如行列式值)
  SIGNAL scalar_s    : SIGNED(31 DOWNTO 0);         -- 标量结果数值

  -- 数码管显示字符信号
  SIGNAL g0, g1, g2, g3, g4, g5 : UNSIGNED(4 DOWNTO 0) := (OTHERS => '0');
  SIGNAL dp_s : STD_LOGIC_VECTOR(5 DOWNTO 0) := (OTHERS => '1'); -- 小数点控制 (低电平点亮)

  -- 蜂鸣器控制信号
  SIGNAL buz_cnt : NATURAL RANGE 0 TO 240000 := 0;  -- 蜂鸣器持续时间计数器 (24MHz下约10ms)
  SIGNAL buz_div : NATURAL RANGE 0 TO 5999 := 0;    -- 蜂鸣器频率分频计数器
  SIGNAL buz_on  : STD_LOGIC := '0';                -- 蜂鸣器开启标志
  SIGNAL buz_sig : STD_LOGIC := '0';                -- 蜂鸣器驱动信号
  SIGNAL rst : STD_LOGIC;                           -- 内部高电平有效复位信号

  -- 字形常量定义
  CONSTANT GLYPH_BLANK : UNSIGNED(4 DOWNTO 0) := TO_UNSIGNED(16, 5); -- 空白
  CONSTANT GLYPH_DASH  : UNSIGNED(4 DOWNTO 0) := TO_UNSIGNED(17, 5); -- 负号/横线
  CONSTANT GLYPH_E     : UNSIGNED(4 DOWNTO 0) := TO_UNSIGNED(14, 5); -- 'E' (未用)
  CONSTANT GLYPH_r     : UNSIGNED(4 DOWNTO 0) := TO_UNSIGNED(18, 5); -- 'r' (未用)

  -- 辅助函数：计算32位有符号数的绝对值，返回无符号数
  FUNCTION abs32(x : SIGNED(31 DOWNTO 0)) RETURN UNSIGNED IS
    VARIABLE a : SIGNED(31 DOWNTO 0);
  BEGIN
    IF x < 0 THEN
      a := -x;
    ELSE
      a := x;
    END IF;
    RETURN UNSIGNED(a);
  END FUNCTION;

  -- 辅助函数：取16位有符号数的低4位 (Nibble)
  FUNCTION lo_nibble(x : SIGNED(15 DOWNTO 0)) RETURN UNSIGNED IS
  BEGIN
    RETURN UNSIGNED(x(3 DOWNTO 0));
  END FUNCTION;

BEGIN
  rst <= NOT reset;  -- 输入reset是低电平有效(按键)，取反生成内部高电平有效复位信号

  -- 实例化按键扫描模块
  u_kbd : ENTITY work.key_scanner
    PORT MAP (
      clk        => clk,        -- 系统时钟
      reset      => rst,        -- 复位信号
      key_r      => key_r,      -- 行扫描输出
      key_c      => key_c,      -- 列扫描输入
      key_strobe => k_stb,      -- 按键有效脉冲
      key_val    => k_val       -- 键值
    );

  -- 实例化矩阵计算核心模块
  u_calc : ENTITY work.matrix_calculator
    PORT MAP (
      clk          => clk,          -- 时钟
      reset        => rst,          -- 复位
      key_strobe   => k_stb,        -- 按键脉冲
      key_val      => k_val,        -- 键值
      edit_is_a    => edit_is_a_s,  -- 是否正在编辑A矩阵状态
      in_single    => in_single_s,  -- 单矩阵显示模式状态
      in_result    => in_result_s,  -- 结果显示模式状态
      a11          => a11_s,        -- A11 输出
      a12          => a12_s,        -- A12 输出
      a21          => a21_s,        -- A21 输出
      a22          => a22_s,        -- A22 输出
      b11          => b11_s,        -- B11 输出
      b12          => b12_s,        -- B12 输出
      b21          => b21_s,        -- B21 输出
      b22          => b22_s,        -- B22 输出
      m11          => m11_s,        -- 当前显示矩阵 M11
      m12          => m12_s,        -- 当前显示矩阵 M12
      m21          => m21_s,        -- 当前显示矩阵 M21
      m22          => m22_s,        -- 当前显示矩阵 M22
      cursor_idx   => cursor_idx_s, -- 当前光标位置
      scalar_valid => scalar_ok_s,  -- 标量结果有效
      scalar_value => scalar_s      -- 标量结果值
    );

  -- 实例化LED点阵显示模块
  u_led : ENTITY work.led_matrix_2x2_hex
    PORT MAP (
      clk   => clk,     -- 时钟
      reset => rst,     -- 复位
      v11   => m11_s,   -- 待显示的矩阵值 (左上)
      v12   => m12_s,   -- (右上)
      v21   => m21_s,   -- (左下)
      v22   => m22_s,   -- (右下)
      row   => row,     -- 行驱动
      col   => col      -- 列驱动
    );

  -- 实例化数码管与数码管扫描模块
  u_seg : ENTITY work.seg6_mux
    PORT MAP (
      clk    => clk,    -- 时钟
      reset  => rst,    -- 复位
      glyph0 => g0,     -- 数码管0显示内容
      glyph1 => g1,     -- 数码管1显示内容
      glyph2 => g2,     -- 数码管2显示内容
      glyph3 => g3,     -- 数码管3显示内容
      glyph4 => g4,     -- 数码管4显示内容
      glyph5 => g5,     -- 数码管5显示内容
      dp     => dp_s,   -- 小数点控制
      seg    => seg,    -- 段选输出
      dig    => dig     -- 位选输出
    );

  -- 状态指示灯 (LED Bar)，低电平点亮
  -- 显示当前编辑的是A还是B，当前是处于什么模式
  ldd(0) <= edit_is_a_s;      -- LED0: 亮表示编辑矩阵B (edit_is_a_s=0)
  ldd(1) <= NOT edit_is_a_s;  -- LED1: 亮表示编辑矩阵A (edit_is_a_s=1)
  ldd(2) <= in_single_s;      -- LED2: 亮表示常规/视图模式 (in_single_s=0)
  ldd(3) <= NOT in_single_s;  -- LED3: 亮表示单矩阵操作模式 (in_single_s=1)
  ldd(4) <= in_result_s;      -- LED4: 亮表示编辑/单矩阵模式 (in_result_s=0)
  ldd(5) <= NOT in_result_s;  -- LED5: 亮表示结果查看模式 (in_result_s=1)
  ldd(6) <= '1';              -- 常灭 (保留)
  ldd(7) <= '1';              -- 常灭 (保留)

  -- 蜂鸣器进程：按键按下时发出短促提示音
  PROCESS(clk)
  BEGIN
    IF rising_edge(clk) THEN                        -- 上升沿触发
      IF rst = '1' THEN                             -- 复位
        buz_cnt <= 0;
        buz_on <= '0';
        buz_div <= 0;
        buz_sig <= '0';
      ELSE
        IF k_stb = '1' THEN                         -- 检测到按键有效脉冲
          buz_cnt <= 240000;                        -- 设置蜂鸣时长计数器 (240000cyc / 24MHz = 10ms)
          buz_on <= '1';                            -- 开启蜂鸣器使能
        ELSIF buz_cnt = 0 THEN                      -- 计数结束
          buz_on <= '0';                            -- 关闭蜂鸣器
        ELSE
          buz_cnt <= buz_cnt - 1;                   -- 倒计时
        END IF;

        IF buz_on = '1' THEN                        -- 如果蜂鸣器开启
          IF buz_div = 5999 THEN                    -- 分频计数 (24MHz / 12000 = 2kHz)
            buz_div <= 0;
            buz_sig <= NOT buz_sig;                 -- 翻转输出信号生成方波
          ELSE
            buz_div <= buz_div + 1;
          END IF;
        ELSE
          buz_div <= 0;
          buz_sig <= '0';                           -- 蜂鸣器关闭时输出低
        END IF;
      END IF;
    END IF;
  END PROCESS;
  buzzer <= buz_sig;                                -- 将内部蜂鸣器信号输出到端口

  -- 数码管内容显示逻辑进程
  -- 功能：
  -- 1. 如果是标量结果 (scalar_valid)，显示有符号16进制数 (负号+5位)
  -- 2. 否则，显示当前矩阵(M)的4个元素的低4位 (4位HEX)
  PROCESS(edit_is_a_s, in_single_s, in_result_s, cursor_idx_s, scalar_ok_s, scalar_s,
          m11_s, m12_s, m21_s, m22_s)
    VARIABLE is_neg : BOOLEAN;                      -- 是否为负数
    VARIABLE a : UNSIGNED(31 DOWNTO 0);             -- 绝对值暂存
  BEGIN
    dp_s <= (OTHERS => '1');                        -- 默认小数点全灭 (active low)

    IF scalar_ok_s = '1' THEN                       -- 如果有标量结果 (如行列式)
      is_neg := (scalar_s < 0);                     -- 判断正负
      a := abs32(scalar_s);                         -- 取绝对值

      g0 <= ("0" & a(3 DOWNTO 0));                  -- 显示最低位 (HEX)
      g1 <= ("0" & a(7 DOWNTO 4));                  -- 显示次低位
      g2 <= ("0" & a(11 DOWNTO 8));
      g3 <= ("0" & a(15 DOWNTO 12));
      g4 <= ("0" & a(19 DOWNTO 16));
      IF is_neg THEN
        g5 <= GLYPH_DASH;                           -- 如果是负数，最高位显示负号
      ELSE
        g5 <= ("0" & a(23 DOWNTO 20));              -- 否则显示最高位数字
      END IF;
    ELSE
      -- 矩阵模式：显示4个矩阵元素的低4位
      -- 布局：g3(左上) g2(右上) g1(左下) g0(右下)
      g0 <= ("0" & lo_nibble(m22_s));
      g1 <= ("0" & lo_nibble(m21_s));
      g2 <= ("0" & lo_nibble(m12_s));
      g3 <= ("0" & lo_nibble(m11_s));
      g4 <= GLYPH_BLANK;                            -- 高位消隐
      g5 <= GLYPH_BLANK;

      -- 光标小数点指示 (仅在编辑模式有效)
      -- 用小数点指示当前正在编辑哪个矩阵元素
      IF in_result_s = '0' AND in_single_s = '0' THEN
        CASE TO_INTEGER(cursor_idx_s) IS
          WHEN 0 => dp_s(3) <= '0';                 -- 光标0 -> 点亮数码管3的小数点 (对应m11)
          WHEN 1 => dp_s(2) <= '0';                 -- 光标1 -> 点亮数码管2的小数点 (对应m12)
          WHEN 2 => dp_s(1) <= '0';                 -- 光标2 -> 点亮数码管1的小数点 (对应m21)
          WHEN OTHERS => dp_s(0) <= '0';            -- 光标3 -> 点亮数码管0的小数点 (对应m22)
        END CASE;
      END IF;
    END IF;
  END PROCESS;
END ARCHITECTURE;
