library ieee;
use ieee.std_logic_1164.all;

entity adder4 is
    port (
        a  : in  std_logic_vector(3 downto 0);  -- 加数
        b  : in  std_logic_vector(3 downto 0);  -- 加数
        ci : in  std_logic;                     -- 来自低位的进位
        s  : out std_logic_vector(3 downto 0);  -- 和
        co : out std_logic                      -- 向高位的进位
    );
end entity adder4;

architecture rtl of adder4 is
    signal c0, c1, c2 : std_logic;  -- 中间进位信号
begin
    -- 第0位
    s(0) <= a(0) xor b(0) xor ci;
    c0   <= (a(0) and b(0)) or (a(0) and ci) or (b(0) and ci);

    -- 第1位
    s(1) <= a(1) xor b(1) xor c0;
    c1   <= (a(1) and b(1)) or (a(1) and c0) or (b(1) and c0);

    -- 第2位
    s(2) <= a(2) xor b(2) xor c1;
    c2   <= (a(2) and b(2)) or (a(2) and c1) or (b(2) and c1);

    -- 第3位
    s(3) <= a(3) xor b(3) xor c2;
    co   <= (a(3) and b(3)) or (a(3) and c2) or (b(3) and c2);
end architecture rtl;
