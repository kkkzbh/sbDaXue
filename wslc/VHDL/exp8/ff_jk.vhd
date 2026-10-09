-- ff_jk.vhd  同步清零 JK 触发器（clr 低有效，rising_edge 同步）
library ieee;
use ieee.std_logic_1164.all;

entity ff_jk is
  port (
    clk : in  std_logic;
    clr : in  std_logic;   -- 同步清零，低有效
    j   : in  std_logic;
    k   : in  std_logic;
    q   : out std_logic;
    nq  : out std_logic
  );
end entity;

architecture rtl of ff_jk is
  signal q_r : std_logic := '0';
begin
  process(clk)
  begin
    if rising_edge(clk) then
      if clr = '0' then
        q_r <= '0';                  -- 同步清零
      else
        case std_logic_vector'(j & k) is
          when "00" => null;         -- 保持（不赋值即保持）
          when "01" => q_r <= '0';   -- 复位
          when "10" => q_r <= '1';   -- 置位
          when "11" => q_r <= not q_r; -- 翻转
          when others => null;
        end case;
      end if;
    end if;
  end process;

  q  <= q_r;
  nq <= not q_r;
end architecture;
