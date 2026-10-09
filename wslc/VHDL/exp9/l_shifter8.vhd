-- l_shifter8.vhd

library ieee;
use ieee.std_logic_1164.all;

entity L_shifter8 is
  port(
    clk : in  std_logic;
    clr : in  std_logic;  -- synchronous active-low clear
    si  : in  std_logic;  -- serial input (enters LSB)
    d   : out std_logic_vector(6 downto 0); -- parallel output
    so  : out std_logic                    -- serial output (current MSB)
  );
end entity L_shifter8;

architecture rtl of L_shifter8 is
  signal reg_q : std_logic_vector(6 downto 0) := (others => '0');
begin
  process(clk)
  begin
    if rising_edge(clk) then
      if clr = '0' then
        reg_q <= (others => '0');
      else
        reg_q <= reg_q(5 downto 0) & si;
      end if;
    end if;
  end process;

  d  <= reg_q;
  so <= reg_q(6);
end architecture rtl;
