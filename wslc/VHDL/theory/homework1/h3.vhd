library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity t_flip_flop is
    Port (
        clk : in STD_LOGIC;   -- 时钟信号
        t   : in STD_LOGIC;   -- 触发控制信号
        q   : out STD_LOGIC   -- 输出信号
    );
end t_flip_flop;

architecture Behavioral of t_flip_flop is
    signal q_temp : STD_LOGIC := '0';  -- 内部信号,存储当前状态
begin
    
    -- T触发器进程:上升沿触发
    process(clk)
    begin
        -- 检测时钟上升沿
        if rising_edge(clk) then
            -- 根据t信号判断动作
            if t = '1' then
                -- t=1时,输出翻转
                q_temp <= not q_temp;
            else
                -- t=0时,输出保持
                q_temp <= q_temp;
            end if;
        end if;
    end process;
    
    -- 将内部信号赋值给输出端口
    q <= q_temp;

end Behavioral;