LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY key_scanner IS
  GENERIC (
    scan_div         : NATURAL := 3000;  -- 扫描行分频系数，24MHz时钟下，每行扫描间隔约125us (24000/3001)
    debounce_cycles  : NATURAL := 4;     -- 消抖周期，需要连续4个完整扫描帧确认按键按下
    release_cycles   : NATURAL := 2      -- 释放周期，需要连续2个完整扫描帧确认按键释放
  );
  PORT (
    clk        : IN  STD_LOGIC;                      -- 系统时钟
    reset      : IN  STD_LOGIC;                      -- 复位信号 (高电平有效)

    key_r      : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);   -- 键盘行驱动信号 (低电平有效)
    key_c      : IN  STD_LOGIC_VECTOR(3 DOWNTO 0);   -- 键盘列检测信号 (按下时为低电平)

    key_strobe : OUT STD_LOGIC;                      -- 按键确认脉冲 (高电平有效，持续一个时钟周期)
    key_val    : OUT STD_LOGIC_VECTOR(3 DOWNTO 0)    -- 键值输出 (0-9, A=10, B=11, C=12, D=13, *=14, #=15)
  );
END ENTITY;

ARCHITECTURE rtl OF key_scanner IS
  -- 定义列采样数组类型，用于存储4行的列输入状态
  TYPE col_samples_t IS ARRAY (0 TO 3) OF STD_LOGIC_VECTOR(3 DOWNTO 0);

  SIGNAL div_cnt      : NATURAL RANGE 0 TO scan_div := 0; -- 扫描分频计数器
  SIGNAL row_idx      : NATURAL RANGE 0 TO 3 := 0;        -- 当前扫描行索引
  SIGNAL col_samples  : col_samples_t := (OTHERS => (OTHERS => '1')); -- 存储所有行的列采样结果，默认全是1(未按下)

  SIGNAL frame_pulse  : STD_LOGIC := '0';                 -- 帧同步脉冲，每扫描完4行产生一次

  SIGNAL raw_any      : STD_LOGIC := '0';                 -- 原始按键检测标志 (未消抖)
  SIGNAL raw_code     : STD_LOGIC_VECTOR(3 DOWNTO 0) := (OTHERS => '0'); -- 原始扫描码 (未消抖)

  SIGNAL stable_any   : STD_LOGIC := '0';                 -- 稳定按键状态标志
  SIGNAL stable_code  : STD_LOGIC_VECTOR(3 DOWNTO 0) := (OTHERS => '0'); -- 稳定扫描码
  SIGNAL press_cnt    : NATURAL := 0;                     -- 按下持续时间计数器 (用于消抖)
  SIGNAL rel_cnt      : NATURAL := 0;                     -- 释放持续时间计数器
  SIGNAL key_down     : STD_LOGIC := '0';                 -- 按键已确认按下状态标志

  -- 辅助函数：将行列坐标解码为键值
  FUNCTION decode_key(row_i : NATURAL; col_i : NATURAL) RETURN STD_LOGIC_VECTOR IS
    VARIABLE v : INTEGER := 0;
  BEGIN
    -- 键盘布局映射:
    -- row0: 1 2 3 A
    -- row1: 4 5 6 B
    -- row2: 7 8 9 C
    -- row3: * 0 # D
    -- 注意：* 映射为 14, # 映射为 15, A-D 映射为 10-13
    IF row_i = 0 THEN
      CASE col_i IS
        WHEN 0 => v := 1;
        WHEN 1 => v := 2;
        WHEN 2 => v := 3;
        WHEN OTHERS => v := 10; -- A
      END CASE;
    ELSIF row_i = 1 THEN
      CASE col_i IS
        WHEN 0 => v := 4;
        WHEN 1 => v := 5;
        WHEN 2 => v := 6;
        WHEN OTHERS => v := 11; -- B
      END CASE;
    ELSIF row_i = 2 THEN
      CASE col_i IS
        WHEN 0 => v := 7;
        WHEN 1 => v := 8;
        WHEN 2 => v := 9;
        WHEN OTHERS => v := 12; -- C
      END CASE;
    ELSE -- row_i = 3
      CASE col_i IS
        WHEN 0 => v := 14;      -- *
        WHEN 1 => v := 0;
        WHEN 2 => v := 15;      -- #
        WHEN OTHERS => v := 13; -- D
      END CASE;
    END IF;
    RETURN STD_LOGIC_VECTOR(TO_UNSIGNED(v, 4));
  END FUNCTION;

