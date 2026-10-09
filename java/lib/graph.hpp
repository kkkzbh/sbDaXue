#pragma once

#include<iostream>
#include"vector.hpp"
#include"list.hpp"
#include"queue.hpp"
#include"stack.hpp"
#include"heap.hpp"
#include"set.hpp"

namespace matrix
{

#define INFINITY_INT 147483647

template<class T>
class __graph;

template<class T>
struct __side_node;

template<class T>
class dircted_graph;

template<class T>
class undircted_graph;

template<class T>
class __graph
{
protected:
    vector<vector<T>> G;
    int point_size;
    int side_size;
    vector<vector<T>> path;
public:
    inline __graph(int n);
    inline __graph(int n,const T& max);
    inline virtual ~__graph();
    void clearv();
    void clearv(const T& max);
    virtual void insert(const __side_node<T> &node) = 0;
    virtual void insert(const int& v1,const int& v2,const T& weigh) = 0;
    bool Floyd();
    int getLowerPath(int v1,int v2);
};

template<class T>
__graph<T>::__graph(int n) : G(n,vector<T>(n)),point_size(n),side_size(0),path(n){}

template <class T>
__graph<T>::__graph(int n, const T& max) : G(n,vector<T>(n,max)),point_size(n),side_size(0),path(n)
{
    for(int i = 0;i<point_size;++i)
    {
        G[i][i] = 0;
        for(int j = 0;j<point_size;++j)
        {
            path[i][j] = -1;
        }
    }
}

template<class T>
__graph<T>::~__graph(){}

template<class T>
auto __graph<T>::Floyd() -> bool
{
    for(int k = 0;k<point_size;++k)
    {
        for(int i = 0;i<point_size;++i)
        {
            if(G[i][k] == INFINITY_INT) continue;
            for(int j = 0;j<point_size;++j)
            {
                if(i == j && G[i][j] < 0) return false; // 说明存在负环
                if(G[i][k] + G[k][j] < G[i][j])
                {
                    G[i][j] = G[i][k] + G[k][j];
                    path[i][j] = k;
                }
            }
        }
    }
    return true;
}

template<class T>
auto __graph<T>::clearv() -> void
{
    for(int i = 0;i<point_size;++i)
    {
        for(int j = 0;j<point_size;++j)
        {
            path[i][j] = -1;
            G[i][j] = 0;
        }
    }
}

template<class T>
auto __graph<T>::clearv(const T& max) -> void
{
    for(int i = 0;i<point_size;++i)
    {
        for(int j = 0;j<point_size;++j)
        {
            path[i][j] = -1;
            G[i][j] = max;
        }
        G[i][i] = 0;
    }
}

template<class T>
auto __graph<T>::getLowerPath(int v1, int v2) -> int
{
    std::cout << v1;
    int count = G[v1][v2];
    while(path[v1][v2] != -1)
    {
        v1 = path[v1][v2];
        std::cout << ' ' << v1;
    }
    std::cout << ' ' << v2;
    return count;
}


template<class T>
struct __side_node
{
    int v1;
    int v2;
    T weigh;
};

template<class T>
class dircted_graph : public __graph<T>
{
protected:
public:
    inline dircted_graph(int n);
    inline dircted_graph(int n,const T& max);
    inline virtual ~dircted_graph();
    inline virtual void insert(const __side_node<T>& node) override;
    inline virtual void insert(const int& v1,const int& v2,const T& weigh) override;
};

template<class T>
dircted_graph<T>::dircted_graph(int n) : __graph<T>(n){}

template <class T>
inline dircted_graph<T>::dircted_graph(int n, const T &max) : __graph<T>(n,max){}

template <class T>
dircted_graph<T>::~dircted_graph() {}

template<class T>
void dircted_graph<T>::insert(const __side_node<T> &node)
{
    this->G[node.v1][node.v2] = node.weigh;
    ++this->side_size;
}

template<class T>
void dircted_graph<T>::insert(const int& v1, const int& v2, const T& weigh)
{
    this->G[v1][v2] = weigh;
    ++this->side_size;
}

template<class T>
class undircted_graph : public __graph<T>
{
protected:
public:
    inline undircted_graph(int n);
    inline undircted_graph(int n,const T& max);
    inline virtual ~undircted_graph();
    inline virtual void insert(const __side_node<T>& node) override;
    inline virtual void insert(const int& v1,const int& v2,const T& weigh) override;
};

template<class T>
undircted_graph<T>::undircted_graph(int n) : __graph<T>(n){}

template <class T>
inline undircted_graph<T>::undircted_graph(int n, const T &max) : __graph<T>(n,max){}

template <class T>
undircted_graph<T>::~undircted_graph() {}

template<class T>
void undircted_graph<T>::insert(const __side_node<T> &node)
{
    this->G[node.v1][node.v2] = node.weigh;
    this->G[node.v2][node.v1] = node.weigh;
    ++this->side_size;
}

template<class T>
inline void undircted_graph<T>::insert(const int& v1,const int& v2,const T& weigh)
{
    this->G[v1][v2] = weigh;
    this->G[v2][v1] = weigh;
    ++this->side_size;
}

}

