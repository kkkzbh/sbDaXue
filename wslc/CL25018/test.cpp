#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

string S, T;
int n, m;
map<pair<int, int>, long long> dp[105];

// 分治计算S'_idx中T[l..r]作为子序列出现的次数
void solve(int idx) {
    if (idx == 0) {
        // 基础情况：S'_0 = S[0]
        for (int i = 0; i < m; i++) {
            if (S[0] == T[i]) {
                dp[0][{i, i}] = 1;
            }
        }
        return;
    }

    // 先递归计算S'_{idx-1}
    solve(idx - 1);

    // S'_idx = S'_{idx-1} + S[idx] + S'_{idx-1}
    // 合并左边S'_{idx-1}、中间S[idx]、右边S'_{idx-1}

    // 枚举[l,r]
    for (int l = 0; l < m; l++) {
        for (int r = l; r < m; r++) {
            long long cnt = 0;

            // 完全在左边的S'_{idx-1}
            if (dp[idx-1].count({l, r})) {
                cnt = (cnt + dp[idx-1][{l, r}]) % MOD;
            }

            // 完全在右边的S'_{idx-1}
            if (dp[idx-1].count({l, r})) {
                cnt = (cnt + dp[idx-1][{l, r}]) % MOD;
            }

            // 跨越中间，枚举k∈[l,r]
            for (int k = l; k <= r; k++) {
                if (S[idx] == T[k]) {
                    long long leftCnt = 1, rightCnt = 1;

                    // [l, k-1]的次数
                    if (k > l) {
                        if (dp[idx-1].count({l, k-1})) {
                            leftCnt = dp[idx-1][{l, k-1}];
                        } else {
                            leftCnt = 0;
                        }
                    }

                    // [k+1, r]的次数
                    if (k < r) {
                        if (dp[idx-1].count({k+1, r})) {
                            rightCnt = dp[idx-1][{k+1, r}];
                        } else {
                            rightCnt = 0;
                        }
                    }

                    // 加上[l, k-1]和[k+1, r]的组合
                    cnt = (cnt + leftCnt * rightCnt) % MOD;

                    // 再加上[l, k]与[k+1, r]的组合
                    if (k < r) {
                        long long leftK = 0, rightK = 0;
                        if (dp[idx-1].count({l, k})) {
                            leftK = dp[idx-1][{l, k}];
                        }
                        if (dp[idx-1].count({k+1, r})) {
                            rightK = dp[idx-1][{k+1, r}];
                        }
                        cnt = (cnt + leftK * rightK) % MOD;
                    }

                    // 再加上[l, k-1]与[k, r]的组合
                    if (k > l) {
                        long long leftK = 0, rightK = 0;
                        if (dp[idx-1].count({l, k-1})) {
                            leftK = dp[idx-1][{l, k-1}];
                        }
                        if (dp[idx-1].count({k, r})) {
                            rightK = dp[idx-1][{k, r}];
                        }
                        cnt = (cnt + leftK * rightK) % MOD;
                    }
                }
            }

            if (cnt > 0) {
                dp[idx][{l, r}] = cnt;
            }
        }
    }
}

int main() {
    cin >> S >> T;
    n = S.length();
    m = T.length();

    solve(n - 1);

    long long ans = 0;
    if (dp[n-1].count({0, m-1})) {
        ans = dp[n-1][{0, m-1}];
    }

    cout << ans << endl;

    return 0;
}