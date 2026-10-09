library IEEE; -- 引入IEEE库
use IEEE.STD_LOGIC_1164.ALL; -- 使用STD_LOGIC_1164标准逻辑包

entity encode_16_4 is -- 定义实体：16选1低有效优先编码器（16→4）
    Port ( -- 端口列表开始
        in0, in1, in2, in3, in4, in5, in6, in7 : in STD_LOGIC; -- 单比特输入0~7（低电平表示选中）
        in8, in9, in10, in11, in12, in13, in14, in15 : in STD_LOGIC; -- 单比特输入8~15（低电平表示选中）
        dout : out STD_LOGIC_VECTOR(3 downto 0); -- 4位输出编码（低有效输入的索引）
        nul : out STD_LOGIC; -- 无有效输入标志（全为'1'时为'1'）
        inv : out STD_LOGIC -- 非法输入标志（多于一个为'0'时为'1'）
    ); -- 端口列表结束
end encode_16_4; -- 实体结束

architecture Behavioral of encode_16_4 is -- 行为级结构体开始
    signal input_vector : STD_LOGIC_VECTOR(15 downto 0); -- 汇总后的16位输入向量
    signal valid_count : integer range 0 to 16; -- 低电平输入的计数（0~16）
begin -- 结构体主体开始
    -- 将输入组合成向量便于处理
    input_vector <= in15 & in14 & in13 & in12 & in11 & in10 & in9 & in8 & -- 拼接高位部分(15..8)
                    in7 & in6 & in5 & in4 & in3 & in2 & in1 & in0; -- 拼接低位部分(7..0)
    
    -- 主编码进程
    process(in0, in1, in2, in3, in4, in5, in6, in7,  -- 敏感信号列表(0..7)
            in8, in9, in10, in11, in12, in13, in14, in15) -- 敏感信号列表(8..15)
        variable count : integer range 0 to 16; -- 用于过程内统计的变量计数器
    begin -- 进程开始
        -- 计算有效输入(低电平)的个数
        count := 0; -- 初始化计数为0
        for i in 0 to 15 loop -- 遍历16个输入位
            if input_vector(i) = '0' then -- 检查第i位是否为低电平
                count := count + 1; -- 统计低电平个数+1
            end if; -- if结束
        end loop; -- for循环结束
        
        valid_count <= count; -- 更新寄存信号：低电平个数
        
        -- 判断无有效输入标志(所有输入为1)
        if count = 0 then -- 若没有任何低电平
            nul <= '1'; -- 置位nul：无有效输入
            inv <= '0'; -- inv清零：非非法
            dout <= "0000"; -- 输出编码无意义，置0
            
        -- 判断非法输入标志(多个输入同时为0)
        elsif count > 1 then -- 若出现多个低电平
            nul <= '0'; -- nul清零：存在输入
            inv <= '1'; -- 置位inv：非法输入
            dout <= "0000"; -- 输出编码无意义，置0
            
        -- 正常编码(只有一个输入为0)
        else -- 仅有一个低电平有效
            nul <= '0'; -- nul清零：存在输入
            inv <= '0'; -- inv清零：输入合法
            
            -- 优先编码器:从高位到低位检查
            if in15 = '0' then -- 若in15为低
                dout <= "1111";  -- 15：输出索引15
            elsif in14 = '0' then -- 否则检查in14
                dout <= "1110";  -- 14：输出索引14
            elsif in13 = '0' then -- 检查in13
                dout <= "1101";  -- 13：输出索引13
            elsif in12 = '0' then -- 检查in12
                dout <= "1100";  -- 12：输出索引12
            elsif in11 = '0' then -- 检查in11
                dout <= "1011";  -- 11：输出索引11
            elsif in10 = '0' then -- 检查in10
                dout <= "1010";  -- 10：输出索引10
            elsif in9 = '0' then -- 检查in9
                dout <= "1001";  -- 9：输出索引9
            elsif in8 = '0' then -- 检查in8
                dout <= "1000";  -- 8：输出索引8
            elsif in7 = '0' then -- 检查in7
                dout <= "0111";  -- 7：输出索引7
            elsif in6 = '0' then -- 检查in6
                dout <= "0110";  -- 6：输出索引6
            elsif in5 = '0' then -- 检查in5
                dout <= "0101";  -- 5：输出索引5
            elsif in4 = '0' then -- 检查in4
                dout <= "0100";  -- 4：输出索引4
            elsif in3 = '0' then -- 检查in3
                dout <= "0011";  -- 3：输出索引3
            elsif in2 = '0' then -- 检查in2
                dout <= "0010";  -- 2：输出索引2
            elsif in1 = '0' then -- 检查in1
                dout <= "0001";  -- 1：输出索引1
            elsif in0 = '0' then -- 检查in0
                dout <= "0000";  -- 0：输出索引0
            else -- 理论不可达（已保证count=1）
                dout <= "0000"; -- 回退默认值
            end if; -- 优先编码条件结束
        end if; -- 三分支判断结束
    end process; -- 进程结束

end Behavioral; -- 结构体结束
  dout <= "0000";
            end if;
        end if;
    end process;

end Behavioral;