//************************************************************************************************//

namespace table
{

template<class T>
class undircted_graph;

template<class T>
class dircted_graph;

#define INFINITY_INT 147483647

template<class T>
struct table
{
    int v;
    T weigh;

    table():v(-1){}
    table(int vt,const T& w):v(vt),weigh(w){}
};

template<class T>
class __graph
{
protected:
    vector<single_list<table<T>>> G;
    int point_size;
    int side_size;
    vector<T> dist;
    vector<int> path;
    vector<bool> container;
public:
    inline __graph(int n);
    inline __graph(int n,const T& max_weigh);
    virtual inline ~__graph();
    virtual void insert(const matrix::__side_node<T>& node) = 0;
    virtual void insert(int v1,int v2,const T& weigh) = 0;
    void DFS(int v);
    void clearv();
    virtual void visit(int v);
    void BFS(int v);
    void unweighed_path(int v);
    void Dijkstra(int v);
    int getLowerPath(int v1,int v2);
    int Prim(undircted_graph<T>& MST);
    auto Kruskal(undircted_graph<T>& MST) -> int;
    auto Topsort() -> bool;
};

template<class T>
__graph<T>::__graph(int n) : G(n),point_size(n),side_size(0),dist(n),path(n),container(n)
{
    for(int i = 0;i<n;++i)
    {
        dist[i] = -1;
        path[i] = -1;
    }
}

template<class T>
__graph<T>::__graph(int n, const T &max_weigh) : G(n),point_size(n),dist(n),path(n),container(n)
{
    for(int i = 0;i<n;++i)
    {
        dist[i] = max_weigh;
        path[i] = -1;
    }
}

template<class T>
__graph<T>::~__graph(){}


template<class T>
void __graph<T>::DFS(int v)
{
    dist[v] = 1;
    visit(v);
    for(auto i = G[v].begin(); i != G[v].end();++i)
    {
        if(!dist[i->element.v])
        {
            DFS(i->element.v);
        }
    }
}

template<class T>
void __graph<T>::BFS(int v)
{
    queue<int> qv;
    qv.push(v);
    dist[v] = 1;
    visit(v);
    int V;
    while(!qv.empty())
    {
        V = qv.front();
        qv.pop();
        for(auto i = G[V].begin(); i != G[V].end();++i)
        {
            if(!dist[i->element.v])
            {
                qv.push(i->element.v);
                dist[i->element.v] = 1;
                visit(i->element.v);
            }
        }
    }
}

template<class T>
void __graph<T>::clearv()
{
    for(int i = 0;i < point_size;++i)
    {
        dist[i] = -1;
        path[i] = -1;
        container[i] = false;
    }
}

template<class T>
void __graph<T>::visit(int v)
{
    std::cout << "正在访问第" << v << "个节点\n";
}

template<class T>
auto __graph<T>::unweighed_path(int v) -> void
{
    queue<int> que;
    que.push(v);
    dist[v] = 0;
    int V;
    while(!que.empty())
    {
        V = que.front();
        que.pop();
        for(auto i = G[V].begin();i != G[V].end();++i)
        {
            if(dist[i->element.v] == -1)
            {
                que.push(i->element.v);
                dist[i->element.v] = dist[V] + 1;
                path[i->element.v] = V;
            }
        }
    }
}

template<class T>
auto __graph<T>::Dijkstra(int v) -> void
{
    int V = v;
    dist[V] = 0;
    T tmpdist = 0;
    while(tmpdist != INFINITY_INT)
    {
        container[V] = true;
        for(auto x = G[V].begin();x != G[V].end();++x)
        {
            if(!container[x->element.v] && dist[V] + x->element.weigh < dist[x->element.v])
            {
                dist[x->element.v] = dist[V] + x->element.weigh;
                path[x->element.v] = V;
            }
        }
        tmpdist = INFINITY_INT;
        for(int i = 0;i != point_size;++i)
        {
            if (!container[i] && dist[i] < tmpdist)
            {
                V = i;
                tmpdist = dist[i];
            }
        }
    }
}

template<class T>
auto __graph<T>::getLowerPath(int v1, int v2) -> int
{
    if(v1 == v2)
    {
        return 0;
    }
    stack<int> stk;
    int v = v2;
    while(path[v] != -1)
    {
        stk.push(v);
        v = path[v];
    }
    std::cout << v1;
    while(!stk.empty())
    {
        v = stk.top();
        std::cout << ' ' << v;
        stk.pop();
    }
    return dist[v2];
}

template<class T>
auto __graph<T>::Prim(undircted_graph<T>& MST) -> int
{
    int v = 0;
    T tmpdist = 0;
    dist[v] = 0;
    int Vcount = 0;
    int weigh = 0;
    while(tmpdist != INFINITY_INT)
    {
        ++Vcount;
        for(auto x = G[v].begin(); x!= G[v].end();++x)
        {
            if(dist[x->element.v] && x->element.weigh < dist[x->element.v])
            {
                dist[x->element.v] = x->element.weigh;
                path[x->element.v] = v;
            }
        }
        tmpdist = INFINITY_INT;
        for(int i = 0;i<point_size;++i)
        {
            if(dist[i] && dist[i] < tmpdist)
            {
                v = i;
                tmpdist = dist[i];
            }
        }
        if(tmpdist != INFINITY_INT)
        {
            weigh += dist[v];
            MST.insert(path[v], v, dist[v]);
            dist[v] = 0;
        }
    }
    if(point_size == Vcount)
        return weigh;
    else
        return -1;
}

template<class T>
auto __graph<T>::Kruskal(undircted_graph<T> &MST) -> int
{
    struct node
    {
        int v1;
        int v2;
        T weigh;
        node():v1(0),v2(0){}
        node(int x,int y,const T& z) : v1(x),v2(y),weigh(z){}
        inline bool operator>(const node& nd) const
        {
            return weigh > nd.weigh;
        }
    }tmp;
    heap<node,vector<node>,greater<node>> hp;
    array::eff_set set((size_t)point_size);
    for(int i = 0;i<point_size;++i)
    {
        set.insert(i);
    }
    for(int v = 0;v<point_size;++v)
    {
        for(auto x = G[v].begin(); x != G[v].end();++x)
        {
            if(v < x->element.v)
            {
                hp.push(node(v,x->element.v,x->element.weigh));
            }
        }
    }
    T weigh = 0;
    int Ecount = 0;
    while(Ecount != point_size-1 && !hp.empty())
    {
        tmp = hp.top();
        hp.pop();
        if(!set.judge(tmp.v1,tmp.v2))
        {
            set.uni(tmp.v1,tmp.v2);
            weigh += tmp.weigh;
            ++Ecount;
            MST.insert(tmp.v1,tmp.v2,tmp.weigh);
        }
    }
    if(point_size-1 == Ecount)
        return weigh;
    else
        return -1;
}

template<class T>
auto __graph<T>::Topsort() -> bool
{
    int Indegree[point_size] = {0};
    for(int v = 0;v<point_size;++v)
    {
        for(auto it = G[v].begin();it != G[v].end();++it)
        {
            ++Indegree[it->element.v];
        }
    }
    queue<int> que;
    for(int v = 0;v<point_size;++v)
    {
        if (!Indegree[v])
        {
            que.push(v);
            std::cout << v << ' ';
        }
    }
    int count = 0;
    std::cout << '\n';
    int tmp = que.back();
    while(!que.empty())
    {
        for(auto it = G[que.front()].begin();it != G[que.front()].end();++it)
        {
            if(!--Indegree[it->element.v])
            {
                que.push(it->element.v);
                std::cout << it->element.v << ' ';
            }
        }
        if(que.front() == tmp)
        {
            std::cout << '\n';
            tmp = que.back();
        }
        que.pop();
        ++count;
    }
    if(point_size != count)
        return false;
    return true;
}


template<class T>
class undircted_graph : public __graph<T>
{
protected:
public:
    inline undircted_graph(int n);
    inline undircted_graph(int n,const T& weigh_max);
    virtual inline ~undircted_graph();
    virtual inline void insert(const matrix::__side_node<T>& node) override;
    virtual inline void insert(int v1,int v2,const T& weigh) override;
};

template<class T>
undircted_graph<T>::undircted_graph(int n):__graph<T>(n){}

template<class T>
undircted_graph<T>::undircted_graph(int n,const T& weigh_max):__graph<T>(n,weigh_max){}

template<class T>
undircted_graph<T>::~undircted_graph(){}

template<class T>
void undircted_graph<T>::insert(const matrix::__side_node<T>& node)
{
    this->G[node.v1].push_up(table<T>(node.v2,node.weigh));
    this->G[node.v2].push_up(table<T>(node.v1,node.weigh));
    ++++this->side_size;
}

template <class T>
void undircted_graph<T>::insert(int v1, int v2, const T &weigh)
{
    this->G[v1].push_up(table<T>(v2,weigh));
    this->G[v2].push_up(table<T>(v1,weigh));
    ++++this->side_size;
}


template<class T>
class dircted_graph : public __graph<T>
{
protected:
public:
    inline dircted_graph(int n);
    inline dircted_graph(int n,const T& weigh_max);
    virtual inline ~dircted_graph();
    virtual inline void insert(const matrix::__side_node<T>& node) override;
    virtual inline void insert(int v1,int v2,const T& weigh) override;
};

template<class T>
dircted_graph<T>::dircted_graph(int n):__graph<T>(n){}

template<class T>
dircted_graph<T>::dircted_graph(int n,const T& weigh_max) : __graph<T>(n,weigh_max){}

template<class T>
dircted_graph<T>::~dircted_graph(){}

template<class T>
void dircted_graph<T>::insert(const matrix::__side_node<T>& node)
{
    this->G[node.v1].push_up(table<T>(node.v2,node.weigh));
    ++this->side_size;
}

template <class T>
void dircted_graph<T>::insert(int v1, int v2, const T &weigh)
{
    this->G[v1].push_up(table<T>(v2,weigh));
    ++this->side_size;
}




}



















