

#include <bits/stdc++.h>

using i64 = long long;
using namespace std;

signed main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int n,m;
    cin>>n>>m;
    std::vector a(n+1,0LL);
    for(int i=1;i<=n;i++)cin>>a[i];
    vector b(n+1,0LL);
    for(int i=n;i>1;i--) {
        b[i-1]=a[i]-a[i-1];
    }
    vector c(n+1,0LL);
    for(int i=1;i<=n;i++) {
        c[i]=c[i-1]+max(0LL,b[i]);
    }
    i64 k;
    cin>>k;
    i64 s,t;
    while(m--) {
        cin>>s>>t;
        cout<<k+c[t-1]-c[s-1]<<"\n";
    }


    return 0;
}
