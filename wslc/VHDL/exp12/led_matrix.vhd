LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.std_logic_unsigned.ALL;

ENTITY led_matrix IS
    PORT (
        clk   : IN  STD_LOGIC;                      -- 24MHz时钟输入
        reset : IN  STD_LOGIC;                      -- 复位信号（高电平有效）
        KD    : IN  STD_LOGIC_VECTOR(20 DOWNTO 1);  -- 波动开关输入，用于控制方向
        row   : OUT STD_LOGIC_VECTOR(15 DOWNTO 0);  -- 行选信号（低电平有效）
        col   : OUT STD_LOGIC_VECTOR(15 DOWNTO 0)   -- 列选信号（低电平有效，低亮）
    );
END led_matrix;

ARCHITECTURE rtl OF led_matrix IS
    -- 字符数量：20231202051计科1班高康嘉 = 18个字符
    CONSTANT CHAR_NUM : INTEGER := 18;
    
    -- 汉字点阵ROM：每个汉字16行×16列
    TYPE rom_array IS ARRAY (0 TO 15) OF STD_LOGIC_VECTOR(15 DOWNTO 0);
    TYPE char_rom IS ARRAY (0 TO CHAR_NUM-1) OF rom_array;
    
    -- 点阵数据 (1=点亮, 0=熄灭; 输出时取反为低电平有效)
    -- 使用左右镜像后的16x16点阵，确保显示方向正确
    CONSTANT font_data : char_rom := (
    -- 0: 2 (Mirrored)
    (X"0000", X"0000", X"0000", X"0000", X"01C0", X"0220", X"0200", X"0200", X"0100", X"0180", X"00C0", X"0040", X"03E0", X"0000", X"0000", X"0000"),
    -- 1: 0 (Mirrored)
    (X"0000", X"0000", X"0000", X"0000", X"01C0", X"0360", X"0220", X"0220", X"0220", X"0220", X"0220", X"0360", X"01C0", X"0000", X"0000", X"0000"),
    -- 2: 2 (Mirrored)
    (X"0000", X"0000", X"0000", X"0000", X"01C0", X"0220", X"0200", X"0200", X"0100", X"0180", X"00C0", X"0040", X"03E0", X"0000", X"0000", X"0000"),
    -- 3: 3 (Mirrored)
    (X"0000", X"0000", X"0000", X"0000", X"01C0", X"0220", X"0200", X"0300", X"01C0", X"0200", X"0200", X"0200", X"01E0", X"0000", X"0000", X"0000"),
    -- 4: 1 (Mirrored)
    (X"0000", X"0000", X"0000", X"0000", X"00C0", X"00A0", X"0080", X"0080", X"0080", X"0080", X"0080", X"0080", X"0080", X"0000", X"0000", X"0000"),
    -- 5: 2 (Mirrored)
    (X"0000", X"0000", X"0000", X"0000", X"01C0", X"0220", X"0200", X"0200", X"0100", X"0180", X"00C0", X"0040", X"03E0", X"0000", X"0000", X"0000"),
    -- 6: 0 (Mirrored)
    (X"0000", X"0000", X"0000", X"0000", X"01C0", X"0360", X"0220", X"0220", X"0220", X"0220", X"0220", X"0360", X"01C0", X"0000", X"0000", X"0000"),
    -- 7: 2 (Mirrored)
    (X"0000", X"0000", X"0000", X"0000", X"01C0", X"0220", X"0200", X"0200", X"0100", X"0180", X"00C0", X"0040", X"03E0", X"0000", X"0000", X"0000"),
    -- 8: 0 (Mirrored)
    (X"0000", X"0000", X"0000", X"0000", X"01C0", X"0360", X"0220", X"0220", X"0220", X"0220", X"0220", X"0360", X"01C0", X"0000", X"0000", X"0000"),
    -- 9: 5 (Mirrored)
    (X"0000", X"0000", X"0000", X"0000", X"01E0", X"0020", X"0020", X"01E0", X"0200", X"0200", X"0200", X"0200", X"01E0", X"0000", X"0000", X"0000"),
    -- 10: 1 (Mirrored)
    (X"0000", X"0000", X"0000", X"0000", X"00C0", X"00A0", X"0080", X"0080", X"0080", X"0080", X"0080", X"0080", X"0080", X"0000", X"0000", X"0000"),
    -- 11: 计 (Mirrored)
    (X"0000", X"0000", X"0210", X"0210", X"0200", X"0200", X"1FD8", X"0210", X"0210", X"0210", X"0250", X"0230", X"0200", X"0000", X"0000", X"0000"),
    -- 12: 科 (Mirrored)
    (X"0000", X"0000", X"0840", X"0938", X"0A10", X"0878", X"0990", X"0A30", X"1858", X"0F98", X"0810", X"0810", X"0810", X"0000", X"0000", X"0000"),
    -- 13: 1 (Mirrored)
    (X"0000", X"0000", X"0000", X"0000", X"00C0", X"00A0", X"0080", X"0080", X"0080", X"0080", X"0080", X"0080", X"0080", X"0000", X"0000", X"0000"),
    -- 14: 班 (Mirrored)
    (X"0000", X"0000", X"0100", X"1F38", X"0990", X"0990", X"09B8", X"1D50", X"0950", X"0910", X"08B0", X"0888", X"1E40", X"0000", X"0000", X"0000"),
    -- 15: 高 (Mirrored)
    (X"0000", X"0000", X"0080", X"1FF8", X"07E0", X"0810", X"0FF0", X"0000", X"1FF8", X"17E8", X"1428", X"17E8", X"1C08", X"0000", X"0000", X"0000"),
    -- 16: 康 (Mirrored)
    (X"0000", X"0000", X"0080", X"1FF8", X"0108", X"0FE8", X"1FF8", X"0908", X"0FE8", X"0928", X"0F88", X"0D78", X"118C", X"0000", X"0000", X"0000"),
    -- 17: 嘉 (Mirrored)
    (X"0000", X"0000", X"0000", X"1FF8", X"1FF8", X"0FF0", X"0810", X"0FF0", X"1FF8", X"0020", X"1EF8", X"1290", X"1EC8", X"0000", X"0000", X"0000")
    );
    
    -- 分频计数器
    SIGNAL div_scan   : INTEGER RANGE 0 TO 2399 := 0;         -- 行扫描分频 (24MHz/2400=10kHz)
    SIGNAL div_scroll : INTEGER RANGE 0 TO 999999 := 0;       -- 滚动分频 (24MHz/1M=24Hz) Speed Up for smooth scroll
    
    -- 行扫描计数器 (0-15)
    SIGNAL row_cnt : INTEGER RANGE 0 TO 15 := 0;
    
    -- 滚动偏移量
    SIGNAL offset_x : INTEGER RANGE 0 TO (CHAR_NUM * 16 - 1) := 0; -- 水平像素偏移
    SIGNAL offset_y : INTEGER RANGE 0 TO 15 := 0;                  -- 垂直像素偏移
    
    -- 输出寄存器
    SIGNAL row_out : STD_LOGIC_VECTOR(15 DOWNTO 0) := (OTHERS => '1');
    SIGNAL col_out : STD_LOGIC_VECTOR(15 DOWNTO 0) := (OTHERS => '1');

