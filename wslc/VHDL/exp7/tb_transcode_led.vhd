library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity tb_transcode_led is
end entity;

architecture sim of tb_transcode_led is
  -- DUT ports
  signal code_input : std_logic_vector(3 downto 0) := (others => '0');
  signal code_valid : std_logic := '0';
  signal LEDC_a, LEDC_b, LEDC_c, LEDC_d : std_logic;
  signal LEDC_e, LEDC_f, LEDC_g, LEDC_dp : std_logic;
  signal LEDC1 : std_logic;

  constant Tstep : time := 1 us;

  -- Expected patterns for a..g,dp (low-active, '0' lights the segment)
  type rom_t is array (0 to 15) of std_logic_vector(7 downto 0);
  constant ROM : rom_t := (
    0  => "00000011", -- 0
    1  => "10011111", -- 1
    2  => "00100101", -- 2
    3  => "00001101", -- 3
    4  => "10011001", -- 4
    5  => "01001001", -- 5
    6  => "01000001", -- 6
    7  => "00011111", -- 7
    8  => "00000001", -- 8
    9  => "00001001", -- 9
    10 => "00010001", -- A
    11 => "11000001", -- b
    12 => "01100011", -- placeholder to keep index; will be overridden below
    13 => "10000101", -- d
    14 => "01100001", -- E
    15 => "01110001"  -- F
  );

  -- Because VHDL constant aggregates need literals at declaration,
  -- patch the "C" pattern after declaration for readability.
  -- We'll use a variable initialized in a process to avoid tool quirks.
  signal seg_vec : std_logic_vector(7 downto 0);
begin
  -- Instantiate DUT
  dut: entity work.transcode_led
    port map (
      code_input => code_input,
      code_valid => code_valid,
      LEDC_a => LEDC_a, LEDC_b => LEDC_b, LEDC_c => LEDC_c, LEDC_d => LEDC_d,
      LEDC_e => LEDC_e, LEDC_f => LEDC_f, LEDC_g => LEDC_g, LEDC_dp => LEDC_dp,
      LEDC1  => LEDC1
    );

  seg_vec <= LEDC_a & LEDC_b & LEDC_c & LEDC_d & LEDC_e & LEDC_f & LEDC_g & LEDC_dp;

  stim: process
    variable rom_local : rom_t := ROM;
  begin
    -- Patch C pattern: a d e f on, others off => "01100011"
    rom_local(12) := "01100011";

    -- Enable display and sweep 0..F
    code_valid <= '1';
    for i in 0 to 15 loop
      code_input <= std_logic_vector(to_unsigned(i, 4));
      wait for Tstep;
      assert seg_vec = rom_local(i)
        report "Mismatch at hex=" & integer'image(i) &
               " expected=" & rom_local(i) & " got=" & seg_vec
        severity error;
      assert LEDC1 = '0' report "LEDC1 should be low when valid=1" severity error;
    end loop;

    -- Gate off
    code_valid <= '0';
    wait for Tstep;
    assert seg_vec = (others => '1') report "Segments should be all high when valid=0" severity error;
    assert LEDC1 = '1' report "LEDC1 should be high (not selected) when valid=0" severity error;

    report "tb_transcode_led PASSED." severity note;
    wait;
  end process;
end architecture;
