#include<iostream>
#include<list>

struct node
{
    int index;
    int power;
    node() = default;
    node(int i,int p) : index(i),power(p){}
    node& operator=(const node& n)
    {
        index = n.index;
        power = n.power;
        return *this;
    }
};

inline std::istream& operator>>(std::istream& is,std::list<node>& p)
{
    int n;
    is >> n;
    int index,power;
    for(int i = 1; i <= n;++i)
    {
        is >> index >> power;
        p.emplace_back(index,power);
    }
    return is;
}

std::list<node> operator*(const std::list<node>& p1,const std::list<node>& p2)
{
    std::list<node> p;
    for(auto i = p1.begin(); i != p1.end();++i)
    {
        auto it = p.begin();
        for(auto j = p2.begin(); j != p2.end();)
        {
            if(it == p.end())
            {
                p.emplace_back(i->index * j->index,i->power + j->power);
                ++j;
            }
            else if(it->power > i->power + j->power)
            {
                ++it;
            }
            else if(it->power < i->power + j->power)
            {
                p.insert(it,node(i->index * j->index,i->power + j->power));
                ++j;
            }
            else
            {
                it->index += i->index * j->index;
                ++j;
                if(!it->index)
                    it = p.erase(it);
            }
        }
    }
    return p;
}

std::list<node> operator+(const std::list<node>& l1,const std::list<node>& l2)
{
    std::list<node> l;
    auto ita = l1.begin();
    auto enda = l1.end();
    auto itb = l2.begin();
    auto endb = l2.end();
    while(ita != enda && itb != endb)
    {
        if(ita->power > itb->power)
        {
            l.emplace_back(ita->index,ita->power);
            ++ita;
        }
        else if(ita->power < itb->power)
        {
            l.emplace_back(itb->index,itb->power);
            ++itb;
        }
        else
        {
            if(ita->index + itb->index)
            {
                l.emplace_back(ita->index + itb->index,ita->power);
            }
            ++ita;
            ++itb;
        }
    }
    while(ita != enda)
    {
        l.emplace_back(ita->index,ita->power);
        ++ita;
    }
    while(itb != endb)
    {
        l.emplace_back(itb->index,itb->power);
        ++itb;
    }
    return l;
}

void print(const std::list<node>& l)
{
    if(l.empty())
    {
        std::cout << 0 << ' ' << 0;
    }
    else
    {
        int flag = 1;
        for(auto it : l)
        {
            if(flag) flag = 0; else std::cout << ' ';
            std::cout << it.index << ' ' << it.power;
        }
    }
}

int main()
{
    std::list<node> l1;
    std::list<node> l2;
    std::cin >> l1 >> l2;
    print(l1 * l2);
    std::cout << '\n';
    print(l1 + l2);

    return 0;
}