BEGIN
    -- 统一时序进程：分频 + 扫描 + 滚动逻辑
    PROCESS(clk)
        VARIABLE temp_row    : STD_LOGIC_VECTOR(15 DOWNTO 0);
        VARIABLE cur_row_idx : INTEGER RANGE 0 TO 15;
        
        -- 用于水平滚动的变量
        VARIABLE char_idx_l  : INTEGER RANGE 0 TO CHAR_NUM-1;
        VARIABLE char_idx_r  : INTEGER RANGE 0 TO CHAR_NUM-1;
        VARIABLE shift_bit   : INTEGER RANGE 0 TO 15;
        VARIABLE data_l      : STD_LOGIC_VECTOR(15 DOWNTO 0);
        VARIABLE data_r      : STD_LOGIC_VECTOR(15 DOWNTO 0);
        VARIABLE temp_32     : STD_LOGIC_VECTOR(31 DOWNTO 0);
    BEGIN
        IF rising_edge(clk) THEN
            -- 同步复位
            IF reset = '0' THEN
                div_scan <= 0;
                div_scroll <= 0;
                row_cnt <= 0;
                offset_x <= 0;
                offset_y <= 0;
                row_out <= (OTHERS => '1');
                col_out <= (OTHERS => '1');
            ELSE
            
            -- 1. 扫描分频逻辑
            IF div_scan = 2399 THEN
                div_scan <= 0;
                IF row_cnt = 15 THEN
                    row_cnt <= 0;
                ELSE
                    row_cnt <= row_cnt + 1;
                END IF;
            ELSE
                div_scan <= div_scan + 1;
            END IF;
            
            -- 2. 滚动控制逻辑 (根据KD按键状态)
            IF div_scroll = 999999 THEN
                div_scroll <= 0;
                -- 优先级: KD1(左) > KD2(右) > KD3(上) > KD4(下)
                -- 假设KD为高电平有效(Switch ON)
                IF KD(1) = '1' THEN -- 向左滚动
                    offset_y <= 0; -- 复位Y方向
                    IF offset_x = (CHAR_NUM * 16 - 1) THEN
                        offset_x <= 0;
                    ELSE
                        offset_x <= offset_x + 1;
                    END IF;
                ELSIF KD(2) = '1' THEN -- 向右滚动
                    offset_y <= 0;
                    IF offset_x = 0 THEN
                        offset_x <= (CHAR_NUM * 16 - 1);
                    ELSE
                        offset_x <= offset_x - 1;
                    END IF;
                ELSIF KD(3) = '1' THEN -- 向上滚动
                    -- 保持水平偏移不变，仅垂直滚动
                    IF offset_y = 15 THEN
                        offset_y <= 0;
                    ELSE
                        offset_y <= offset_y + 1;
                    END IF;
                ELSIF KD(4) = '1' THEN -- 向下滚动
                    IF offset_y = 0 THEN
                        offset_y <= 15;
                    ELSE
                        offset_y <= offset_y - 1;
                    END IF;
                END IF;
            ELSE
                div_scroll <= div_scroll + 1;
            END IF;
            
            -- 3. 显示驱动逻辑
            
            -- Row output (One-hot, Low effective)
            temp_row := (OTHERS => '1');
            temp_row(row_cnt) := '0';
            row_out <= temp_row;
            
            -- Column output calculation
            -- 计算当前实际显示的物理行对应的逻辑行索引
            -- 加上 offset_y 实现垂直滚动
            IF (row_cnt + offset_y) > 15 THEN
                cur_row_idx := row_cnt + offset_y - 16;
            ELSE
                cur_row_idx := row_cnt + offset_y;
            END IF;
            
            -- 计算水平偏移对应的字符和位移
            char_idx_l := offset_x / 16;
            shift_bit  := offset_x MOD 16;
            
            -- 计算右侧相邻字符索引 (为了平滑滚动)
            IF char_idx_l = CHAR_NUM - 1 THEN
                char_idx_r := 0;
            ELSE
                char_idx_r := char_idx_l + 1;
            END IF;
            
            -- 获取左右两个字符在当前行的数据
            data_l := font_data(char_idx_l)(cur_row_idx);
            data_r := font_data(char_idx_r)(cur_row_idx);
            
            -- 拼接成32位数据：[DataL][DataR]
            -- DataL在高位(左), DataR在低位(右)
            -- 假设 X"01C0" (0000 0001 1100 0000) 中 15是左边, 0是右边
            -- 需要拼接为: Left(15..0) & Right(15..0)
            temp_32 := data_l & data_r;
            
            -- 截取窗口: 从 (31 - shift) 到 (16 - shift)
            -- 当 shift=0, 取 31..16 (即 data_l)
            -- 当 shift=1, 取 30..15 (即 data_l(14..0) & data_r(15))
            col_out <= NOT temp_32((31 - shift_bit) DOWNTO (16 - shift_bit));
            
            END IF;
        END IF;
    END PROCESS;
    
    -- 输出连接
    row <= row_out;
    col <= col_out;

END rtl;
