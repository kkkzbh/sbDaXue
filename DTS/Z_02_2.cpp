

#include<iostream>
#include<iomanip>
constexpr int null = -1;
constexpr int size = 1e5 + 10;

struct node
{
    int position;
    int data;
    int next;
};

node a[size];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int head = null;
    int k;
    int n;
    std::cin >> head >> n >> k;
    int t_position;
    int t_data;
    int t_next;
    while(n--)
    {   
        std::cin >> t_position >> t_data >> t_next;
        a[t_position].position = t_position;
        a[t_position].data = t_data;
        a[t_position].next = t_next;
    }
    int it = head;
    int back = a[it].next;
    int front = null;
    int sz = 0;
    while(it != null)
    {
        ++sz;
        it = a[it].next;
    }
    it = head;
    while(sz - k > 0)
    {
        int h = it;
        int fh = front;
        for(int i = 1; i <= k;++i)
        {
            a[it].next = front;
            front = it;
            it = back;
            back = a[back].next;
        }
        a[h].next = it;
        if(fh == null)
        {
            head = front;
        }
        else a[fh].next = front;
        front = h;
        sz -= k;
    }
    it = head;
    while(it != null)
    {
        std::cout << std::setw(5) << std::setfill('0')  << a[it].position << ' ' << a[it].data << ' ';
        if(a[it].next != null) std::cout << std::setw(5) << std::setfill('0');
        std::cout << a[it].next << '\n';
        it = a[it].next;
    }

    return 0;
}