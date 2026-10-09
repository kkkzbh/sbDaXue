// 酒吧博弈游戏模拟器 - 核心实现模块
module;

#include <vector>
#include <algorithm>
#include <ranges>
#include <random>

export module bar.core;

// 简化类型定义，让代码看起来更清爽
using u32 = unsigned;
using namespace std::views;

// 游戏配置参数结构体
export struct config
{
    int n;                  // 总人数，有多少人参与这个游戏
    int t;                  // 仿真天数，要跑多少天
    int c;                  // 酒吧容量，能坐多少人
    double random_ratio;    // 随机决策的人占多少比例
    double adaptive_ratio;  // 自适应策略的人占多少比例
    int kw;                 // 移动平均的记忆天数，记住前几天的情况
    u32 seed;              // 随机数种子，保证结果可重现
};

// 仿真结果数据结构体
export struct result
{
    std::vector<int> attendance;        // 每天去酒吧的人数记录
    std::vector<double> avg_rewards;    // 每天的平均奖励
    std::vector<double> cum_rewards;    // 每个人的累积奖励
};

// 代表一个人的数据结构
struct people
{
    // 人的决策策略类型
    enum struct policy
    {
        random,             // 随机决策：纯粹靠运气
        moving_avg,         // 移动平均：看前几天的平均人数
        adaptive_threshold  // 自适应阈值：会学习调整自己的判断标准
    };

    policy type;                        // 这个人用什么策略
    double p;                          // 随机策略的概率参数
    int k;                             // 移动平均策略的记忆长度
    double cum_reward = 0;             // 累积获得的奖励
    double threshold = 0.5;            // 自适应策略的判断阈值
    std::vector<double> reward_history; // 自适应策略的奖励历史记录
};

// 酒吧博弈仿真主函数
export auto sim(config const& cfg) -> result
{
    // 解包配置参数，让代码更简洁
    auto [n,t,c,ratio,adaptive_ratio,kw,seed] = cfg;

    // 计算各种策略的人数
    auto rn = int(ratio * n);           // 随机策略的人数
    auto an = int(adaptive_ratio * n);  // 自适应策略的人数
    auto mn = n - rn - an;              // 移动平均策略的人数

    // 创建所有参与者的容器
    auto a = std::vector<people>{};
    a.reserve(n);

    // 随机策略的基础概率：如果酒吧容量是总人数的60%，那基础去的概率就是0.6
    auto p = double(c) / n;

    // 创建随机决策的人：这些人完全靠运气决定去不去
    for(auto i : iota(0,rn)) {
        a.emplace_back(people::policy::random,p);
    }

    // 创建自适应阈值的人：这些人会根据自己的经历调整判断标准
    for(auto i : iota(0,an)) {
        auto agent = people{ people::policy::adaptive_threshold,0.5,3,0,0.5 };
        agent.reward_history.reserve(10);  // 记住最近10次的奖励情况
        a.emplace_back(std::move(agent));
    }

    // 创建移动平均的人：这些人会看前几天的平均情况来决定
    for(auto i : iota(0,mn)) {
        a.emplace_back(people::policy::moving_avg,0,kw);
    }

    // 设置随机数生成器，保证每次运行结果一致
    auto rng = std::mt19937{ seed };
    auto uni = std::uniform_real_distribution{ 0.,1. };
    auto rand = [&] {
        return uni(rng);
    };

    // 准备记录每天的数据
    auto attend = std::vector<int>{};       // 每天去酒吧的人数
    auto avg_reward = std::vector<double>{}; // 每天的平均奖励
    attend.reserve(t);
    avg_reward.reserve(t);

    // 开始每天的仿真循环
    for(auto day : iota(0,t)) {
        // 每个人都要做决策：今天去不去酒吧？
        auto decisions {
            iota(0,n)
            | transform([&a,&attend,rand,c](auto i) {
                using enum people::policy;

                // 随机策略：纯粹扔硬币决定
                if(a[i].type == random) {
                    return rand() < a[i].p;
                }

                // 自适应阈值策略：会根据自己的经历调整判断标准
                if(a[i].type == adaptive_threshold) {
                    // 如果有历史记录，就根据最近的奖励调整阈值
                    if(!a[i].reward_history.empty()) {
                        auto recent_avg = std::ranges::fold_left(
                            a[i].reward_history
                            | reverse      // 从最新的开始
                            | take(3),     // 取最近3次
                            0., std::plus{}
                        ) / std::min(3, int(a[i].reward_history.size()));
                        // 根据最近的奖励调整阈值：奖励好就更愿意去，奖励差就更谨慎
                        a[i].threshold = 0.5 + 0.3 * recent_avg;  // 范围在0.2到0.8之间
                    }

                    // 看看最近几天的出勤情况来预测今天
                    auto tn = std::min(int(attend.size()), 5);
                    if(tn == 0) {
                        // 第一天没有历史数据，随机决定
                        return rand() < 0.5;
                    };

                    // 预测今天的出勤人数
                    auto predicted = std::ranges::fold_left(
                        attend
                        | reverse    // 从最近的开始
                        | take(tn),  // 取最近几天
                        0.,
                        std::plus{}
                    ) / tn;

                    // 加入一些随机噪声，模拟预测的不确定性
                    predicted += (rand() - 0.5) * 0.2 * c;

                    // 如果预测人数小于自己的阈值，就去
                    return predicted < (c * a[i].threshold);
                }

                // 移动平均策略：看前几天的平均人数决定
                auto tn = std::min(int(attend.size()),a[i].k);
                auto s = std::ranges::fold_left (
                    attend
                    | reverse    // 从最近的开始
                    | take(tn),  // 取记忆长度内的天数
                    0.,
                    std::plus{}
                );
                auto avg = s / tn;
                // 如果平均人数小于容量，就去
                return avg < c;
            })
            | std::ranges::to<std::vector>()
        };
        // 统计今天实际去了多少人
        auto att = std::ranges::fold_left(decisions,0,std::plus{});
        attend.emplace_back(att);

        // 计算每个人今天的奖励
        auto sr = std::ranges::fold_left (
            iota(0,n)
            | transform([&a,&decisions,att,c](auto i) {
                // 计算第i个人今天的奖励
                auto r = [&] {
                    if(decisions[i] == 1) {
                        // 如果这个人去了酒吧
                        return (att <= c) ? 1. : -1.;  // 人没超就爽(+1)，人太多就痛苦(-1)
                    }
                    // 如果没去，就有点无聊(-0.2)
                    return -0.2;
                }();

                // 累加到个人总奖励
                a[i].cum_reward += r;

                // 自适应策略的人需要记住这次的奖励，用来调整下次的决策
                if(a[i].type == people::policy::adaptive_threshold) {
                    a[i].reward_history.emplace_back(r);
                    // 只保留最近10次的记录，太久远的就忘了
                    if(a[i].reward_history.size() > 10) {
                        a[i].reward_history.erase(a[i].reward_history.begin());
                    }
                }
                return r;
            }),
            0.,
            std::plus{}
        );

        // 记录今天的平均奖励
        avg_reward.emplace_back(sr / n);
    }

    // 整理最终的累积奖励数据
    auto cum {
        a
        | transform([](auto& p) {
            return p.cum_reward;  // 每个人的最终累积奖励
        })
        | std::ranges::to<std::vector>()
    };

    // 返回所有仿真结果
    return { attend,avg_reward,cum };
}

