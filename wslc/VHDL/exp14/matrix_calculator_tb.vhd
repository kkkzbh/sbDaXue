LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY matrix_calculator_tb IS
END ENTITY;

ARCHITECTURE arch_tb OF matrix_calculator_tb IS
  SIGNAL clk        : STD_LOGIC := '0';
  SIGNAL reset      : STD_LOGIC := '1';
  SIGNAL key_strobe : STD_LOGIC := '0';
  SIGNAL key_val    : STD_LOGIC_VECTOR(3 DOWNTO 0) := (OTHERS => '0');

  SIGNAL edit_is_a  : STD_LOGIC;
  SIGNAL in_single  : STD_LOGIC;
  SIGNAL in_result  : STD_LOGIC;
  SIGNAL cursor_idx : UNSIGNED(1 DOWNTO 0);

  SIGNAL a11,a12,a21,a22 : SIGNED(15 DOWNTO 0);
  SIGNAL b11,b12,b21,b22 : SIGNED(15 DOWNTO 0);
  SIGNAL m11,m12,m21,m22 : SIGNED(15 DOWNTO 0);

  SIGNAL scalar_valid : STD_LOGIC;
  SIGNAL scalar_value : SIGNED(31 DOWNTO 0);

  PROCEDURE press(
    SIGNAL ks : OUT STD_LOGIC;
    SIGNAL kv : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
    SIGNAL c  : IN  STD_LOGIC;
    CONSTANT v : IN INTEGER
  ) IS
  BEGIN
    kv <= STD_LOGIC_VECTOR(TO_UNSIGNED(v, 4));
    ks <= '1';
    WAIT UNTIL rising_edge(c);
    ks <= '0';
    WAIT UNTIL rising_edge(c);
  END PROCEDURE;
BEGIN
  clk <= NOT clk AFTER 10 ns;

  u : ENTITY work.matrix_calculator
    PORT MAP (
      clk          => clk,
      reset        => reset,
      key_strobe   => key_strobe,
      key_val      => key_val,
      edit_is_a    => edit_is_a,
      in_single    => in_single,
      in_result    => in_result,
      a11          => a11,
      a12          => a12,
      a21          => a21,
      a22          => a22,
      b11          => b11,
      b12          => b12,
      b21          => b21,
      b22          => b22,
      m11          => m11,
      m12          => m12,
      m21          => m21,
      m22          => m22,
      cursor_idx   => cursor_idx,
      scalar_valid => scalar_valid,
      scalar_value => scalar_value
    );

  stimulus : PROCESS
  BEGIN
    WAIT FOR 100 ns;
    reset <= '0';

    -- input A: 1 2 3 4
    press(key_strobe, key_val, clk, 1); press(key_strobe, key_val, clk, 2); press(key_strobe, key_val, clk, 3); press(key_strobe, key_val, clk, 4);
    ASSERT a11 = TO_SIGNED(1, 16) AND a12 = TO_SIGNED(2, 16) AND a21 = TO_SIGNED(3, 16) AND a22 = TO_SIGNED(4, 16)
      REPORT "A input failed" SEVERITY FAILURE;

    -- toggle to B
    press(key_strobe, key_val, clk, 13);
    ASSERT edit_is_a = '0' REPORT "Expected editing B" SEVERITY FAILURE;

    -- input B: 5 6 7 8
    press(key_strobe, key_val, clk, 5); press(key_strobe, key_val, clk, 6); press(key_strobe, key_val, clk, 7); press(key_strobe, key_val, clk, 8);
    ASSERT b11 = TO_SIGNED(5, 16) AND b12 = TO_SIGNED(6, 16) AND b21 = TO_SIGNED(7, 16) AND b22 = TO_SIGNED(8, 16)
      REPORT "B input failed" SEVERITY FAILURE;

    -- A+B
    press(key_strobe, key_val, clk, 11);
    ASSERT in_result = '1' REPORT "Expected result view" SEVERITY FAILURE;
    ASSERT m11 = TO_SIGNED(6, 16) AND m12 = TO_SIGNED(8, 16) AND m21 = TO_SIGNED(10, 16) AND m22 = TO_SIGNED(12, 16)
      REPORT "A+B wrong" SEVERITY FAILURE;

    -- back to edit
    press(key_strobe, key_val, clk, 13);
    ASSERT in_result = '0' REPORT "Expected back to edit" SEVERITY FAILURE;

    -- A*B
    press(key_strobe, key_val, clk, 12);
    ASSERT in_result = '1' REPORT "Expected result view after multiply" SEVERITY FAILURE;
    ASSERT m11 = TO_SIGNED(19, 16) AND m12 = TO_SIGNED(22, 16) AND m21 = TO_SIGNED(43, 16) AND m22 = TO_SIGNED(50, 16)
      REPORT "A*B wrong" SEVERITY FAILURE;

    -- back to edit and enter single mode on A
    press(key_strobe, key_val, clk, 13);
    IF edit_is_a = '0' THEN
      press(key_strobe, key_val, clk, 13); -- toggle back to A if needed
    END IF;
    press(key_strobe, key_val, clk, 10); -- MODE
    ASSERT in_single = '1' REPORT "Expected single mode" SEVERITY FAILURE;

    -- DET(A) = 1*4 - 2*3 = -2
    press(key_strobe, key_val, clk, 12);
    ASSERT scalar_valid = '1' AND scalar_value = TO_SIGNED(-2, 32)
      REPORT "DET wrong" SEVERITY FAILURE;

    -- NOR = sumsq(AT*A) = 892 for A=[[1,2],[3,4]]
    press(key_strobe, key_val, clk, 15);
    ASSERT scalar_valid = '1' AND scalar_value = TO_SIGNED(892, 32)
      REPORT "NOR wrong" SEVERITY FAILURE;

    -- POW: A^3 => [[37,54],[81,118]]
    press(key_strobe, key_val, clk, 11); -- enter pow
    press(key_strobe, key_val, clk, 3);  -- exponent
    press(key_strobe, key_val, clk, 15); -- OK
    -- wait for multi-cycle pow to finish
    FOR i IN 0 TO 30 LOOP
      WAIT UNTIL rising_edge(clk);
    END LOOP;
    ASSERT a11 = TO_SIGNED(37, 16) AND a12 = TO_SIGNED(54, 16) AND a21 = TO_SIGNED(81, 16) AND a22 = TO_SIGNED(118, 16)
      REPORT "POW wrong" SEVERITY FAILURE;

    -- EXIT to normal
    press(key_strobe, key_val, clk, 13);
    press(key_strobe, key_val, clk, 13);
    ASSERT in_single = '0' REPORT "Expected normal mode" SEVERITY FAILURE;

    WAIT FOR 200 ns;
    REPORT "matrix_calculator_tb done" SEVERITY NOTE;
    WAIT;
  END PROCESS;
END ARCHITECTURE;
