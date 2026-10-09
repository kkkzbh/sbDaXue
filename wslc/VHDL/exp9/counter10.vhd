-- counter10.vhd

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity counter10 is
  port(
    clk : in  std_logic;
    clr : in  std_logic;                    -- 同步低电平清零
    q   : out std_logic_vector(3 downto 0); -- 4 位并行输出
    co  : out std_logic                     -- 9→0 时产生进位脉冲
  );
end entity counter10;

architecture rtl of counter10 is
  signal cnt  : unsigned(3 downto 0) := (others => '0');
  signal co_r : std_logic := '0';
begin
  process(clk)
  begin
    if rising_edge(clk) then
      -- 同步清零，clr = '0' 时计数器清零，进位输出为 0
      if clr = '0' then
        cnt  <= (others => '0');
        co_r <= '0';
      else
        -- 正常计数：0~9，9 之后回 0，并在该拍 co=1
        if cnt = "1001" then               -- 9
          cnt  <= (others => '0');         -- 回到 0
          co_r <= '1';                     -- 该拍产生进位
        else
          cnt  <= cnt + 1;                 -- 递增
          co_r <= '0';                     -- 其它拍进位为 0
        end if;
      end if;
    end if;
  end process;

  q  <= std_logic_vector(cnt);
  co <= co_r;
end architecture rtl;
