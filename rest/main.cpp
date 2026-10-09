#include<bits/stdc++.h>
#define endl "\n"
#define IOS ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define int long long
using namespace std;
typedef pair<int, int> PII;
typedef pair<double, double> PDD;
const int N = 2e5 + 5, mod = 998244353, M = 1e9;
const double eps = 1e-10;
int n, m, k, t, a[N],sum1[N],sum2[N];
void solve() {
    cin >> n >> m;
    vector<int> ve;
    for(int i = 0; i < m; ++i) {
        cin >> t;
        ve.push_back(t);
    }
    if(m & 1){
        sum1[0] = sum2[m - 1] = 0;
        for(int i = 2; i < m; i += 2)
            sum1[i] = sum1[i - 2] + ve[i - 1] - ve[i - 2];
        for(int i = m - 3; i >= 0; i -= 2)
            sum2[i] = sum2[i + 2] + ve[i + 2] - ve[i + 1];
        int res = 1e9;
        for(int i = 0; i < m; i += 2)
            res = min(res,sum1[i] + sum2[i]);
        cout << res << endl;
    }else{
        int res = 0;
        for(int i = 1; i < m; i += 2)
            res += ve[i] - ve[i - 1];
        cout << res << endl;
    }
}
signed main() {
    //IOS;
    int _ = 1;
    //cin >> _;
    while (_--) {
        solve();
    }
    return 0;
}
