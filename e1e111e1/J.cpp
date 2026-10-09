#include <bits/stdc++.h>
using namespace std;
#define int long long
using i64 = long long;


signed main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int t;
    cin>>t;

    while(t--) {
        int x;
        [&]() {
            cin>>x;
            auto d = x;
            int k=x-(int)sqrt(x)*(int)sqrt(x);
            if(k == 0) {
                cout << 0 << '\n';
                cout << '\n';
                return;
            }
            auto it = 1LL;
            k=((int)sqrt(x)+it)*((int)sqrt(x)+it)-x;
            vector<int>a;
            auto st = set<int>{};
            while(k){
                auto flag = false;
                for(int i=k;i>=1;i--){
                    if(x%i==0&&st.contains(i)==0){
                        flag = true;
                        st.emplace(i);
                        a.push_back(i);
                        x+=i;
                        k-=i;
                        break;
                    }
                }
                if(not flag) {
                    ++it;
                    x = d;
                    k = ((int)sqrt(x)+it)*((int)sqrt(x)+it)-x;
                    st.clear();
                    a.clear();
                }
                assert(k >= 0);
            }


            cout<<a.size()<<'\n';
            for(int i=0;i<a.size();i++){
                cout<<a[i]<<' ';
            }
            cout<<'\n';
        }();
    }
    return 0;
}
