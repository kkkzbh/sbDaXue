
#pragma once

#include"../header/print.h"
#include<stack>
#include<stdexcept>
#include<queue>
#include<functional>
#include"algotree.h"
#include"decl.h"


template<typename T>
struct basic_node
{
    T val{};
    basic_node* left{nullptr };
    basic_node* right{nullptr };
    basic_node() = default;
    basic_node(const T& v) : val(v){}
};

template<typename T>
struct basic_binary_tree
{
    using node = basic_node<T>;

    node* head{ nullptr };

    virtual ~basic_binary_tree()
    {
        clear();
    }

    void clear()
    {
        if(!head)
            return;
        M_del(head);
        head = nullptr;
    }

    virtual void preorder() const
    {
        std::stack<node*> stk;
        node* it = head;
        while(!stk.empty() || it)
        {
            if(it)
            {
                visit(it);
                stk.push(it);
                it = it->left;
            }
            else
            {
                it = stk.top();
                stk.pop();
                it = it->right;
            }
        }
    }

    template<typename F>
    void preorder(std::function<void(F*)> vis) const
    {
        std::stack<node*> stk;
        node* it{ head };
        while(!stk.empty() || it)
        {
            if(it)
            {
                vis(cast<F>(it));
                stk.push(it);
                it = it->left;
            }
            else
            {
                it = stk.top();
                stk.pop();
                it = it->right;
            }
        }
    }

    virtual void inorder() const
    {
        std::stack<node*> stk;
        node* it{ head };
        while(!stk.empty() || it)
        {
            if(it)
            {
                stk.push(it);
                it = it->left;
            }
            else
            {
                it = stk.top();
                visit(it);
                stk.pop();
                it = it->right;
            }
        }
    }

    template<typename F>
    void inorder(std::function<void(F*)> vis) const
    {
        std::stack<node*> stk;
        node* it{ head };
        while(!stk.empty() || it)
        {
            if(it)
            {
                stk.push(it);
                it = it->left;
            }
            else
            {
                it = stk.top();
                vis(cast<F>(it));
                stk.pop();
                it = it->right;
            }
        }
    }

    virtual void postorder() const
    {
        std::stack<node*> stk;
        node* it = head;
        while(!stk.empty() || it)
        {
            if(it)
            {
                stk.push(it);
                it = it->left;
            }
            else if(long long v{ reinterpret_cast<long long>(stk.top()) }; v > 0)
            {
                it = stk.top()->right;
                stk.top() = reinterpret_cast<node*>(-v);
            }
            else
            {
                visit(reinterpret_cast<node*>(-v));
                stk.pop();
            }
        }
    }

    template<typename F>
    void postorder(std::function<void(F*)> vis) const
    {
        std::stack<node*> stk;
        node* it{ head };
        while(!stk.empty() || it)
        {
            if(it)
            {
                stk.push(it);
                it = it->left;
            }
            else if(long long v{ reinterpret_cast<long long>(stk.top()) }; v > 0)
            {
                it = stk.top()->right;
                stk.top() = reinterpret_cast<F*>(-v);
            }
            else
            {
                vis(reinterpret_cast<F*>(-v));
                stk.pop();
            }
        }
    }

    virtual void rpostorder() const
    {

    }

    virtual void levelorder() const
    {
        std::queue<node*> que;
        if(head)
            que.push(head);
        while(!que.empty())
        {
            for(std::size_t i{},cei{ que.size() }; i != cei; ++i)
            {
                node* v = que.front();
                visit(v);
                que.pop();
                if(v->left)
                    que.push(v->left);
                if(v->right)
                    que.push(v->right);
            }
        }
    }

    template<typename F>
    void levelorder(std::function<void(F*)> vis) const
    {
        std::queue<node*> que;
        if(head)
            que.push(head);
        while(!que.empty())
        {
            for(std::size_t i{},cei{ que.size() }; i != cei; ++i)
            {
                node* v = que.front();
                vis(cast<F>(v));
                que.pop();
                if(v->left)
                    que.push(v->left);
                if(v->right)
                    que.push(v->right);
            }
        }
    }

    template<typename M_node = node>
    void tmp_create()
    {
        clear();
        head = new  M_node(2);
        head->left = new M_node(30);
        head->right = new M_node(15);
        auto l = head->left;
        auto r = head->right;
        l->left = new M_node(5);
        l->left->right = new M_node(7);
        r->left = new M_node(3);
        r->right = new M_node(999);
    }


    template<typename M_node = node>
    void pre_create(const T& null = T{})   //默认基于std::cin
    {
        clear();
        std::stack<M_node*> stk;
        T val;
        std::cin >> val;
        M_node** it = &reinterpret_cast<M_node*>(head);
        while(!stk.empty() || val != null)
        {
            if(val != null)
            {
                (*it) = new M_node(val);
                stk.push(*it);
                it = &(*it)->left;
                std::cin >> val;
            }
            else
            {
                it = &(stk.top()->right);
                stk.pop();
                std::cin >> val;
            }
        }
    }

    template<typename It,typename M_node = node>
    void picreate(const It* in_beg,const It* in_end,const It* pre_beg)
    {
        clear();
        M_pic(in_beg,in_end,pre_beg,cast<M_node>(head));
    }

    template<typename It,typename M_node = node>
    void bicreate(const It* in_beg,const It* in_end,const It* back_end)
    {
        clear();
        M_bic(in_beg,in_end,back_end - 1,cast<M_node>(head));
    }

protected:

    template<typename It,typename M_node>
    static void M_pic(const It* in_beg,const It* in_end,const It* pre_beg,M_node*& it)
    {
        if(in_beg == in_end)
            return;
        const It* i{ in_beg };
        while(*i != *pre_beg)
            ++i;
        it = new M_node(*pre_beg);
        M_pic(in_beg,i,pre_beg + 1,cast<M_node>(it->left));
        M_pic(i + 1,in_end,pre_beg + 1 + (i - in_beg),cast<M_node>(it->right));
    }

    template<typename It,typename M_node>
    static void M_bic(const It* in_beg,const It* in_end,const It* back_end,M_node*& it)
    {
        if(in_beg == in_end)
            return;
        const It* i{ in_beg };
        while(*i != *back_end)
            ++i;
        it = new M_node(*back_end);
        M_bic(in_beg,i,back_end - (in_end - i),cast<M_node>(it->left));
        M_bic(i + 1,in_end,back_end - 1,cast<M_node>(it->right));
    }

    virtual void visit(node* it) const noexcept
    {
        print("{} ",it->val);
    }

    void M_del(node* it)
    {
        if(it->left)
            M_del(it->left);
        if(it->right)
            M_del(it->right);
        delete it;
    }

    template<typename C,typename M_node>
    __attribute__((always_inline))
    constexpr static C*& cast(M_node*& ptr) noexcept
    {
        return reinterpret_cast<C*&>(ptr);
    }

    template<typename C,typename M_node>
    __attribute__((always_inline))
    constexpr static const C*& cast(const M_node*& ptr) noexcept
    {
        return reinterpret_cast<const C*&>(ptr);
    }

    static void M_null_tree()
    {
        throw std::out_of_range("The basic_binary_tree is null");
    }
};