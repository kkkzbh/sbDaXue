--------------------------------------------------------------------------------
-- 实验：超级玛丽 (Super Mario Bros) 完整版 [修正版] - Adapted for buzzer_play
-- 平台：HDLE-2 (Cyclone III EP3C16Q240C8)
-- 时钟：24MHz
-- 输出：PIN_174 (Buzzer)
--------------------------------------------------------------------------------

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_unsigned.ALL;

ENTITY buzzer_play IS
    PORT (
        clk      : IN  STD_LOGIC; -- 24MHz system clock
        reset    : IN  STD_LOGIC; -- Reset button (active high)
        buzzer   : OUT STD_LOGIC  -- Buzzer output pin
    );
END buzzer_play;

ARCHITECTURE rtl OF buzzer_play IS
    -- =========================================================
    -- 1. 音符频率常量定义 (基于 24MHz 时钟)
    -- Formula: Count = 12,000,000 / Freq (Note: Logic toggles, so Freq = 24M / (2*Count))
    -- =========================================================
    -- 低音/中音区
    CONSTANT NOTE_G3  : INTEGER := 61224; -- 196Hz
    CONSTANT NOTE_C4  : INTEGER := 45866; -- 261Hz
    CONSTANT NOTE_E4  : INTEGER := 36404; -- 329Hz
    CONSTANT NOTE_F4  : INTEGER := 34361; -- 349Hz
    CONSTANT NOTE_G4  : INTEGER := 30612; -- 392Hz
    CONSTANT NOTE_A4  : INTEGER := 27272; -- 440Hz
    CONSTANT NOTE_AS4 : INTEGER := 25751; -- 466Hz (A# / Bb)
    CONSTANT NOTE_B4  : INTEGER := 24291; -- 493Hz
    
    -- 高音区 (马里奥主要在这里)
    CONSTANT NOTE_C5  : INTEGER := 22944; -- 523Hz
    CONSTANT NOTE_D5  : INTEGER := 20443; -- 587Hz
    CONSTANT NOTE_E5  : INTEGER := 18209; -- 659Hz
    CONSTANT NOTE_F5  : INTEGER := 17180; -- 698Hz
    CONSTANT NOTE_G5  : INTEGER := 15306; -- 783Hz
    CONSTANT NOTE_A5  : INTEGER := 13636; -- 880Hz
    CONSTANT NOTE_B5  : INTEGER := 12148; -- 987Hz
    CONSTANT NOTE_C6  : INTEGER := 11472; -- 1046Hz
    
    -- 【修正点】统一命名为 NOTE_REST
    CONSTANT NOTE_REST : INTEGER := 0;    

    -- =========================================================
    -- 2. 乐谱数据 (Intro + Main Theme)
    -- =========================================================
    CONSTANT SONG_LENGTH : INTEGER := 62; -- 音符总数
    
    TYPE melody_array IS ARRAY (0 TO SONG_LENGTH-1) OF INTEGER;
    TYPE rhythm_array IS ARRAY (0 TO SONG_LENGTH-1) OF INTEGER;

    -- 旋律数组
    CONSTANT melody : melody_array := (
        -- [Intro] 登 登 登... 登... 登... 登!
        NOTE_E5, NOTE_E5, NOTE_REST, NOTE_E5, 
        NOTE_REST, NOTE_C5, NOTE_E5, NOTE_REST,
        NOTE_G5, NOTE_REST, NOTE_G4, NOTE_REST,

        -- [Main Theme Section A] 
        NOTE_C5, NOTE_REST, NOTE_G4, NOTE_REST, NOTE_E4, NOTE_REST,
        NOTE_A4, NOTE_REST, NOTE_B4, NOTE_REST, NOTE_AS4, NOTE_A4,
        NOTE_G4, NOTE_E5, NOTE_G5,
        NOTE_A5, NOTE_F5, NOTE_G5,
        NOTE_REST, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_B4, NOTE_REST,

        -- [Main Theme Section A - Repeat]
        NOTE_C5, NOTE_REST, NOTE_G4, NOTE_REST, NOTE_E4, NOTE_REST,
        NOTE_A4, NOTE_REST, NOTE_B4, NOTE_REST, NOTE_AS4, NOTE_A4,
        NOTE_G4, NOTE_E5, NOTE_G5,
        NOTE_A5, NOTE_F5, NOTE_G5,
        NOTE_REST, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_B4, NOTE_REST,
        
        -- 结尾停顿
        NOTE_REST, NOTE_REST 
    );

    -- 节拍数组 (数字代表倍数，基准节拍约 120ms)
    -- 1 = 短音(16分音符), 2 = 标准音(8分音符), 4 = 长音(4分音符)
    CONSTANT durations : rhythm_array := (
        -- [Intro]
        1, 2, 1, 2, 
        1, 1, 2, 1,
        4, 4, 4, 4,

        -- [Main Theme A]
        2, 1, 2, 1, 2, 1, -- C5 G4 E4
        2, 1, 2, 1, 1, 2, -- A4 B4 A#4 A4
        1, 1, 2,          -- G4 E5 G5
        1, 1, 2,          -- A5 F5 G5
        1, 1, 1, 1, 2, 2, -- E5 C5 D5 B4

        -- [Main Theme A - Repeat]
        2, 1, 2, 1, 2, 1, 
        2, 1, 2, 1, 1, 2, 
        1, 1, 2,          
        1, 1, 2,          
        1, 1, 1, 1, 2, 2,
        
        4, 4
    );

    -- =========================================================
    -- 3. 信号定义
    -- =========================================================
    SIGNAL tone_div_cnt : INTEGER RANGE 0 TO 70000 := 0; 
    SIGNAL tone_target  : INTEGER RANGE 0 TO 70000 := 0; 
    SIGNAL buzzer_reg   : STD_LOGIC := '0';
    
    -- 节拍控制
    -- 24MHz时钟下，120ms = 2,880,000 counts
    -- 若觉得速度不对，可调整此数值
    CONSTANT BASE_TIME  : INTEGER := 2400000; 
    SIGNAL tempo_cnt    : INTEGER RANGE 0 TO 24000000 := 0; 
    SIGNAL current_dur  : INTEGER RANGE 0 TO 24000000 := 0;
    SIGNAL note_index   : INTEGER RANGE 0 TO SONG_LENGTH-1 := 0;
    
BEGIN

    -- ---------------------------------------------------------
    -- 进程1：主控逻辑 (负责切歌、换音符)
    -- ---------------------------------------------------------
    PROCESS(clk, reset)
    BEGIN
        IF reset = '1' THEN
            tempo_cnt <= 0;
            note_index <= 0;
            tone_target <= NOTE_REST; -- 【修正点】使用 NOTE_REST
            current_dur <= BASE_TIME; 
        ELSIF rising_edge(clk) THEN
            -- 计算当前音符应该播放的总时长
            current_dur <= durations(note_index) * BASE_TIME;

            -- 节拍计数器
            IF tempo_cnt >= current_dur THEN
                tempo_cnt <= 0;
                
                -- 切换到下一个音符
                IF note_index = SONG_LENGTH - 1 THEN
                    note_index <= 0; -- 循环播放
                ELSE
                    note_index <= note_index + 1;
                END IF;
            ELSE
                tempo_cnt <= tempo_cnt + 1;
            END IF;

            -- 更新当前音高
            tone_target <= melody(note_index);
        END IF;
    END PROCESS;

    -- ---------------------------------------------------------
    -- 进程2：发声逻辑 (负责产生方波)
    -- ---------------------------------------------------------
    PROCESS(clk, reset)
    BEGIN
        IF reset = '1' THEN
            tone_div_cnt <= 0;
            buzzer_reg <= '0';
        ELSIF rising_edge(clk) THEN
            IF tone_target = NOTE_REST THEN -- 【修正点】使用 NOTE_REST
                buzzer_reg <= '0'; -- 休止符不震动
                tone_div_cnt <= 0;
            ELSE
                IF tone_div_cnt >= tone_target THEN
                    tone_div_cnt <= 0;
                    buzzer_reg <= NOT buzzer_reg; -- 翻转电平
                ELSE
                    tone_div_cnt <= tone_div_cnt + 1;
                END IF;
            END IF;
        END IF;
    END PROCESS;

    -- 输出到引脚
    buzzer <= buzzer_reg;

END rtl;
