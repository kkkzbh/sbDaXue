-- ff_d.vhd  同步置数 + 异步清零 D 触发器（clr 异步低有效；set 同步低有效）
library ieee;
use ieee.std_logic_1164.all;

entity ff_d is
  port (
    clk : in  std_logic;
    set : in  std_logic;   -- 同步置数，低有效
    clr : in  std_logic;   -- 异步清零，低有效
    d   : in  std_logic;
    q   : out std_logic;
    nq  : out std_logic
  );
end entity;

architecture rtl of ff_d is
  signal q_r : std_logic := '0';
begin
  process(clk, clr)               -- 异步清零必须进敏感表
  begin
    if clr = '0' then
      q_r <= '0';                 -- 立刻清零（异步）
    elsif rising_edge(clk) then
      if set = '0' then
        q_r <= '1';               -- 同步置数在时钟上升沿生效
      else
        q_r <= d;                 -- 常规 D 采样
      end if;
    end if;
  end process;

  q  <= q_r;
  nq <= not q_r;
end architecture;
