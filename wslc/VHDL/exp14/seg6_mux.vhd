LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY seg6_mux IS
  GENERIC (
    scan_div : NATURAL := 4000  -- 24MHz/4000 ~= 6kHz scan step
  );
  PORT (
    clk   : IN  STD_LOGIC;
    reset : IN  STD_LOGIC; -- active high

    glyph0 : IN UNSIGNED(4 DOWNTO 0); -- rightmost digit (dig[0])
    glyph1 : IN UNSIGNED(4 DOWNTO 0);
    glyph2 : IN UNSIGNED(4 DOWNTO 0);
    glyph3 : IN UNSIGNED(4 DOWNTO 0);
    glyph4 : IN UNSIGNED(4 DOWNTO 0);
    glyph5 : IN UNSIGNED(4 DOWNTO 0); -- leftmost digit (dig[5])

    dp     : IN STD_LOGIC_VECTOR(5 DOWNTO 0); -- '0' lights dp (active low segment)

    seg    : OUT STD_LOGIC_VECTOR(7 DOWNTO 0); -- dp g f e d c b a (active low)
    dig    : OUT STD_LOGIC_VECTOR(5 DOWNTO 0)  -- active low
  );
END ENTITY;

ARCHITECTURE rtl OF seg6_mux IS
  CONSTANT GLYPH_BLANK : UNSIGNED(4 DOWNTO 0) := TO_UNSIGNED(16, 5);
  CONSTANT GLYPH_DASH  : UNSIGNED(4 DOWNTO 0) := TO_UNSIGNED(17, 5);
  CONSTANT GLYPH_r     : UNSIGNED(4 DOWNTO 0) := TO_UNSIGNED(18, 5);

  SIGNAL div_cnt   : NATURAL RANGE 0 TO scan_div := 0;
  SIGNAL scan_idx  : NATURAL RANGE 0 TO 5 := 0;

  FUNCTION encode(g : UNSIGNED(4 DOWNTO 0)) RETURN STD_LOGIC_VECTOR IS
    VARIABLE s : STD_LOGIC_VECTOR(6 DOWNTO 0); -- g f e d c b a (active low)
    VARIABLE gi : INTEGER;
  BEGIN
    gi := TO_INTEGER(g);
    -- active low segments: 0 lights segment
    CASE gi IS
      WHEN 0  => s := "1000000"; -- 0
      WHEN 1  => s := "1111001"; -- 1
      WHEN 2  => s := "0100100"; -- 2
      WHEN 3  => s := "0110000"; -- 3
      WHEN 4  => s := "0011001"; -- 4
      WHEN 5  => s := "0010010"; -- 5
      WHEN 6  => s := "0000010"; -- 6
      WHEN 7  => s := "1111000"; -- 7
      WHEN 8  => s := "0000000"; -- 8
      WHEN 9  => s := "0010000"; -- 9
      WHEN 10 => s := "0001000"; -- A
      WHEN 11 => s := "0000011"; -- b
      WHEN 12 => s := "1000110"; -- C
      WHEN 13 => s := "0100001"; -- d
      WHEN 14 => s := "0000110"; -- E
      WHEN 15 => s := "0001110"; -- F
      WHEN 17 => s := "0111111"; -- dash '-'
      WHEN 18 => s := "0101111"; -- r (approx)
      WHEN OTHERS => s := "1111111"; -- blank
    END CASE;
    RETURN s;
  END FUNCTION;

  FUNCTION sel_glyph(
    i : NATURAL;
    g0 : UNSIGNED(4 DOWNTO 0);
    g1 : UNSIGNED(4 DOWNTO 0);
    g2 : UNSIGNED(4 DOWNTO 0);
    g3 : UNSIGNED(4 DOWNTO 0);
    g4 : UNSIGNED(4 DOWNTO 0);
    g5 : UNSIGNED(4 DOWNTO 0)
  ) RETURN UNSIGNED IS
  BEGIN
    CASE i IS
      WHEN 0 => RETURN g0;
      WHEN 1 => RETURN g1;
      WHEN 2 => RETURN g2;
      WHEN 3 => RETURN g3;
      WHEN 4 => RETURN g4;
      WHEN OTHERS => RETURN g5;
    END CASE;
  END FUNCTION;

BEGIN
  PROCESS(clk)
    VARIABLE g : UNSIGNED(4 DOWNTO 0);
    VARIABLE seg7 : STD_LOGIC_VECTOR(6 DOWNTO 0);
    VARIABLE dp_bit : STD_LOGIC;
  BEGIN
    IF rising_edge(clk) THEN
      IF reset = '1' THEN
        div_cnt <= 0;
        scan_idx <= 0;
      ELSE
        IF div_cnt = scan_div THEN
          div_cnt <= 0;
          IF scan_idx = 5 THEN
            scan_idx <= 0;
          ELSE
            scan_idx <= scan_idx + 1;
          END IF;
        ELSE
          div_cnt <= div_cnt + 1;
        END IF;
      END IF;

      CASE scan_idx IS
        WHEN 0 => dig <= "111110";
        WHEN 1 => dig <= "111101";
        WHEN 2 => dig <= "111011";
        WHEN 3 => dig <= "110111";
        WHEN 4 => dig <= "101111";
        WHEN OTHERS => dig <= "011111";
      END CASE;

      g := sel_glyph(scan_idx, glyph0, glyph1, glyph2, glyph3, glyph4, glyph5);
      seg7 := encode(g);
      dp_bit := dp(scan_idx);
      seg <= dp_bit & seg7; -- dp + (g..a)
    END IF;
  END PROCESS;
END ARCHITECTURE;

