

#include <bits/stdc++.h>

using i64 = long long;
using namespace std;
#define int long long
#define endl "\n"

void solve()
{
    int n;
    cin>>n;

    vector<int>a(n+1),max1(n+1,0),min1(n+1,0);

    for(int i=1;i<=n;i++) {
        cin>>a[i];
    }

    max1[1]=a[1],min1[1]=a[1];

    for(int i=2;i<=n;i++) {
        max1[i]=max(a[i],max1[i-1]);
        min1[i]=min(a[i],min1[i-1]);
    }
    for(int i=1;i<=n;i++) {
        if(i==1) {
            cout<<a[i]+a[i]<<' ';
        }
        else if(i==2) {
            cout<<max(a[1]+a[1],max(a[1]+a[2],a[2]+a[2]))<<' ';
        }
        else if(i==3) {
            map<int,int>mp;
            mp[a[1]+a[1]]++;
            mp[a[2]+a[2]]++;
            mp[a[3]+a[3]]++;
            mp[a[1]+a[2]]++;
            mp[a[1]+a[3]]++;
            mp[a[2]+a[3]]++;
            mp[min(a[1],min(a[2],a[3]))+max(a[1],max(a[2],a[3]))]++;
            int f1,f2=0;
            for(auto j:mp) {
                if(j.second>=f2)f1=j.first,f2=j.second;
            }
            cout<<f1<<' ';
        }
        else {
            cout<<max1[i]+min1[i]<<' ';
        }

    }


}

signed main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);

    int t;
    cin>>t;
    while(t--) {
        solve();
        cout<<endl;
    }

    return 0;
}
