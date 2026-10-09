function main()
    r = 2; % 饲养成本
    g = 0.1; % 市场价格下降值
    Q = @(t) (8 - g * t) * (80 + r * t) - 4 * t - 640; % 目标函数

    % 图解法
    solve1(Q);

    % 代数法
    solve2(r, g);
end

function solve1(Q)
    t = 0:20; % 出售时间
    y = arrayfun(Q, t); % 计算利润

    figure;
    title('Profit function of live pig sale');
    plot(t, y);
    xlabel('Selling time (t)');
    ylabel('Profit (Q)', 'Rotation', 90);
    xticks(t);

    [value, index] = max(y);
    fprintf('解法1: 在 %d 处取最大值 %f\n', index - 1, value);

    grid on; % 添加网格
end

function solve2(r, g)
    syms t;

    % 定义目标函数 Q(t)
    Q = (8 - g * t) * (80 + r * t) - 4 * t - 640;

    % 求导
    dQ = diff(Q, t);

    % 求解 dQ = 0
    res = solve(dQ == 0, t);

    % 计算最大值
    kt = double(res); % 转换为双精度数组
    ans = arrayfun(@(t_val) double(subs(Q, t, t_val)), kt); % 计算最大值

    fprintf('解法2: 函数在 %s 处取得最大值 %s\n', mat2str(kt), mat2str(ans));
end
