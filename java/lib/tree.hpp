#pragma once

#include<iostream>
#include"stack.hpp"
#include"queue.hpp"
using size_t =  unsigned long long;
#define MAX(A,B) ((A) > (B) ? (A) : (B))
#define MIN(A,B) ((A) > (B) ? (B) : (A))

template<class T>
class BST;

template<class T>
class AVL;

namespace list
{

template<class T>
class tree;

template<class T>
bool isomorphism(const tree<T>* tr1,const tree<T>* tr2);

template<class T>
class tree
{
    friend class BST<T>;
    friend class AVL<T>;
    friend bool isomorphism<T>(const tree<T>* tr1,const tree<T>* tr2);
private:
    T element;
    tree<T>* left;
    tree<T>* right;
    void create();
    size_t _heigh;
    tree(const T& ele);
public:
    tree() = delete;
    tree(const tree<T>& tr) = delete;
    virtual ~tree();
    void preorder();
    void inorder();
    void postorder();
    void queorder();
    size_t heigh();
};


// template<class T>
// basic_binary_tree<T>::basic_binary_tree(): element(),left(nullptr),right(nullptr){}
template<class T>
tree<T>::tree(const T& ele): element(ele),left(nullptr),right(nullptr),_heigh(1){}

template<class T>
tree<T>::~tree()
{
    if(left)
        delete left;
    if(right)
        delete right;
}

template<class T>
inline size_t tree<T>::heigh()
{
    return MAX((left ? left->_heigh : 0),(right ? right->_heigh : 0)) + 1; 
}


template<class T>
void tree<T>::create()
{
    left = new tree<T>;
    left->left = new tree<T>;
    left->right = new tree<T>;
    left->left->left = new tree<T>;
    left->left->left->right = new tree<T>;
    right = new tree<T>;
    right->left = new tree<T>;
    right->right = new tree<T>;
    right->right->right = new tree<T>;
}

template<class T>
void tree<T>::preorder()
{
    if(!this)
        return;
    tree<T>* it = this;
    stack<tree<T>*> stk;
    tree<T>* lastv = it;
    stk.push(it);
    std::cout << it->element;
    while(!stk.empty())
    {
        while(it->left && lastv != it->left && lastv != it->right)
        {
            lastv = it;
            it = it->left;
            stk.push(it);
            std::cout << ' ' << it->element;
        }
        if(it->right && lastv != it->right)
        {
            lastv = it;
            it = it->right;
            stk.push(it);
            std::cout << ' ' << it->element;
        }
        else
        {
            lastv = it;
            stk.pop();
            it = stk.top();
        }
    }
}

template<class T>
void tree<T>::inorder()
{
    if(!this)
        return;
    tree<T>* it = this;
    stack<tree<T>*> stk;
    tree<T>* lastv = nullptr;
    stk.push(it);
    int find = 1;
    while(!stk.empty())
    {

        while(it->left && lastv != it->left && lastv != it->right)
        {
            lastv = it;
            it = it->left;
            stk.push(it);
        }
        if(lastv != it->right && (lastv == it->left || !it->left))
        {
            if(find) find = 0;
            else std::cout << ' ';
            std::cout << it->element;
        }
        if(it->right && lastv != it->right)
        {
            lastv = it;
            it = it->right;
            stk.push(it);
        }
        else
        {
            lastv = it;
            stk.pop();
            it = stk.top();
        }
    }
}

template<class T>
void tree<T>::postorder()
{
    if(!this)   //头是空的
        return;
    tree<T>* it = this;
    stack<tree<T>*> stk;
    tree<T>* lastv = nullptr;
    stk.push(it);
    int find = 0;
    while(!stk.empty())
    {
        while(it->left && lastv != it->left && lastv != it->right)
        {
            lastv = it;
            it = it->left;
            stk.push(it);
        }
        if(it->right && lastv != it->right)
        {
            lastv = it;
            it = it->right;
            stk.push(it);
        }
        else
        {
            lastv = it;
            stk.pop();
            if(find) find = 0;
            else std::cout << ' ';
            std::cout << it->element;
            it = stk.top();
        }
    }
}


template<class T>
void tree<T>::queorder()
{
    queue<tree<T>*> que;
    tree<T>* it = this;
    que.push(it);
    int find = 1;
    while(!que.empty())
    {
        it = que.front();
        que.pop();
        if(find) find = 0;
        else std::cout << ' ';
        std::cout << it->element;
        if(it->left)
            que.push(it->left);
        if(it->right)
            que.push(it->right);
    }
}


template<class T>
bool isomorphism(const tree<T>* tr1,const tree<T>* tr2)
{
    if(!tr1 && !tr2)
        return true;
    else if(!tr1 || !tr2)
        return false;
    if(tr1->element != tr2->element)
        return false;
    else
        return (isomorphism(tr1->left,tr2->left) && isomorphism(tr1->right,tr2->right)) ||
                (isomorphism(tr1->left,tr2->right) && isomorphism(tr1->right,tr2->left));
}

}

