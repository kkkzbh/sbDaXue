#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

string S, T;
int n, m;
map<pair<int, int>, long long> dp[105];

void solve(int idx) {
    if (idx == 0) {
        // S'_0 = a_0
        for (int i = 0; i < m; i++) {
            if (S[0] == T[i]) {
                dp[0][{i, i}] = 1;
            }
        }
        return;
    }

    solve(idx - 1);

    // S'_idx = S'_{idx-1} + a_idx + S'_{idx-1}

    for (int l = 0; l < m; l++) {
        for (int r = l; r < m; r++) {
            long long cnt = 0;

            // 完全在左边S'_{idx-1}
            if (dp[idx-1].count({l, r})) {
                cnt = (cnt + dp[idx-1][{l, r}]) % MOD;
            }

            // 完全在右边S'_{idx-1}
            if (dp[idx-1].count({l, r})) {
                cnt = (cnt + dp[idx-1][{l, r}]) % MOD;
            }

            // 跨越中间，枚举k∈[l,r]
            for (int k = l; k <= r; k++) {
                if (S[idx] == T[k]) {
                    // 加上[l,k-1]的次数和[k+1,r]的次数
                    long long leftCnt = (k == l ? 1 : 0);
                    long long rightCnt = (k == r ? 1 : 0);

                    if (k > l && dp[idx-1].count({l, k-1})) {
                        leftCnt = dp[idx-1][{l, k-1}];
                    }
                    if (k < r && dp[idx-1].count({k+1, r})) {
                        rightCnt = dp[idx-1][{k+1, r}];
                    }

                    cnt = (cnt + leftCnt * rightCnt) % MOD;

                    // 再加上[l,k]与[k+1,r]
                    if (k < r) {
                        long long left = 0, right = 0;
                        if (dp[idx-1].count({l, k})) left = dp[idx-1][{l, k}];
                        if (dp[idx-1].count({k+1, r})) right = dp[idx-1][{k+1, r}];
                        cnt = (cnt + left * right) % MOD;
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