library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;  -- 支持向量加法

entity adder4_3 is
    port (
        a  : in  std_logic_vector(3 downto 0);  -- 加数
        b  : in  std_logic_vector(3 downto 0);  -- 加数
        ci : in  std_logic;                     -- 来自低位的进位
        s  : out std_logic_vector(3 downto 0);  -- 和
        co : out std_logic                      -- 向高位的进位
    );
end entity adder4_3;

architecture rtl of adder4_3 is
    signal aa, bb, ss : std_logic_vector(4 downto 0);  -- 扩展为5位
begin
    aa <= '0' & a;  -- 高位补0
    bb <= '0' & b;

    ss <= aa + bb + ci;  -- 五位求和

    s  <= ss(3 downto 0);  -- 低4位作为和
    co <= ss(4);           -- 最高位作为进位
end architecture rtl;