//********************            Array        *************************************//
#ifdef ARRAY_TREE

namespace array
{

#define __SIZE__ 15
#define null -1

template<class T>
struct node
{
    T element;
    int left;
    int right;

    node():element(),left(null),right(null){}
    ~node(){}
};

template<class T>
class basic_binary_tree
{
private:
    node<T>* tr;
    int root;
    size_t _size;
    size_t multiple;
public:
    basic_binary_tree(size_t n = __SIZE__);
    basic_treec_tree();
    void create(size_t n);
    void realloc(size_t n);
    int getroot();
    void preorder(int root);
    void inorder(int root);
    void postorder(int root);
    void queorder(int root);
};

template<class T>
basic_binary_tree<T>::basic_binary_tree(size_t n) :root(null),multiple(1+n/__SIZE__),_size(0),tr(new node<T>[n]){}

template<class T>
basic_binary_tree<T>::basic_treec_tree()
{
    delete[] tr;
}

template<class T>
void basic_binary_tree<T>::create(size_t n)
{
    if(n > multiple*__SIZE__)
        realloc(n);
    _size = n;
    int* table = new int[_size]();
    std::cout << "元素值  左  右    '-'表示无子节点\n";
    char tmp = 0;
    for(int i = 0;i<_size;++i)
    {
        std::cout << i+1 << " :";
        std::cin >> tr[i].element;
        std::cout << "  ";
        std::cin.ignore();
        if('-' != (tmp = std::cin.get()))
        {
            tr[i].left = tmp - '0';
            table[tr[i].left] = 1;
        }
        else  tr[i].left = null;
        std::cout << "  ";
        std::cin.ignore();
        if('-' != (tmp = std::cin.get()))
        {
            tr[i].right = tmp - '0';
            table[tr[i].right] = 1;
        }
        std::cout << '\n';
    }
    for(int i = 0;i<_size;++i)
    {
        if(!table[i])
        {
            root = i;
            break;
        }
    }
}

template<class T>
void basic_binary_tree<T>::realloc(size_t n)
{
    node<T>* tmp = tr;
    multiple = 1 + n/__SIZE__;
    tr = new node<T>[multiple*__SIZE__];
    for(int i = 0;i<_size;++i)
    {
        tr[i] = tmp[i];
    }
    delete[] tmp;
}

template<class T>
inline int basic_binary_tree<T>::getroot()
{
    return root;
}


template<class T>
void basic_binary_tree<T>::preorder(int root)
{
    if(null != root)
    {
        std::cout << tr[root].element << ' ';
        preorder(tr[root].left);
        preorder(tr[root].right);
    }
}

template<class T>
void basic_binary_tree<T>::inorder(int root)
{
    if(null != root)
    {
        inorder(tr[root].left);
        std::cout << tr[root].element << ' ';
        inorder(tr[root].right);
    }

}

template<class T>
void basic_binary_tree<T>::postorder(int root)
{
    if(null != root)
    {
        postorder(tr[root].left);
        postorder(tr[root].right);
        std::cout << tr[root].element << ' ';
    }
}

template<class T>
void basic_binary_tree<T>::queorder(int root)
{
    queue<int> que;
    que.push(root);
    node<T> tmp;
    while(!que.empty())
    {
        std::cout << tr[que.front()] << ' ';
        tmp = tr[que.front()];
        if(null != tmp.left)
            que.push(tmp.left);
        if(null != tmp.right)
            que.push(tmp.right);
    }
}

}

#endif