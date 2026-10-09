

#include"std.h"
#include"component.h"
#include"rand.h"
#include"io.h"
#include"middleware.h"
#include"fip.h"

constexpr double p_start = 0.05;
constexpr double p_end = 0.30;

int m;
std::vector<int> m_cnt;

std::vector<std::vector<std::vector<bool>>> data;
std::vector<std::vector<int>> check,dis;

fun add(std::vector<std::vector<int>>& v)
{
    v[0][0] += 1;
    for(int next{}; let& val : v | join) {
        val += next;
        next = 0;
        if(val > 1) {
            val = 0;
            next = 1;
        }
    }
}

fun make()
{
    double cost{};
    double earn{};

    for(int i : iota(1,m - 1)) {
        for(int j{}; let& mid : middlewares[i - 1]) {
            let& need = mid.need;
            let& v = data[i - 1];
            let& nv = data[i][j];
            let ok = [&] {
                bool contain{ true };
                for(int val : need) {
                    if(check[i - 1][val]) {
                        while(!v[val].empty() and !v[val].back()) {
                            cost += mid.check_s;
                            v[val].pop_back();
                        }
                        if(!v[val].empty()) {
                            cost += mid.check_s;
                        } else {
                            contain = false;
                        }
                    } else if(v[val].empty()) {
                        contain = false;
                        break;
                    }
                }
                return contain;
            };
            while(ok()) {
                bool well{ true };
                for(int val : need) {
                    if(!v[val].back()) {
                        well = false;
                        break;
                    }
                }
                if(check[i][j]) {
                    cost += mid.check_s;
                    if(!well) {
                        if(dis[i][j]) {

                        } else {
                            continue;
                        }
                    }
                }
                cost += mid.fit_s;
            }

            ++j;
        }
    }

    let& v = data[m - 2];
    let ok = [&] {
        bool contain{ true };
        for(int i{}; let& val : v) {
            if(check[m - 2][i]) {
                while(!val.empty() and !val.back()) {
                    val.pop_back();
                    cost += middlewares[m - 2][i].check_s;
                }
                if(!val.empty()) {
                    cost += middlewares[m - 2][i].check_s;
                } else {
                    contain = false;
                }
            } else if(val.empty()) {
                contain = false;
                break;
            }

            ++i;
        }
        return contain;
    };


}

fun solve()
{

}

fun main() -> int
{
    println("请输入工序m");
    std::cin >> m;
    middlewares.assign(m - 2,{});
    data.assign(m,{});
    check.assign(m,{}),dis.assign(m,{});
    println("零件数n");
    int n;
    std::cin >> n;
    m_cnt.push_back(n);
    components.assign(n,{});
    data[0].assign(n,{});
    check[0].assign(n,{}),dis[0].assign(n,{});
    println("依次输入按格式 次品率 购买单价 检测成本");
    for(let& [p,buy_s,check_s] : components) {
        std::cin >> p >> buy_s >> check_s;
    }
    for(int _ : iota(1,m - 1)) {
        println("请输入第二道工序的中间件个数n");
        std::cin >> n;
        m_cnt.push_back(n);
        let& mid = middlewares[_];
        mid.assign(n,{});
        data[_].assign(n,{});
        check[_].assign(n,{}),dis[_].assign(n,{});
        println("按两行输入\n次品率 装配成本 检测成本 拆解费用\n需要的上件个数 上件编号(0开始)");
        for(let& [p,fit_s,check_s,dis_s,need] : mid) {
            std::cin >> p >> fit_s >> check_s >> dis_s;
            std::cin >> n;
            std::copy_n(std::istream_iterator<int>{ std::cin },n,std::back_inserter(need));
        }
    }
    data.back().assign(1,{});
    check.back().assign(1,{}),dis.back().assign(1,{});
    println("请输入成品的参数\n次品率 装配成本 检测成本 拆解费用 市场售价 调换损失");
    std::cin >> fip.p >> fip.fit_s >> fip.check_s >> fip.dis_s >> fip.price >> fip.swap_s;

    for(int i{}; let& component_v : data[0]) {
        component_v = make_components(i++);
    }



}