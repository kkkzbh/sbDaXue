

#include<iostream>

const int N = 10000;
const int null = -1;

struct heap // 该堆 下标从0开始 注意！
{

    struct node // 注意如果使用这个类内结构体 需要用 heap::node 的方式
    {
        friend bool operator<(const node& n1,const node& n2)
        {
            // friend 说明声明了一个全局的函数 只不过写在了类内  所以参数不涉及this指针传递 这个函数内部是不涉及this指针的
            // 其次这个函数是类 node 的友元(friend) 拥有访问类node private的权利
            // 这个函数的作用是 给node 提供 < 运算符 实现看下方定义
            return n1.weigh < n2.weigh;
        }

        friend bool operator>(const node& n1,const node& n2)
        {
            return n2 < n1;
        }


        int weigh; // 权重
        char val;   // 值
        int index; // 可以是某个索引 比如在利用堆建立哈夫曼树时
                // 另开一个数组存哈夫曼树  堆作为辅助
                // 每次从堆中弹出两个元素 根据index的值 判断这两个元素 在数组里的哪儿个下标
                // 然后往数组和堆里插入新结点时 利用index 更方标的调节index处的父指针(int) 和 新插入结点的 左右指针(int) 等
    };

public:

    //关于构造函数有必要细说一下  C++的构造函数 名字必须与类名一样 且无返回值

    heap() = default;   // 这个表明声明一个默认的构造函数 这样就可以默认构造类heap  比如 heap x; 默认构造了x
                        // 需要说明的是 如果一个类没有定义任何构造函数 默认构造函数被隐式定义


//    heap(int sz)        // heap x{ 100 }   创建一个内部数组大小为100的 堆
//    {
//        pa = new node[sz];  // 等价 this->pa = new node[sz]
//        n = sz; // 等价 this->n = sz;
//    }

    /* ************************************************* /*

    如果你选择上一个的写法  我们在struct里 是 给了 pa一个默认值的  下面有个 node* pa = new node[N]
    上一个写法 是在函数内部 对成员赋值  他会经历 先赋值 new node[N[ 在赋值 new node[sz]
    这样不仅内存泄露 还多了一次赋值 非常低效， 当然java只能这样了 除非你 没有在一开始struct内 给成员指定一个初始值
    而下方写法 会无视原先初始值 直接用所给参数构造成员  且下方才是真正的 C++ 构造函数写法 对于成员变量 一律写到 : 后面 用()内参数初始化



    /* ************************************************ */
    explicit heap(int sz) : pa(new node[sz]),n(sz)
    {

    }

                        // 该构造函数 接受一个数组和n 实现O(n) 建堆
                        // 怎么用呢 C++里方法其实多的很 这里简单介绍几种常用的
                        // 1. 传统构造函数调用方法  heap x(arr,n);   定义一个x 以这个构造函数构造
                        // 2. 常用的统一花括号构造语法  heap x{ arr,n };  同 1
                        // 3. 拷贝语义的花括号写法  heap x = { arr,n } 语义为拷贝 但一般可认为 同 2
                        // 4. 拷贝语义显示指定类型的写法  heap x = heap{ arr,n } 同理 一般可认为同 3
    heap(const node arr[],int n)
    {
        for(int i = 0; i < n; ++i)
        {
            a[i] = arr[i];
        }
        for(int it = up(n - 1); it != -1; --it)
        {
            auto val = a[it];   // 思考这里为什么需要拷一份
            down(it,val);
        }
    }


    void push(const node& v)
    {
        int it = n++;
        for(; it and a[up(it)] > v; it = up(it)) // 注意这里直接比较了结构体  然后 and 等效 && 我喜欢 and
        {
            a[it] = a[up(it)];
        }
        a[it] = v;
    }

    void pop()
    {
        down(0,a[n--]);
    }

    node& top()
    {
        return a[0];
    }

    // [[]] 双方括号 是C++11引入的一个叫做属性的东西 你可以不管 属性一般是与编译器交流
        // [[nodiscard]]告诉编译器 这个函数的返回值不应该被抛弃 那么 如果有人调用了 x.size()函数 而没有用他做赋值等用法
        //                                              只是空调了一下x.size() 编译器就会给调用者出一个警告
    [[nodiscard]]
    int size() const noexcept   // 从标准而言 一切与size有关的类型都是 C : size_t C++ : std::size_t 但此次我就不用了
    {
        // const 只能用于修饰 这种类的成员函数 表示这个函数 不能修改成员变量的值
        // 类似于const修饰变量 本质是const修饰了this指针
        // noexcept 表示这个函数不会抛出异常 是异常安全的函数  理论上你100%确定不抛异常的 都可以补充noexcept修饰 帮助编译器优化
        return n;
    }

