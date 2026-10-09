#include <bits/stdc++.h>
using namespace std;
#define int long long
using i64 = long long;


signed main()
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);
    int t;
    cin>>t;
    auto mt193 = std::mt19937{ std::random_device{}() };
    auto rd = std::uniform_int_distribution(10000LL,10000000LL);

    while(t--) {
        [&]() {
            int x;
            cin>>x;
            // x = rd(mt193);
            // std::cout << x << std::endl;
            auto d = x;
            auto bq = i64(sqrt(x));
            int k = x - bq * bq;
            if(k == 0) {
                cout << 0 << '\n';
                cout << '\n';
                return;
            }
            ++bq;
            k= bq * bq -x;
            vector<int>a;
            auto st = set<int>{};
            while(k){
                auto flag = false;
                for(int i=k;i>=*++st.rbegin() ;i--){
                    if(x%i==0&&st.contains(i)==0) {
                        flag = true;
                        st.emplace(i);
                        a.push_back(i);
                        x+=i;
                        k-=i;
                        break;
                    }
                }
                if(not flag) {
                    // std::cout << bq << std::endl;
                    bq += 1;
                    x = d;
                    k = bq * bq -x;
                    st.clear();
                    a.clear();
                }
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
