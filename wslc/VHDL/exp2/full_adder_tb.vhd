-- 一位全加器测试平台(Testbench)
-- 用于验证full_adder实体的功能正确性
-- 测试所有可能的输入组合(8种)

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- testbench实体没有端口
entity full_adder_tb is
end full_adder_tb;

architecture Behavioral of full_adder_tb is
    -- 被测试组件声明
    component full_adder
        Port (
            a  : in  STD_LOGIC;
            b  : in  STD_LOGIC;
            ci : in  STD_LOGIC;
            s  : out STD_LOGIC;
            co : out STD_LOGIC
        );
    end component;

    -- 测试信号声明
    signal a_tb  : STD_LOGIC := '0';
    signal b_tb  : STD_LOGIC := '0';
    signal ci_tb : STD_LOGIC := '0';
    signal s_tb  : STD_LOGIC;
    signal co_tb : STD_LOGIC;

    -- 时钟周期常数
    constant clk_period : time := 10 ns;

begin
    -- 实例化被测试单元(UUT: Unit Under Test)
    uut: full_adder port map (
        a  => a_tb,
        b  => b_tb,
        ci => ci_tb,
        s  => s_tb,
        co => co_tb
    );

    -- 激励过程：测试所有可能的输入组合
    stim_proc: process
    begin
        -- 测试用例1: a=0, b=0, ci=0 (期望: s=0, co=0)
        a_tb <= '0'; b_tb <= '0'; ci_tb <= '0';
        wait for clk_period;

        -- 测试用例2: a=0, b=0, ci=1 (期望: s=1, co=0)
        a_tb <= '0'; b_tb <= '0'; ci_tb <= '1';
        wait for clk_period;

        -- 测试用例3: a=0, b=1, ci=0 (期望: s=1, co=0)
        a_tb <= '0'; b_tb <= '1'; ci_tb <= '0';
        wait for clk_period;

        -- 测试用例4: a=0, b=1, ci=1 (期望: s=0, co=1)
        a_tb <= '0'; b_tb <= '1'; ci_tb <= '1';
        wait for clk_period;

        -- 测试用例5: a=1, b=0, ci=0 (期望: s=1, co=0)
        a_tb <= '1'; b_tb <= '0'; ci_tb <= '0';
        wait for clk_period;

        -- 测试用例6: a=1, b=0, ci=1 (期望: s=0, co=1)
        a_tb <= '1'; b_tb <= '0'; ci_tb <= '1';
        wait for clk_period;

        -- 测试用例7: a=1, b=1, ci=0 (期望: s=0, co=1)
        a_tb <= '1'; b_tb <= '1'; ci_tb <= '0';
        wait for clk_period;

        -- 测试用例8: a=1, b=1, ci=1 (期望: s=1, co=1)
        a_tb <= '1'; b_tb <= '1'; ci_tb <= '1';
        wait for clk_period;

        -- 结束仿真
        wait;
    end process;

end Behavioral;