LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY key_scanner_tb IS
END ENTITY;

ARCHITECTURE arch_tb OF key_scanner_tb IS
  SIGNAL clk        : STD_LOGIC := '0';
  SIGNAL reset      : STD_LOGIC := '1';
  SIGNAL key_r      : STD_LOGIC_VECTOR(3 DOWNTO 0);
  SIGNAL key_c      : STD_LOGIC_VECTOR(3 DOWNTO 0) := (OTHERS => '1');
  SIGNAL key_strobe : STD_LOGIC;
  SIGNAL key_val    : STD_LOGIC_VECTOR(3 DOWNTO 0);

  SIGNAL press_en   : STD_LOGIC := '0';
  CONSTANT press_row : NATURAL := 1; -- row1 col1 => key '5'
  CONSTANT press_col : NATURAL := 1;
BEGIN
  clk <= NOT clk AFTER 10 ns;

  u : ENTITY work.key_scanner
    GENERIC MAP (
      scan_div        => 1,
      debounce_cycles => 2,
      release_cycles  => 1
    )
    PORT MAP (
      clk        => clk,
      reset      => reset,
      key_r      => key_r,
      key_c      => key_c,
      key_strobe => key_strobe,
      key_val    => key_val
    );

  -- emulate key press: when selected row is driven low, pull selected column low
  PROCESS(key_r, press_en)
  BEGIN
    key_c <= (OTHERS => '1');
    IF press_en = '1' THEN
      IF key_r(press_row) = '0' THEN
        key_c(press_col) <= '0';
      END IF;
    END IF;
  END PROCESS;

  stimulus : PROCESS
  BEGIN
    WAIT FOR 200 ns;
    reset <= '0';

    WAIT FOR 200 ns;
    press_en <= '1';
    WAIT FOR 5 us;
    press_en <= '0';

    WAIT FOR 5 us;
    REPORT "key_scanner_tb done" SEVERITY NOTE;
    WAIT;
  END PROCESS;

  checker : PROCESS(clk)
  BEGIN
    IF rising_edge(clk) THEN
      IF key_strobe = '1' THEN
        ASSERT key_val = STD_LOGIC_VECTOR(TO_UNSIGNED(5, 4))
          REPORT "Expected key 5" SEVERITY FAILURE;
      END IF;
    END IF;
  END PROCESS;
END ARCHITECTURE;
