-- top
library ieee;
use ieee.std_logic_1164.all;

-- 顶层：同时例化 counter10 和 L_shifter8
-- 用于手动仿真（University Program VWF）或在一块板上观察两个电路
ENTITY exp9_top IS
  PORT(
    clk : IN  std_logic;
    clr : IN  std_logic;
    si  : IN  std_logic;                     -- 送给移位寄存器的串行输入
    q   : OUT std_logic_vector(3 DOWNTO 0);  -- counter10 并行输出
    co  : OUT std_logic;                     -- counter10 进位输出
    d   : OUT std_logic_vector(6 DOWNTO 0);  -- L_shifter8 并行输出
    so  : OUT std_logic                      -- L_shifter8 串行输出
  );
END ENTITY exp9_top;

ARCHITECTURE rtl OF exp9_top IS
BEGIN
  -- 十进制计数器
  u_counter10 : ENTITY work.counter10
    PORT MAP(
      clk => clk,
      clr => clr,
      q   => q,
      co  => co
    );

  -- 7 位逻辑左移寄存器
  u_l_shifter8 : ENTITY work.L_shifter8
    PORT MAP(
      clk => clk,
      clr => clr,
      si  => si,
      d   => d,
      so  => so
    );
END ARCHITECTURE rtl;

