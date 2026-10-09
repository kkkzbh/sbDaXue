#pragma once

#include"basic_binary_tree.h"

template<typename T>
struct thrnode : public basic_node<T>
{
    bool ltag{};
    bool rtag{};
    thrnode() = default;
    using basic_node<T>::basic_node;
};

template<typename T>
struct thr_binary_tree : public basic_binary_tree<T>
{
    using thrnode = thrnode<T>;
    using typename basic_binary_tree<T>::node;
    using basic_binary_tree<T>::head;

    using pre_iterator = Thr_pre_It<T>;
    using in_iterator = Thr_in_It<T>;
    using post_iterator = Thr_post_It<T>;
    using reverse_post_iterator = Thr_post_rIt<T>;

    ~thr_binary_tree()
    {
        if(!head)
            return;
        M_del(cast<thrnode>(head));
        head = nullptr;
    }

    [[nodiscard]]
    __attribute__((always_inline))
    node* prebegin() const noexcept
    {
        return head;
    }

    [[nodiscard]]
    __attribute__((always_inline))
    node* preend() const noexcept
    {
        return nullptr;
    }

    [[nodiscard]]
    __attribute__((always_inline))
    node* inbegin() const noexcept
    {
        node* it{ head };
        if(it)
            while(!cast<thrnode>(it)->ltag && it->left)
                it = it->left;
        return it;
    }

    [[nodiscard]]
    __attribute__((always_inline))
    node* inend() const noexcept
    {
        return nullptr;
    }

    [[nodiscard]]
    __attribute__((always_inline))
    node* postbegin() const noexcept
    {
        node* it{ head };
        if(it)
            do
            {
                while (!cast<thrnode>(it)->ltag && it->left)
                    it = it->left;
            } while (!cast<thrnode>(it)->rtag && it->right ? it = it->right : nullptr);
        return it;
    }

    [[nodiscard]]
    __attribute__((always_inline))
    node* postend() const noexcept
    {
        return nullptr;
    }

    [[nodiscard]]
    __attribute__((always_inline))
    node* postrbegin() const noexcept
    {
        return prebegin();
    }

    [[nodiscard]]
    __attribute__((always_inline))
    node* postrend() const noexcept
    {
        return nullptr;
    }

    void prethread()
    {
        node* pre{ nullptr };
        std::stack<node*> stk;
        node* it { head };
        while(!stk.empty() || it)
        {
            if(it)
            {
                M_thread(cast<thrnode>(it),cast<thrnode>(pre));
                stk.push(it);
                it = cast<thrnode>(it)->ltag ? nullptr : it->left;
            }
            else
            {
                it = stk.top();
                stk.pop();
                it = cast<thrnode>(it)->rtag ? nullptr : it->right;
            }
        }
    }

    void inthread()
    {
        std::stack<node*> stk;
        node* it{ head };
        node* pre{ nullptr };
        while(!stk.empty() || it)
        {
            if(it)
            {
                stk.push(it);
                it = cast<thrnode>(it)->ltag ? nullptr : it->left;
            }
            else
            {
                it = stk.top();
                M_thread(cast<thrnode>(it),cast<thrnode>(pre));
                stk.pop();
                it = cast<thrnode>(it)->rtag ? nullptr : it->right;
            }
        }
    }

    void postthread()
    {
        std::stack<node*> stk;
        node* it = head;
        node* pre{ nullptr };
        while(!stk.empty() || it)
        {
            if(it)
            {
                stk.push(it);
                it = cast<thrnode>(it)->ltag ? nullptr : it->left;
            }
            else if(long long v{ reinterpret_cast<long long>(stk.top()) }; v > 0)
            {
                it = cast<thrnode>(stk.top())->rtag ? nullptr : stk.top()->right;
                stk.top() = reinterpret_cast<thrnode*>(-v);
            }
            else
            {
                M_thread(reinterpret_cast<thrnode*>(-v),cast<thrnode>(pre));
                stk.pop();
            }
        }
    }

protected:

    void M_del(thrnode* it)
    {
        if(it->left && !it->ltag)
            M_del(cast<thrnode>(it->left));
        if(it->right && !it->rtag)
            M_del(cast<thrnode>(it->right));
        delete it;
    }

    void M_thread(thrnode* it,thrnode*& pre)
    {
        if(!it->left)
        {
            it->left = pre;
            it->ltag = true;
        }
        if(pre && !pre->right)
        {
            pre->right = it;
            pre->rtag = true;
        }
        pre = it;
    }
};

template<typename T>
struct pre_thrtree : public thr_binary_tree<T>
{
    using typename thr_binary_tree<T>::node;
    using typename thr_binary_tree<T>::thrnode;
    using iterator = typename thr_binary_tree<T>::pre_iterator;
    using thr_binary_tree<T>::head;

    ~pre_thrtree()
    {
        for(auto beg{ begin() },end{ this->end() }; beg != end;)
            delete reinterpret_cast<thrnode*>((beg++).point());
        head = nullptr;
    }

    iterator begin() const noexcept
    {
        return iterator{ this->prebegin() } ;
    }

    iterator end() const noexcept
    {
        return iterator{ this->preend() };
    }

    void preorder() const override
    {
        for(auto beg = this->begin(),end = this->end(); beg != end; ++beg)
            this->visit(beg);
    }

    template<typename F>
    void preorder(std::function<void(F*)> vis) const
    {
        for(auto beg = this->begin(),end = this->end(); beg != end; ++beg)
            vis(beg);
    }

};

template<typename T>
struct in_thrtree : public thr_binary_tree<T>
{
    using typename thr_binary_tree<T>::node;
    using typename thr_binary_tree<T>::thrnode;
    using iterator = typename thr_binary_tree<T>::in_iterator;
    using thr_binary_tree<T>::head;

    ~in_thrtree()
    {
        for(auto beg{ begin() },end{ this->end() }; beg != end;)
            delete reinterpret_cast<thrnode*>((beg++).point());
        head = nullptr;
    }

    iterator begin() const noexcept
    {
        return iterator{ this->inbegin() };
    }

    iterator end() const noexcept
    {
        return iterator{ this->inend() };
    }

    void inorder() const override
    {
        for(auto beg = this->begin(),end = this->end(); beg != end; ++beg)
            this->visit(beg);
    }

    template<typename F>
    void inorder(std::function<void(F*)> vis) const
    {
        for(auto beg = this->begin(),end = this->end(); beg != end; ++beg)
            vis(beg);
    }
};

template<typename T>
struct post_thrtree : public thr_binary_tree<T>
{
    using typename thr_binary_tree<T>::node;
    using typename thr_binary_tree<T>::thrnode;
    using iterator = typename thr_binary_tree<T>::post_iterator;
    using reverse_iterator = typename thr_binary_tree<T>::reverse_post_iterator;
    using thr_binary_tree<T>::head;

    ~post_thrtree()
    {
        for(auto beg{ rbegin() },end{ this->rend() }; beg != end;)
            delete reinterpret_cast<thrnode*>((beg++).point());
        head = nullptr;
    }

    reverse_iterator rbegin() const noexcept
    {
        return reverse_iterator { this->postrbegin() } ;
    }

    reverse_iterator rend() const noexcept
    {
        return reverse_iterator { this->postrend() };
    }

    void rpostorder() const override
    {
        for(auto beg = this->rbegin(),end = this->rend(); beg != end; ++beg)
            this->visit(beg);
    }

    template<typename F>
    void rpostorder(std::function<void(F*)> vis) const
    {
        for(auto beg = this->rbegin(),end = this->rend(); beg != end; ++beg)
            vis(beg);
    }
};



