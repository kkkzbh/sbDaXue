-- led_matrix_2x2_hex.vhd
-- 2x2 矩阵LED点阵显示模块
-- 每个矩阵元素显示为单个十进制数字 (0-9)
-- 使用5x7点阵字体，居中显示在8x8单元格

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY led_matrix_2x2_hex IS
  GENERIC (
    scan_div : NATURAL := 2399  -- 24MHz/2400 = 10kHz row step
  );
  PORT (
    clk   : IN  STD_LOGIC;
    reset : IN  STD_LOGIC; -- active high

    v11   : IN  SIGNED(15 DOWNTO 0);
    v12   : IN  SIGNED(15 DOWNTO 0);
    v21   : IN  SIGNED(15 DOWNTO 0);
    v22   : IN  SIGNED(15 DOWNTO 0);

    row   : OUT STD_LOGIC_VECTOR(15 DOWNTO 0); -- active low
    col   : OUT STD_LOGIC_VECTOR(15 DOWNTO 0)  -- active low
  );
END ENTITY;

ARCHITECTURE rtl OF led_matrix_2x2_hex IS
  SUBTYPE slv4 IS STD_LOGIC_VECTOR(3 DOWNTO 0);
  SUBTYPE slv8 IS STD_LOGIC_VECTOR(7 DOWNTO 0);

  -- 5x7 font for single digit display (0-9), array sized to 16 to match 4-bit index
  TYPE font_t IS ARRAY (0 TO 15, 0 TO 6) OF slv8;

  -- Font with each row bit-reversed (mirrored horizontally)
  CONSTANT font5x7 : font_t := (
    -- 0: (symmetric, unchanged)
    ( "00111100","01000010","01000010","01000010","01000010","01000010","00111100" ),
    -- 1: bit-reversed
    ( "00010000","00011000","00010000","00010000","00010000","00010000","00111000" ),
    -- 2: bit-reversed
    ( "00111100","01000010","01000000","00111000","00000100","00000010","01111110" ),
    -- 3: bit-reversed
    ( "00111100","01000010","01000000","00111000","01000000","01000010","00111100" ),
    -- 4: bit-reversed
    ( "00100000","00110000","00101000","00100100","01111110","00100000","00100000" ),
    -- 5: bit-reversed
    ( "01111110","00000010","00111110","01000000","01000000","01000010","00111100" ),
    -- 6: bit-reversed
    ( "00111100","00000010","00111110","01000010","01000010","01000010","00111100" ),
    -- 7: bit-reversed
    ( "01111110","01000000","00100000","00010000","00001000","00001000","00001000" ),
    -- 8: (symmetric, unchanged)
    ( "00111100","01000010","01000010","00111100","01000010","01000010","00111100" ),
    -- 9: bit-reversed
    ( "00111100","01000010","01000010","01111100","01000000","01000010","00111100" ),
    -- 10-15: blank (unused, but needed for array sizing)
    ( "00000000","00000000","00000000","00000000","00000000","00000000","00000000" ),
    ( "00000000","00000000","00000000","00000000","00000000","00000000","00000000" ),
    ( "00000000","00000000","00000000","00000000","00000000","00000000","00000000" ),
    ( "00000000","00000000","00000000","00000000","00000000","00000000","00000000" ),
    ( "00000000","00000000","00000000","00000000","00000000","00000000","00000000" ),
    ( "00000000","00000000","00000000","00000000","00000000","00000000","00000000" )
  );

  SIGNAL div_cnt  : NATURAL RANGE 0 TO scan_div := 0;
  SIGNAL row_idx  : NATURAL RANGE 0 TO 15 := 0;

  -- Clamp to single digit 0-9
  FUNCTION sat_digit(x : SIGNED(15 DOWNTO 0)) RETURN UNSIGNED IS
    VARIABLE ax : SIGNED(15 DOWNTO 0);
    VARIABLE u  : UNSIGNED(3 DOWNTO 0);
  BEGIN
    IF x < 0 THEN
      ax := -x;
    ELSE
      ax := x;
    END IF;
    IF ax > TO_SIGNED(9, 16) THEN
      u := TO_UNSIGNED(9, 4);
    ELSE
      -- Use direct bit slicing instead of RESIZE to avoid losing bit 3
      u := UNSIGNED(ax(3 DOWNTO 0));
    END IF;
    RETURN u;
  END FUNCTION;

  -- Get a row of 8 bits for a single digit (0-9), centered in 8x8
  FUNCTION cell_row(digit : UNSIGNED(3 DOWNTO 0); r8 : NATURAL) RETURN slv8 IS
    VARIABLE d : INTEGER RANGE 0 TO 15;
    VARIABLE r : INTEGER RANGE 0 TO 6;
  BEGIN
    -- row 0 is blank top row
    IF r8 = 0 OR r8 > 7 THEN
      RETURN (OTHERS => '0');
    END IF;
    -- rows 1..7 map to font rows 0..6
    d := TO_INTEGER(digit);
    r := r8 - 1;
    -- Explicit case to avoid synthesis optimization issues
    CASE d IS
      WHEN 0 => RETURN font5x7(0, r);
      WHEN 1 => RETURN font5x7(1, r);
      WHEN 2 => RETURN font5x7(2, r);
      WHEN 3 => RETURN font5x7(3, r);
      WHEN 4 => RETURN font5x7(4, r);
      WHEN 5 => RETURN font5x7(5, r);
      WHEN 6 => RETURN font5x7(6, r);
      WHEN 7 => RETURN font5x7(7, r);
      WHEN 8 => RETURN font5x7(8, r);
      WHEN 9 => RETURN font5x7(9, r);
      WHEN OTHERS => RETURN (OTHERS => '0');
    END CASE;
  END FUNCTION;

BEGIN
  PROCESS(clk)
    VARIABLE pat : STD_LOGIC_VECTOR(15 DOWNTO 0);
    VARIABLE v11d, v12d, v21d, v22d : UNSIGNED(3 DOWNTO 0);
    VARIABLE row8 : NATURAL;
    VARIABLE left8, right8 : slv8;
  BEGIN
    IF rising_edge(clk) THEN
      IF reset = '1' THEN
        div_cnt <= 0;
        row_idx <= 0;
      ELSE
        IF div_cnt = scan_div THEN
          div_cnt <= 0;
          IF row_idx = 15 THEN
            row_idx <= 0;
          ELSE
            row_idx <= row_idx + 1;
          END IF;
        ELSE
          div_cnt <= div_cnt + 1;
        END IF;
      END IF;

      -- row select (active low)
      row <= (OTHERS => '1');
      row(row_idx) <= '0';

      -- Clamp each matrix element to single digit 0-9
      v11d := sat_digit(v11);
      v12d := sat_digit(v12);
      v21d := sat_digit(v21);
      v22d := sat_digit(v22);

      -- Layout:
      -- Top 8 rows:    v11 (left) | v12 (right)
      -- Bottom 8 rows: v21 (left) | v22 (right)
      IF row_idx < 8 THEN
        row8 := row_idx;
        left8 := cell_row(v11d, row8);
        right8 := cell_row(v12d, row8);
      ELSE
        row8 := row_idx - 8;
        left8 := cell_row(v21d, row8);
        right8 := cell_row(v22d, row8);
      END IF;

      pat := right8 & left8; -- bit15 is rightmost physically
      col <= NOT pat; -- active low columns
    END IF;
  END PROCESS;
END ARCHITECTURE;