    [[nodiscard]]
    bool empty() const noexcept
    {
        return !n;
    }

private:

    static int left(int i)
    {
        // static 是什么意思？  表示这个函数是与类heap 关系不大的函数, 只不过恰好写在了类内
        // 对于 static函数 是不涉及 this指针的隐式传参的
        // 也就是说 它可以当成全局函数调用 当然我这里用private修饰后 外界也没法调用了
        // 如果没有private 可以使用 heap::left 调用这个函数 亦或者是 某个heap变量h  用h.left调用
        // 但需要指出的是 static修饰的类内函数 不推荐用h.left形式调用 因为本就不涉及this指针的传递,用 h.left 这个left压根与h无关
        return (i << 1) + 1;
    }

    static int right(int i)
    {
        return (i << 1) + 2;
    }

    static int up(int i)
    {
        return (i - 1) >> 1;
    }

    void down(int it,const node& v)  // 这个函数是 向下调整堆的函数
    {
        int rt = left(it);
        while(rt < n)
        {
            if(rt != n - 1 and a[rt + 1] < a[rt])
            {
                ++rt;
            }
            if(a[it] > a[rt])
            {
                break;
            }
            else    // 这里不用swap了 自己想想为什么
            {
                a[it] = a[rt];
                it = rt;
                rt = left(it);
            }
        }
        a[it] = v;
    }

    static void swap(node& v1,node& v2) // 基于引用实现的 结构体 swap 要求 结构体有 = 号 不用const修饰 因为要修改
    {
        node v3 = v1;   // 对于值传递,值赋值而言 有时候const 是可有可无的 自己想想为什么
        v1 = v2;    // 结构体 是自带=号的(要求是每个成员都能=)  具体实现就是 逐个成员 逐个=
        v2 = v1;
    }

    node a[N] = {};

    node* pa = new node[N];
        // 当然 C++ 里可以进一步改写为为  node a[N]{}  省略 = 号,我更推荐省略 =
        // 就像 node a[N]{}一样 C++也支持普通元素的0初始化  如 int a{},  当然C语言也支持(应该) int a = {};
    int n = 0;  // int n{};

};


int main()
{
    heap::node arr[10];
    int n = 2;
    heap x(arr,n);
    heap y{ arr,n };
    heap z = { arr,n };

    x.size();       // 注意波浪线 编译器的警告

    heap h;
    h.push( { 1,2,3 } );
        // 因为node是结构体 可以直接使用{}构造 这里{}会根据函数接受参数 隐式推导为node{}
    h.push( { 1,2,3 } );
    h.push( heap::node{ 1,2,3 } );  // 显式的写自己要构造node
    h.push( { 3,2,3 } );
    h.push( { 5,2,3 } );

    while(!h.empty())
    {
        auto val{ h.top() };  // 现代C++ 推荐使用不带=的{} 统一初始化 同时注意我用auto的场景 不拒绝auto 也不滥用auto
        h.pop();
        std::cout << val.weigh << '\n'; // 打印弹出结点的权重 应该是符合最小堆的
    }

    int* a = new int;   // 开一个堆区的int变量 用int* a 指向
    int* aa = new int{ 3 }; // 这也是我为什么推荐用不带=号的初始化  这在C++里 好处更多  = 最多只是兼容C写法
    int* b = new int[100];  // 开数组 用int* b 指向
    int* c = new int[100]{ 1,3,5,7,9 }; // new 变量支持构造时的初始化 比malloc高级

                        //比如 这个node 就可以这么构造 外层{}是数组 内层每个{}是一个结构体
    auto* d = new heap::node[100]{ {1,2,3}, { 4,5,6 }};
    // 因为new后面写过类型了 所以前面更建议直接auto

    delete a;   //析构变量
    delete[] b; // 如果你反正从来也不free  那么不delete 也行
    delete[] c;
    delete[] d;




    std::cout << a << b << c << d << aa;
    return 0;
}