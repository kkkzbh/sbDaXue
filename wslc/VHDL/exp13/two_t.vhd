--------------------------------------------------------------------------------
-- 实验13：蜂鸣器发音实验 (Buzzer Experiment)
-- 功能：循环播放“两只老虎”旋律
-- 平台：HDLE-2 (Cyclone III EP3C16Q240C8)
-- 时钟：24MHz (PIN_210)
-- 复位：低电平有效 (PIN_151, 需注意按键按下为低电平)
-- 输出：蜂鸣器 (PIN_174)
--------------------------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_unsigned.ALL;

ENTITY buzzer_play IS
    PORT (
        clk      : IN  STD_LOGIC; -- 24MHz system clock
        reset    : IN  STD_LOGIC; -- Reset button (active low)
        buzzer   : OUT STD_LOGIC  -- Buzzer output pin
    );
END buzzer_play;

ARCHITECTURE rtl OF buzzer_play IS
    -- Music definitions (Counts for 24MHz clock, toggle period)
    -- Formula: Count = 24,000,000 / (Freq * 2)
    CONSTANT NOTE_C4 : INTEGER := 45866; -- Do: 261.63Hz
    CONSTANT NOTE_D4 : INTEGER := 40863; -- Re: 293.66Hz
    CONSTANT NOTE_E4 : INTEGER := 36404; -- Mi: 329.63Hz
    CONSTANT NOTE_F4 : INTEGER := 34361; -- Fa: 349.23Hz
    CONSTANT NOTE_G4 : INTEGER := 30612; -- Sol: 392.00Hz
    CONSTANT NOTE_A4 : INTEGER := 27272; -- La: 440.00Hz
    CONSTANT NOTE_B4 : INTEGER := 24291; -- Si: 493.88Hz
    CONSTANT NOTE_REST : INTEGER := 0;   -- Silent/Rest

    -- Melody length
    CONSTANT NOTE_COUNT : INTEGER := 16;
    
    -- Array type for melody sequence
    TYPE note_array IS ARRAY (0 TO NOTE_COUNT-1) OF INTEGER;
    
    -- "Two Tigers" melody fragment: 
    -- 1 2 3 1 | 1 2 3 1 | 3 4 5 - | 3 4 5 -
    CONSTANT melody : note_array := (
        NOTE_C4, NOTE_D4, NOTE_E4, NOTE_C4, -- 两只老虎
        NOTE_C4, NOTE_D4, NOTE_E4, NOTE_C4, -- 两只老虎
        NOTE_E4, NOTE_F4, NOTE_G4, NOTE_REST, -- 跑得快
        NOTE_E4, NOTE_F4, NOTE_G4, NOTE_REST  -- 跑得快
    );

    -- Signals
    SIGNAL tone_div_cnt : INTEGER RANGE 0 TO 50000 := 0;    -- Frequency divider counter
    SIGNAL tone_period  : INTEGER RANGE 0 TO 50000 := 0;    -- Current tone toggle period
    SIGNAL buzzer_reg   : STD_LOGIC := '0';                 -- Buzzer output register
    
    SIGNAL tempo_cnt    : INTEGER RANGE 0 TO 12000000 := 0; -- Tempo counter (0.5s per note)
    SIGNAL note_index   : INTEGER RANGE 0 TO NOTE_COUNT-1 := 0; -- Current note index
    
BEGIN

    -- Process for note sequencing and tempo control
    PROCESS(clk, reset)
    BEGIN
        IF reset = '0' THEN -- Active low reset
            tempo_cnt <= 0;
            note_index <= 0;
            tone_period <= NOTE_REST;
        ELSIF rising_edge(clk) THEN
            -- Tempo timer (0.5s = 12,000,000 cycles at 24MHz)
            IF tempo_cnt >= 12000000 THEN 
                tempo_cnt <= 0;
                -- Move to next note
                IF note_index = NOTE_COUNT - 1 THEN
                    note_index <= 0;
                ELSE
                    note_index <= note_index + 1;
                END IF;
            ELSE
                tempo_cnt <= tempo_cnt + 1;
            END IF;
            
            -- Update tone period based on current note
            -- Small optimization: update only when changing notes could be cleaner, 
            -- but continuous assignment here is safe and simple in RTL.
            tone_period <= melody(note_index);
        END IF;
    END PROCESS;

    -- Process for sound generation (frequency division)
    PROCESS(clk, reset)
    BEGIN
        IF reset = '0' THEN
            tone_div_cnt <= 0;
            buzzer_reg <= '0';
        ELSIF rising_edge(clk) THEN
            IF tone_period = NOTE_REST THEN
                buzzer_reg <= '0'; -- Silence
                tone_div_cnt <= 0;
            ELSE
                if tone_div_cnt >= tone_period THEN
                    tone_div_cnt <= 0;
                    buzzer_reg <= NOT buzzer_reg; -- Toggle buzzer
                ELSE
                    tone_div_cnt <= tone_div_cnt + 1;
                END IF;
            END IF;
        END IF;
    END PROCESS;

    -- Output assignment
    buzzer <= buzzer_reg;

END rtl;
