-- matrix_calculator.vhd
-- 矩阵计算核心模块
-- 支持2x2矩阵的编辑、加法、乘法、转置、行列式、幂运算等功能

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY matrix_calculator IS
  PORT (
    clk          : IN  STD_LOGIC;
    reset        : IN  STD_LOGIC;  -- active high
    key_strobe   : IN  STD_LOGIC;
    key_val      : IN  STD_LOGIC_VECTOR(3 DOWNTO 0);

    edit_is_a    : OUT STD_LOGIC;  -- '1' editing A, '0' editing B
    in_single    : OUT STD_LOGIC;  -- single-matrix mode
    in_result    : OUT STD_LOGIC;  -- showing result matrix

    a11          : OUT SIGNED(15 DOWNTO 0);
    a12          : OUT SIGNED(15 DOWNTO 0);
    a21          : OUT SIGNED(15 DOWNTO 0);
    a22          : OUT SIGNED(15 DOWNTO 0);
    b11          : OUT SIGNED(15 DOWNTO 0);
    b12          : OUT SIGNED(15 DOWNTO 0);
    b21          : OUT SIGNED(15 DOWNTO 0);
    b22          : OUT SIGNED(15 DOWNTO 0);

    m11          : OUT SIGNED(15 DOWNTO 0); -- matrix currently displayed on LED matrix
    m12          : OUT SIGNED(15 DOWNTO 0);
    m21          : OUT SIGNED(15 DOWNTO 0);
    m22          : OUT SIGNED(15 DOWNTO 0);

    cursor_idx   : OUT UNSIGNED(1 DOWNTO 0); -- 0..3 for edit position

    scalar_valid : OUT STD_LOGIC;
    scalar_value : OUT SIGNED(31 DOWNTO 0)
  );
END ENTITY;

ARCHITECTURE rtl OF matrix_calculator IS
  TYPE mode_t IS (mode_edit, mode_single, mode_pow, mode_pow_run, mode_view);

  TYPE mat2_t IS RECORD
    e11 : SIGNED(15 DOWNTO 0);
    e12 : SIGNED(15 DOWNTO 0);
    e21 : SIGNED(15 DOWNTO 0);
    e22 : SIGNED(15 DOWNTO 0);
  END RECORD;

  SIGNAL mode            : mode_t := mode_edit;
  SIGNAL edit_a          : STD_LOGIC := '1';
  SIGNAL cur_idx         : UNSIGNED(1 DOWNTO 0) := (OTHERS => '0');

  SIGNAL a11_r, a12_r, a21_r, a22_r : SIGNED(15 DOWNTO 0) := (OTHERS => '0');
  SIGNAL b11_r, b12_r, b21_r, b22_r : SIGNED(15 DOWNTO 0) := (OTHERS => '0');

  SIGNAL r11, r12, r21, r22         : SIGNED(15 DOWNTO 0) := (OTHERS => '0');
  SIGNAL scalar_v                   : SIGNED(31 DOWNTO 0) := (OTHERS => '0');
  SIGNAL scalar_ok                  : STD_LOGIC := '0';

  SIGNAL pow_exp                    : NATURAL RANGE 1 TO 9 := 1;
  SIGNAL pow_e_u                    : UNSIGNED(3 DOWNTO 0) := (OTHERS => '0');
  SIGNAL pow_r                      : mat2_t;
  SIGNAL pow_b                      : mat2_t;

  TYPE pow_phase_t IS (pow_mul, pow_square);
  SIGNAL pow_phase                  : pow_phase_t := pow_mul;

  FUNCTION clamp16(x : SIGNED(31 DOWNTO 0)) RETURN SIGNED IS
    VARIABLE y : SIGNED(15 DOWNTO 0);
  BEGIN
    -- simple truncation (keeps lower 16 bits); for this lab scale it's OK
    y := RESIZE(x, 16);
    RETURN y;
  END FUNCTION;

  FUNCTION mat_mul(x : mat2_t; y : mat2_t) RETURN mat2_t IS
    VARIABLE t11, t12, t21, t22 : SIGNED(31 DOWNTO 0);
    VARIABLE o : mat2_t;
  BEGIN
    -- 16b * 16b => 32b (avoid 32b*32b overflow in simulation)
    t11 := RESIZE(x.e11 * y.e11, 32) + RESIZE(x.e12 * y.e21, 32);
    t12 := RESIZE(x.e11 * y.e12, 32) + RESIZE(x.e12 * y.e22, 32);
    t21 := RESIZE(x.e21 * y.e11, 32) + RESIZE(x.e22 * y.e21, 32);
    t22 := RESIZE(x.e21 * y.e12, 32) + RESIZE(x.e22 * y.e22, 32);
    o.e11 := clamp16(t11);
    o.e12 := clamp16(t12);
    o.e21 := clamp16(t21);
    o.e22 := clamp16(t22);
    RETURN o;
  END FUNCTION;

