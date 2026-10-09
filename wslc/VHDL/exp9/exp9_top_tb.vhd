LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY exp9_top_tb IS
END ENTITY exp9_top_tb;

ARCHITECTURE arch_tb OF exp9_top_tb IS
  SIGNAL clk : std_logic := '0';
  SIGNAL clr : std_logic := '0';
  SIGNAL si  : std_logic := '0';
  SIGNAL q   : std_logic_vector(3 DOWNTO 0);
  SIGNAL co  : std_logic;
  SIGNAL d   : std_logic_vector(6 DOWNTO 0);
  SIGNAL so  : std_logic;

  SIGNAL done : boolean := FALSE;
BEGIN
  -- 时钟：20 ns 周期
  clk <= NOT clk AFTER 10 ns WHEN NOT done ELSE '0';

  -- 顶层被测单元：同时例化 counter10 和 L_shifter8
  uut : ENTITY work.exp9_top
    PORT MAP(
      clk => clk,
      clr => clr,
      si  => si,
      q   => q,
      co  => co,
      d   => d,
      so  => so
    );

  stimulus : PROCESS
    SUBTYPE bit_arr IS std_logic_vector(6 DOWNTO 0);
    CONSTANT pattern : bit_arr := "1011001";

    VARIABLE exp_cnt : unsigned(3 DOWNTO 0) := (OTHERS => '0');
    VARIABLE exp_co  : std_logic := '0';
    VARIABLE exp_reg : std_logic_vector(6 DOWNTO 0) := (OTHERS => '0');
  BEGIN
    -- 初始：clr = '0'，第一次上升沿同步清零
    WAIT UNTIL rising_edge(clk);
    ASSERT q = "0000" AND co = '0'
      REPORT "counter10 not cleared at power-up"
      SEVERITY failure;
    ASSERT (d = "0000000") AND (so = '0')
      REPORT "l_shifter8 not cleared at power-up"
      SEVERITY failure;

    -- 释放清零，开始计数和移位
    clr <= '1';

    -- 连续 10 个时钟周期：
    --   前 7 拍向移位寄存器串行送入 pattern，
    --   同时检查 counter10 递增。
    FOR i IN 0 TO 9 LOOP
      IF i <= 6 THEN
        -- pattern 索引为 6,5,...,0（与 l_shifter8_tb 一致）
        si <= pattern(6 - i);
      ELSE
        si <= '0';
      END IF;

      WAIT UNTIL rising_edge(clk);

      -- 期望：counter10 0~9 计数，9 后回 0 并产生进位
      IF clr = '0' THEN
        exp_cnt := (OTHERS => '0');
        exp_co  := '0';
      ELSE
        IF exp_cnt = "1001" THEN
          exp_cnt := (OTHERS => '0');
          exp_co  := '1';
        ELSE
          exp_cnt := exp_cnt + 1;
          exp_co  := '0';
        END IF;
      END IF;

      ASSERT q = std_logic_vector(exp_cnt)
        REPORT "counter10 mismatch at cycle " & integer'image(i)
        SEVERITY failure;
      ASSERT co = exp_co
        REPORT "counter10 carry mismatch at cycle " & integer'image(i)
        SEVERITY failure;

      -- 期望：移位寄存器在 clr='1' 时左移串入 si
      IF clr = '0' THEN
        exp_reg := (OTHERS => '0');
      ELSIF i <= 6 THEN
        exp_reg := exp_reg(5 DOWNTO 0) & si;
      END IF;

      IF i <= 6 THEN
        ASSERT d = exp_reg
          REPORT "l_shifter8 parallel mismatch at step " & integer'image(i)
          SEVERITY failure;
        ASSERT so = exp_reg(6)
          REPORT "l_shifter8 serial mismatch at step " & integer'image(i)
          SEVERITY failure;
      END IF;
    END LOOP;

    -- 再打一拍，所有输出应保持不变
    si <= '0';
    WAIT UNTIL rising_edge(clk);
    ASSERT q = std_logic_vector(exp_cnt)
      REPORT "counter10 should hold when inputs steady"
      SEVERITY failure;
    ASSERT d = exp_reg AND so = exp_reg(6)
      REPORT "l_shifter8 should hold when inputs steady"
      SEVERITY failure;

    -- 再次同步清零
    clr <= '0';
    WAIT UNTIL rising_edge(clk);
    ASSERT q = "0000" AND co = '0'
      REPORT "counter10 failed to clear at end"
      SEVERITY failure;
    ASSERT (d = "0000000") AND (so = '0')
      REPORT "l_shifter8 failed to clear at end"
      SEVERITY failure;

    done <= TRUE;
    WAIT FOR 40 ns;
    ASSERT FALSE REPORT "exp9_top_tb finished" SEVERITY note;
    WAIT;
  END PROCESS;
END ARCHITECTURE arch_tb;
