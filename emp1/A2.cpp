#include<bits/stdc++.h>
using namespace std;

#define print(...) std::cout << std::format(__VA_ARGS__)
#define println(...) print(__VA_ARGS__) << '\n'

int main()
{
    int n;
    cin>>n;
    vector<int>a(n+1,0);
    for(int i=1;i<=n;i++) {
        cin>>a[i];
    }
    int pos=1;
    int sum=0;
    vector<int>s;
    while(pos<=n) {
        sum=0;
        if(pos<=n&&a[pos]==1) {
            while(pos<=n&&a[pos]==1) {
                pos++;
                sum++;
            }
        }
        if(pos<=n&&a[pos]==2) {
            while(pos<=n&&a[pos]==2) {
                sum++;
                pos++;
            }
        }
        s.push_back(sum);
    }
    //println("{}",s);
    int mx=0;
    if(s.size()==1) {
        cout<<s[0]<<endl;
        return 0;
    }
    for(int i=0;i<(int)s.size()-1;i++){
        mx=max(mx,s[i]+s[i+1]);
    }
    cout<<mx<<endl;
    return 0;
}