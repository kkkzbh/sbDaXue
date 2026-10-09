--------------------------------------------------------------------------------
-- 实验：只因你太美 (Ji Ni Tai Mei)
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
    -- 计算公式: 计数器上限 = 24,000,000 / (频率 * 2)
    -- =========================================================
    CONSTANT NOTE_C4 : INTEGER := 45866; -- 261Hz Do
    CONSTANT NOTE_D4 : INTEGER := 40863; -- 294Hz Re
    CONSTANT NOTE_E4 : INTEGER := 36404; -- 330Hz Mi
    CONSTANT NOTE_F4 : INTEGER := 34361; -- 349Hz Fa
    CONSTANT NOTE_G4 : INTEGER := 30612; -- 392Hz Sol
    CONSTANT NOTE_A4 : INTEGER := 27272; -- 440Hz La
    CONSTANT NOTE_B4 : INTEGER := 24291; -- 494Hz Si
    CONSTANT NOTE_C5 : INTEGER := 22944; -- 523Hz Do (High)
    CONSTANT NOTE_D5 : INTEGER := 20431; -- 587Hz Re (High)
    CONSTANT NOTE_E5 : INTEGER := 18204; -- 659Hz Mi (High)
    
    CONSTANT NOTE_REST : INTEGER := 0;   -- 休止符

    -- =========================================================
    -- 2. 乐谱数据：只因你太美 (Ji Ni Tai Mei)
    -- =========================================================
    CONSTANT SONG_LENGTH : INTEGER := 48; -- 增加长度
    
    TYPE melody_array IS ARRAY (0 TO SONG_LENGTH-1) OF INTEGER;
    TYPE rhythm_array IS ARRAY (0 TO SONG_LENGTH-1) OF INTEGER;

    CONSTANT melody : melody_array := (
        -- [Phrase 1] "Ji Ni Tai Mei" (只 因 你 太 美)
        NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_F4, NOTE_REST, NOTE_REST,
        
        -- [Phrase 2] "Ji Ni Tai Mei" (只 因 你 太 美)
        NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_F4, NOTE_REST, NOTE_REST,

        -- [Phrase 3] "Ying Mian Zou Lai..." (迎面走来的你让我如此蠢蠢欲动)
        -- 简谱: 3 3 2 1 | 2 3 2 0 | 3 3 2 1 | 2 3 2 0
        NOTE_E4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_REST,
        NOTE_E4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_REST,

        -- [Phrase 4] "Ji Ni Shi Zai Tai Mei" (Reprise)
        NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_F4, NOTE_G4, NOTE_F4,
        NOTE_E4, NOTE_D4, NOTE_C4, NOTE_C4, NOTE_REST, NOTE_REST, NOTE_REST, NOTE_REST
    );

    -- 节拍定义 (1 = 1/8拍, 2 = 1/4拍, 4 = 1/2拍, etc.)
    -- 这里的单位时间大约是 120ms (BASE_TIME 决定)
    CONSTANT durations : rhythm_array := (
        -- Phrase 1
        2, 2, 2, 2, 4, 3, 1, 4, -- C C D E (F F)
        
        -- Phrase 2
        2, 2, 2, 2, 4, 3, 1, 4,
        
        -- Phrase 3
        2, 2, 2, 2, 2, 2, 4, 2, -- E E D C D E D(Long)
        2, 2, 2, 2, 2, 2, 4, 2,
        
        -- Phrase 4
        2, 2, 2, 2, 3, 1, 3, 1, -- C C D E F F G F
        2, 2, 4, 4, 4, 4, 4, 4  -- E D C C (End)
    );

    -- =========================================================
    -- 3. 信号定义
    -- =========================================================
    SIGNAL tone_div_cnt : INTEGER RANGE 0 TO 50000 := 0; 
    SIGNAL tone_target  : INTEGER RANGE 0 TO 50000 := 0; 
    SIGNAL buzzer_reg   : STD_LOGIC := '0';
    
    -- 基准节拍: 100ms (加快一点速度，原版较快)
    -- 24,000,000 * 0.1 = 2,400,000
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
            tone_target <= NOTE_REST;
            current_dur <= BASE_TIME; 
        ELSIF rising_edge(clk) THEN
            -- 计算当前音符时长
            -- 防止 durations(note_index) 为 0 或越界，虽然常量定义保证了非零
            current_dur <= durations(note_index) * BASE_TIME;

            IF tempo_cnt >= current_dur THEN
                tempo_cnt <= 0;
                IF note_index = SONG_LENGTH - 1 THEN
                    note_index <= 0; -- 循环播放
                ELSE
                    note_index <= note_index + 1;
                END IF;
            ELSE
                tempo_cnt <= tempo_cnt + 1;
            END IF;

            tone_target <= melody(note_index);
        END IF;
    END PROCESS;

    -- ---------------------------------------------------------
    -- 进程2：发声逻辑
    -- ---------------------------------------------------------
    PROCESS(clk, reset)
    BEGIN
        IF reset = '1' THEN
            tone_div_cnt <= 0;
            buzzer_reg <= '0';
        ELSIF rising_edge(clk) THEN
            IF tone_target = NOTE_REST THEN
                buzzer_reg <= '1'; -- 休止符输出高电平或低电平取决于蜂鸣器是有源还是无源及驱动电路，通常静音保持固定电平
                tone_div_cnt <= 0;
            ELSE
                IF tone_div_cnt >= tone_target THEN
                    tone_div_cnt <= 0;
                    buzzer_reg <= NOT buzzer_reg;
                ELSE
                    tone_div_cnt <= tone_div_cnt + 1;
                END IF;
            END IF;
        END IF;
    END PROCESS;

    buzzer <= buzzer_reg;

END rtl;
