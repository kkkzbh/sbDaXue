#include <vector>
#include <utility>

/**
 * 质因数分解函数
 * @param n 待分解的整数
 * @return 返回质因数及其对应的次数，以 pair<int, int> 表示
 */
std::vector<std::pair<int, int>> 质因数分解(int n) {
    auto result = std::vector<std::pair<int, int>>{};
    // 处理2作为质因数的情况
    if(n % 2 == 0) {
        auto count = 0;
        do {
            n /= 2;
            count++;
        } while(n % 2 == 0);
        result.emplace_back(2, count);
    }
    for(auto i = 3; i * i <= n; i += 2) {
        if(n % i) {
            continue;
        }
        auto count = 0;
        do {
            n /= i;
            count++;
        } while(n % i == 0);
        result.emplace_back(i, count);

    }
    if(n > 1) {
        result.emplace_back(n, 1);
    }
    return result;
}

