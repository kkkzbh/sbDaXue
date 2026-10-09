-- jd_d.vhd  顶层：同时实例化 ff_jk 与 ff_d
library ieee;
use ieee.std_logic_1164.all;

entity jd_d is
  port (
    clk      : in  std_logic;

    -- 给 ff_jk 的控制与数据
    clr_jk_n : in  std_logic;  -- 同步清零，低有效
    j        : in  std_logic;
    k        : in  std_logic;
    q_jk     : out std_logic;
    nq_jk    : out std_logic;

    -- 给 ff_d 的控制与数据
    set_d_n  : in  std_logic;  -- 同步置数，低有效
    clr_d_n  : in  std_logic;  -- 异步清零，低有效
    d        : in  std_logic;
    q_d      : out std_logic;
    nq_d     : out std_logic
  );
end entity;

architecture rtl of jd_d is
begin
  -- JK 触发器实例
  u_jk : entity work.ff_jk
    port map (
      clk => clk,
      clr => clr_jk_n,  -- 低有效同步清零
      j   => j,
      k   => k,
      q   => q_jk,
      nq  => nq_jk
    );

  -- D 触发器实例
  u_d : entity work.ff_d
    port map (
      clk => clk,
      set => set_d_n,   -- 低有效同步置数
      clr => clr_d_n,   -- 低有效异步清零
      d   => d,
      q   => q_d,
      nq  => nq_d
    );
end architecture;
