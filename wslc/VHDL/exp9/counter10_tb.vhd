library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity counter10_tb is
end entity counter10_tb;

architecture arch_tb of counter10_tb is
  signal clk : std_logic := '0';
  signal clr : std_logic := '0';
  signal q   : std_logic_vector(3 downto 0);
  signal co  : std_logic;

  signal done : boolean := false;
begin
  -- clock generator
  clk <= not clk after 10 ns when not done else '0';

  uut : entity work.counter10
    port map(
      clk => clk,
      clr => clr,
      q   => q,
      co  => co
    );

  stimulus : process
    variable exp_cnt : unsigned(3 downto 0) := (others => '0');
    variable exp_co  : std_logic := '0';
  begin
    -- hold clear low for first edge
    wait until rising_edge(clk);
    assert q = "0000" and co = '0'
      report "counter not cleared at power-up" severity failure;

    -- release clear
    clr <= '1';

    -- run several cycles with counting and rollover check
    for i in 0 to 14 loop
      wait until rising_edge(clk);

      if clr = '0' then
        exp_cnt := (others => '0');
        exp_co  := '0';
      else
        if exp_cnt = "1001" then
          exp_cnt := (others => '0');
          exp_co  := '1';
        else
          exp_cnt := exp_cnt + 1;
          exp_co  := '0';
        end if;
      end if;

      assert q = std_logic_vector(exp_cnt)
        report "counter mismatch at cycle " & integer'image(i)
        severity failure;
      assert co = exp_co
        report "carry mismatch at cycle " & integer'image(i)
        severity failure;

      -- inject a synchronous clear midway
      if i = 6 then
        clr <= '0';
      elsif i = 7 then
        clr <= '1';
      end if;
    end loop;

    done <= true;
    wait for 20 ns;
    assert false report "counter10_tb finished" severity note;
    wait;
  end process;
end architecture arch_tb;
