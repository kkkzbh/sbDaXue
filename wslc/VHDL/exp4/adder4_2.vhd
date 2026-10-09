library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;  -- 支持向量加法

entity adder4_2 is
    port (
        a : in  std_logic_vector(3 downto 0);  -- 加数
        b : in  std_logic_vector(3 downto 0);  -- 加数
        s : out std_logic_vector(3 downto 0)   -- 和
    );
end entity adder4_2;

architecture rtl of adder4_2 is
begin
    -- 直接用运算符描述
    s <= a + b;
end architecture rtl;
