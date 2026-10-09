
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- 实体声明：定义外部接口
entity or_gate_2input is
    Port (
        in1  : in  STD_LOGIC;  -- 第一个或门输入
        in2  : in  STD_LOGIC;  -- 第二个或门输入
        out1 : out STD_LOGIC   -- 或门输出
    );
end or_gate_2input;

-- 构造体：实现或门逻辑
architecture Behavioral of or_gate_2input is
begin
    -- 或门逻辑实现：当in1或in2中至少一个为'1'时，out1为'1'
    out1 <= in1 or in2;
end Behavioral;