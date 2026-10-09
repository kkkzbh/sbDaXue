-- 硬件描述语言实验二：一位全加器实验
-- 实体名称：full_adder
-- 功能：实现一位全加器，具有两个数据输入、一个进位输入和一个和输出、一个进位输出
-- 日期：2025年

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- 实体声明：定义一位全加器的外部接口
entity full_adder is
    Port (
        a  : in  STD_LOGIC;   -- 被加数
        b  : in  STD_LOGIC;   -- 加数
        ci : in  STD_LOGIC;   -- 自低位进位
        s  : out STD_LOGIC;   -- 和
        co : out STD_LOGIC    -- 向高位进位
    );
end full_adder;

-- 构造体：实现一位全加器的逻辑功能
architecture Behavioral of full_adder is
begin
    -- 和的计算：三个输入的异或运算
    s <= a xor b xor ci;

    -- 进位的计算：当任意两个输入为1时产生进位
    co <= (a and b) or (a and ci) or (b and ci);

end Behavioral;