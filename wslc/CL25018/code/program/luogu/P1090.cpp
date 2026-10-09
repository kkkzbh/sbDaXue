

#ifdef P1090

#include<iostream>
#include<queue>
#include<iterator>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cout.tie(nullptr);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::istream_iterator<int> is(std::cin);
    std::istream_iterator<int> end;
    std::priority_queue<int,std::vector<int>,std::greater<>> que(is,end);
    int sum = 0;
    int ans = 0;
    while(que.size() > 1)
    {
        sum += que.top();
        que.pop();
        sum += que.top();
        que.pop();
        que.push(sum);
        ans += sum;
        sum = 0;
    }
    std::cout << ans;

    return 0;
}

#endif