BEGIN
  edit_is_a <= edit_a;
  in_single <= '1' WHEN (mode = mode_single OR mode = mode_pow OR mode = mode_pow_run) ELSE '0';
  in_result <= '1' WHEN mode = mode_view ELSE '0';
  cursor_idx <= cur_idx;

  a11 <= a11_r; a12 <= a12_r; a21 <= a21_r; a22 <= a22_r;
  b11 <= b11_r; b12 <= b12_r; b21 <= b21_r; b22 <= b22_r;
  scalar_value <= scalar_v;
  scalar_valid <= scalar_ok;

  PROCESS(mode, edit_a, a11_r, a12_r, a21_r, a22_r, b11_r, b12_r, b21_r, b22_r, r11, r12, r21, r22)
  BEGIN
    IF mode = mode_view THEN
      m11 <= r11; m12 <= r12; m21 <= r21; m22 <= r22;
    ELSE
      IF edit_a = '1' THEN
        m11 <= a11_r; m12 <= a12_r; m21 <= a21_r; m22 <= a22_r;
      ELSE
        m11 <= b11_r; m12 <= b12_r; m21 <= b21_r; m22 <= b22_r;
      END IF;
    END IF;
  END PROCESS;

  PROCESS(clk)
    VARIABLE kv : INTEGER;
    VARIABLE det_v : SIGNED(31 DOWNTO 0);
    VARIABLE p : SIGNED(31 DOWNTO 0);
    VARIABLE x, y, o : mat2_t;
    VARIABLE swap_tmp : SIGNED(15 DOWNTO 0);
  BEGIN
    IF rising_edge(clk) THEN
      IF reset = '1' THEN
        mode <= mode_edit;
        edit_a <= '1';
        cur_idx <= (OTHERS => '0');
        a11_r <= (OTHERS => '0'); a12_r <= (OTHERS => '0'); a21_r <= (OTHERS => '0'); a22_r <= (OTHERS => '0');
        b11_r <= (OTHERS => '0'); b12_r <= (OTHERS => '0'); b21_r <= (OTHERS => '0'); b22_r <= (OTHERS => '0');
        r11 <= (OTHERS => '0'); r12 <= (OTHERS => '0'); r21 <= (OTHERS => '0'); r22 <= (OTHERS => '0');
        scalar_v <= (OTHERS => '0');
        scalar_ok <= '0';
        pow_exp <= 1;
        pow_e_u <= (OTHERS => '0');
        pow_r <= (e11 => (OTHERS => '0'), e12 => (OTHERS => '0'), e21 => (OTHERS => '0'), e22 => (OTHERS => '0'));
        pow_b <= (e11 => (OTHERS => '0'), e12 => (OTHERS => '0'), e21 => (OTHERS => '0'), e22 => (OTHERS => '0'));
        pow_phase <= pow_mul;
      ELSE
        -- scalar_ok 保持不变，直到用户再次按 C 退出

        -- multi-cycle POW engine (runs without key presses)
        IF mode = mode_pow_run THEN
          IF pow_e_u = TO_UNSIGNED(0, 4) THEN
            IF edit_a = '1' THEN
              a11_r <= pow_r.e11; a12_r <= pow_r.e12; a21_r <= pow_r.e21; a22_r <= pow_r.e22;
            ELSE
              b11_r <= pow_r.e11; b12_r <= pow_r.e12; b21_r <= pow_r.e21; b22_r <= pow_r.e22;
            END IF;
            mode <= mode_single;
          ELSE
            CASE pow_phase IS
              WHEN pow_mul =>
                IF pow_e_u(0) = '1' THEN
                  pow_r <= mat_mul(pow_r, pow_b);
                END IF;
                pow_phase <= pow_square;
              WHEN OTHERS =>
                pow_b <= mat_mul(pow_b, pow_b);
                pow_e_u <= '0' & pow_e_u(3 DOWNTO 1);
                pow_phase <= pow_mul;
            END CASE;
          END IF;
        END IF;

        IF key_strobe = '1' THEN
          kv := TO_INTEGER(UNSIGNED(key_val));

          CASE mode IS
            WHEN mode_edit =>
              -- A=MODE (enter single), B=+, C=*, D=BACK (toggle A/B or exit result view)
              IF kv = 10 THEN
                mode <= mode_single;
              ELSIF kv = 11 THEN
                -- r = A + B
                r11 <= RESIZE(a11_r + b11_r, 16);
                r12 <= RESIZE(a12_r + b12_r, 16);
                r21 <= RESIZE(a21_r + b21_r, 16);
                r22 <= RESIZE(a22_r + b22_r, 16);
                mode <= mode_view;
              ELSIF kv = 12 THEN
                -- r = A * B
                x := (e11 => a11_r, e12 => a12_r, e21 => a21_r, e22 => a22_r);
                y := (e11 => b11_r, e12 => b12_r, e21 => b21_r, e22 => b22_r);
                o := mat_mul(x, y);
                r11 <= o.e11; r12 <= o.e12; r21 <= o.e21; r22 <= o.e22;
                mode <= mode_view;
              ELSIF kv = 13 THEN
                -- toggle edit matrix
                edit_a <= NOT edit_a;
              ELSIF kv >= 0 AND kv <= 9 THEN
                -- digit input into selected matrix, sequential cursor
                IF edit_a = '1' THEN
                  CASE TO_INTEGER(cur_idx) IS
                    WHEN 0 => a11_r <= TO_SIGNED(kv, 16);
                    WHEN 1 => a12_r <= TO_SIGNED(kv, 16);
                    WHEN 2 => a21_r <= TO_SIGNED(kv, 16);
                    WHEN OTHERS => a22_r <= TO_SIGNED(kv, 16);
                  END CASE;
                ELSE
                  CASE TO_INTEGER(cur_idx) IS
                    WHEN 0 => b11_r <= TO_SIGNED(kv, 16);
                    WHEN 1 => b12_r <= TO_SIGNED(kv, 16);
                    WHEN 2 => b21_r <= TO_SIGNED(kv, 16);
                    WHEN OTHERS => b22_r <= TO_SIGNED(kv, 16);
                  END CASE;
                END IF;
                cur_idx <= cur_idx + 1;
              END IF;

            WHEN mode_view =>
              -- D returns to edit, A enters single (on current edit matrix)
              IF kv = 13 THEN
                mode <= mode_edit;
              ELSIF kv = 10 THEN
                mode <= mode_single;
              END IF;

            WHEN mode_single =>
              -- A=T, B=POW, C=DET, D=EXIT, #=NOR
              IF kv = 13 THEN
                mode <= mode_edit;
                scalar_ok <= '0';
              ELSIF kv = 10 THEN
                -- transpose in place
                IF edit_a = '1' THEN
                  swap_tmp := a12_r;
                  a12_r <= a21_r;
                  a21_r <= swap_tmp;
                ELSE
                  swap_tmp := b12_r;
                  b12_r <= b21_r;
                  b21_r <= swap_tmp;
                END IF;
              ELSIF kv = 11 THEN
                mode <= mode_pow;
                pow_exp <= 1;
                scalar_ok <= '0';
              ELSIF kv = 12 THEN
                -- determinant: 按 C 切换显示
                IF scalar_ok = '1' THEN
                  -- 已在显示结果，再按 C 退出
                  scalar_ok <= '0';
                ELSE
                  -- 计算并显示行列式
                  IF edit_a = '1' THEN
                    det_v := RESIZE(a11_r * a22_r, 32) - RESIZE(a12_r * a21_r, 32);
                  ELSE
                    det_v := RESIZE(b11_r * b22_r, 32) - RESIZE(b12_r * b21_r, 32);
                  END IF;
                  scalar_v <= det_v;
                  scalar_ok <= '1';
                END IF;
              ELSIF kv = 15 THEN
                -- norm: sum of squares of all elements of (A^T * A)
                IF edit_a = '1' THEN
                  x := (e11 => a11_r, e12 => a21_r, e21 => a12_r, e22 => a22_r); -- A^T
                  y := (e11 => a11_r, e12 => a12_r, e21 => a21_r, e22 => a22_r); -- A
                ELSE
                  x := (e11 => b11_r, e12 => b21_r, e21 => b12_r, e22 => b22_r); -- B^T
                  y := (e11 => b11_r, e12 => b12_r, e21 => b21_r, e22 => b22_r); -- B
                END IF;
                o := mat_mul(x, y);
                p := RESIZE(o.e11 * o.e11, 32)
                   + RESIZE(o.e12 * o.e12, 32)
                   + RESIZE(o.e21 * o.e21, 32)
                   + RESIZE(o.e22 * o.e22, 32);
                scalar_v <= p;
                scalar_ok <= '1';
              END IF;

            WHEN mode_pow =>
              -- 1..9 sets exponent, #=OK applies, D=EXIT
              IF kv = 13 THEN
                mode <= mode_single;
              ELSIF kv >= 1 AND kv <= 9 THEN
                pow_exp <= kv;
              ELSIF kv = 15 THEN
                pow_r <= (e11 => TO_SIGNED(1, 16), e12 => TO_SIGNED(0, 16), e21 => TO_SIGNED(0, 16), e22 => TO_SIGNED(1, 16));
                IF edit_a = '1' THEN
                  pow_b <= (e11 => a11_r, e12 => a12_r, e21 => a21_r, e22 => a22_r);
                ELSE
                  pow_b <= (e11 => b11_r, e12 => b12_r, e21 => b21_r, e22 => b22_r);
                END IF;
                pow_e_u <= TO_UNSIGNED(pow_exp, 4);
                pow_phase <= pow_mul;
                mode <= mode_pow_run;
              END IF;
            WHEN mode_pow_run =>
              NULL;
          END CASE;
        END IF;
      END IF;
    END IF;
  END PROCESS;
END ARCHITECTURE;
