


#include<iostream>

template<typename T>
struct node
{
    T element = T();
    node* left = nullptr;
    node* right = nullptr;
    node() = default;
    explicit node(const T& ele) : element(ele){}
};

template<typename T>
class BST
{
    friend bool isequal(const node<T>* a,const node<T>* b);
private:
    node<T>* head = nullptr;
public:
    void insert(const T& ele)
    {
        if(!head) head = new node<T>(ele);
        node<T>* it = head;
        while(true)
        {
            if(ele > it->element)
            {
                if(it->right) it = it->right;
                else
                {
                    it->right = new node<T>(ele);
                    break;
                }
            }
            else if(ele < it->element)
            {
                if(it->left) it = it->left;
                else
                {
                    it->left = new node<T>(ele);
                    break;
                }
            }
            else break;
        }
    }
    const node<T>* get() const
    {
        return head;
    }
};

template<typename T>
bool isequal(const node<T>* a,const node<T>* b)
{
    if(a == nullptr && b == nullptr) return true;
    else if(a == nullptr || b == nullptr) return false;
    return isequal(a->left,b->left) && isequal(a->right,b->right);
}

constexpr char ans[][5]{"No","Yes"};

int main()
{
    int n;
    int v;
    int l;
    while(std::cin >> n)
    {
        if(!n) break;
        std::cin >> l;
        BST<int> a;
        for(int i = 1; i <= n;++i)
        {
            std::cin >> v;
            a.insert(v);
        }
        for(int i = 1; i <= l;++i)
        {
            BST<int> tmp;
            for(int j = 1; j <= n;++j)
            {
                std::cin >> v;
                tmp.insert(v);
            }
            std::cout << ans[isequal(a.get(),tmp.get())] << '\n';
        }
    }
    return 0;
}