BEGIN
  -- 行扫描驱动逻辑 (低电平有效，选中某一行输出0，其他输出1)
  -- row_idx 决定哪一行被拉低
  PROCESS(row_idx)
  BEGIN
    key_r <= (OTHERS => '1');  -- 默认全高
    key_r(row_idx) <= '0';     -- 当前行拉低
  END PROCESS;

  -- 主时钟进程：处理扫描、采样、消抖
  PROCESS(clk)
    VARIABLE found   : BOOLEAN;                     -- 临时变量：是否找到按键
    VARIABLE r_i     : NATURAL;                     -- 临时变量
    VARIABLE c_i     : NATURAL;                     -- 临时变量
    VARIABLE code_v  : STD_LOGIC_VECTOR(3 DOWNTO 0);-- 临时变量：解码后的键值
    VARIABLE any_v   : STD_LOGIC;                   -- 临时变量：是否有键按下
  BEGIN
    IF rising_edge(clk) THEN
      key_strobe <= '0';                            -- 默认无脉冲
      frame_pulse <= '0';                           -- 默认无帧脉冲

      IF reset = '1' THEN                           -- 复位逻辑
        div_cnt <= 0;
        row_idx <= 0;
        col_samples <= (OTHERS => (OTHERS => '1'));
        raw_any <= '0';
        raw_code <= (OTHERS => '0');
        stable_any <= '0';
        stable_code <= (OTHERS => '0');
        press_cnt <= 0;
        rel_cnt <= 0;
        key_down <= '0';
        key_val <= (OTHERS => '0');
      ELSE
        -- 1. 行扫描分频逻辑
        IF div_cnt = scan_div THEN                  -- 达到分频计数值
          div_cnt <= 0;

          -- 采样当前行的列输入 (active low)
          col_samples(row_idx) <= key_c;

          -- 切换到下一行
          IF row_idx = 3 THEN
            row_idx <= 0;
            frame_pulse <= '1';                     -- 完成一轮(4行)扫描，产生帧脉冲
          ELSE
            row_idx <= row_idx + 1;
          END IF;
        ELSE
          div_cnt <= div_cnt + 1;
        END IF;

        -- 2. 帧处理逻辑 (每扫描完一整轮执行一次)
        IF frame_pulse = '1' THEN
          found := FALSE;
          any_v := '0';
          code_v := (OTHERS => '0');

          -- 遍历4行4列的采样结果，寻找被按下的键 (低电平有效)
          FOR rr IN 0 TO 3 LOOP
            FOR cc IN 0 TO 3 LOOP
              -- 找到第一个低电平 (优先响应索引小的)
              IF col_samples(rr)(cc) = '0' AND (NOT found) THEN
                found := TRUE;
                any_v := '1';
                code_v := decode_key(rr, cc);       -- 获取键值
              END IF;
            END LOOP;
          END LOOP;

          raw_any <= any_v;
          raw_code <= code_v;

          -- 3. 消抖与边沿检测逻辑
          IF any_v = '1' THEN                       -- 检测到有键按下
            rel_cnt <= 0;                           -- 清零释放计数
            -- 如果按下键值稳定 (与上一次稳定状态一致)
            IF stable_any = '1' AND code_v = stable_code THEN
              IF press_cnt < debounce_cycles THEN   -- 累加按下计数器
                press_cnt <= press_cnt + 1;
              END IF;
            ELSE
              -- 键值改变或新按下，重置按键状态和计数
              stable_any <= '1';
              stable_code <= code_v;
              press_cnt <= 0;
            END IF;

            -- 如果之前未确认按下，且保持按下达到消抖周期
            IF key_down = '0' AND press_cnt = debounce_cycles THEN
              key_down <= '1';                      -- 标记键已按下
              key_val <= stable_code;               -- 更新输出键值
              key_strobe <= '1';                    -- 发送按键有效脉冲
            END IF;
          ELSE                                      -- 无键按下
            press_cnt <= 0;                         -- 清零按下计数
            IF key_down = '1' THEN                  -- 之前是按下状态
              IF rel_cnt < release_cycles THEN      -- 累加释放计数器
                rel_cnt <= rel_cnt + 1;
              END IF;
              IF rel_cnt = release_cycles THEN      -- 达到释放消抖周期
                key_down <= '0';                    -- 标记键已释放
                stable_any <= '0';
              END IF;
            ELSE
              stable_any <= '0';
              rel_cnt <= 0;
            END IF;
          END IF;
        END IF;
      END IF;
    END IF;
  END PROCESS;
END ARCHITECTURE;
