library ieee;
use ieee.std_logic_1164.all;

entity l_shifter8_tb is
end entity l_shifter8_tb;

architecture arch_tb of l_shifter8_tb is
  signal clk : std_logic := '0';
  signal clr : std_logic := '0';
  signal si  : std_logic := '0';
  signal d   : std_logic_vector(6 downto 0);
  signal so  : std_logic;

  signal done : boolean := false;
begin
  clk <= not clk after 10 ns when not done else '0';

  uut : entity work.L_shifter8
    port map(
      clk => clk,
      clr => clr,
      si  => si,
      d   => d,
      so  => so
    );

  stimulus : process
    subtype bit_arr is std_logic_vector(6 downto 0);
    constant pattern : bit_arr := "1011001"; -- bits shift in LSB-first
    variable exp_reg : std_logic_vector(6 downto 0) := (others => '0');
  begin
    -- apply synchronous clear on first edge
    wait until rising_edge(clk);
    assert d = (others => '0') and so = '0'
      report "register not cleared at reset" severity failure;

    clr <= '1';

    -- shift in pattern bits
    for i in pattern'range loop
      si <= pattern(i);
      wait until rising_edge(clk);

      exp_reg := exp_reg(5 downto 0) & pattern(i);

      assert d = exp_reg
        report "parallel output mismatch at step " & integer'image(i)
        severity failure;
      assert so = exp_reg(6)
        report "serial output mismatch at step " & integer'image(i)
        severity failure;
    end loop;

    -- hold to check maintain
    wait until rising_edge(clk);
    assert d = exp_reg and so = exp_reg(6)
      report "register should hold when inputs steady" severity failure;

    -- synchronous clear again
    clr <= '0';
    wait until rising_edge(clk);
    assert d = (others => '0') and so = '0'
      report "register failed to clear" severity failure;

    done <= true;
    wait for 20 ns;
    assert false report "l_shifter8_tb finished" severity note;
    wait;
  end process;
end architecture arch_tb;
