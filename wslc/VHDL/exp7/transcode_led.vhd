-- transcode_led.vhd
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- 实体名按要求：transcode_led
entity transcode_led is
  port (
    code_input : in  std_logic_vector(3 downto 0);  -- 4位十六进制
    code_valid : in  std_logic;                     -- 1=有效；0=空/非法→不显示

    -- 段选线：共阳极，低电平点亮
    LEDC_a     : out std_logic;
    LEDC_b     : out std_logic;
    LEDC_c     : out std_logic;
    LEDC_d     : out std_logic;
    LEDC_e     : out std_logic;
    LEDC_f     : out std_logic;
    LEDC_g     : out std_logic;
    LEDC_dp    : out std_logic;

    -- 字选：低电平有效
    LEDC1      : out std_logic
  );
end entity;

architecture rtl of transcode_led is
  -- seg_n 位序为 a b c d e f g dp（左到右），'0' 表示点亮，'1' 表示熄灭
  signal seg_n_raw   : std_logic_vector(7 downto 0);
  signal seg_n_gated : std_logic_vector(7 downto 0);
begin
  -- 4位码到七段图样的查表（共阳极低有效）
  -- 0→F 的常见字形，dp 一律不点亮（'1'）
  with code_input select
    seg_n_raw <=
      "00000011" when "0000", -- 0 : a b c d e f 亮
      "10011111" when "0001", -- 1 : b c
      "00100101" when "0010", -- 2 : a b d e g
      "00001101" when "0011", -- 3 : a b c d g
      "10011001" when "0100", -- 4 : b c f g
      "01001001" when "0101", -- 5 : a c d f g
      "01000001" when "0110", -- 6 : a c d e f g
      "00011111" when "0111", -- 7 : a b c
      "00000001" when "1000", -- 8 : a b c d e f g
      "00001001" when "1001", -- 9 : a b c d f g
      "00010001" when "1010", -- A : a b c e f g
      "11000001" when "1011", -- b : c d e f g
      "01100011" when "1100", -- C : a d e f
      "10000101" when "1101", -- d : b c d e g
      "01100001" when "1110", -- E : a d e f g
      "01110001" when "1111", -- F : a e f g
      "11111111" when others; -- 兜底：全灭

  -- 有效信号门控：无效时整位熄灭
  seg_n_gated <= seg_n_raw when code_valid = '1' else (others => '1');

  -- 段线输出映射（注意位序）
  LEDC_a  <= seg_n_gated(7);
  LEDC_b  <= seg_n_gated(6);
  LEDC_c  <= seg_n_gated(5);
  LEDC_d  <= seg_n_gated(4);
  LEDC_e  <= seg_n_gated(3);
  LEDC_f  <= seg_n_gated(2);
  LEDC_g  <= seg_n_gated(1);
  LEDC_dp <= seg_n_gated(0);

  -- 字选：有效显示时拉低；无效时拉高（不选通）
  LEDC1   <= '0' when code_valid = '1' else '1';
end architecture;
