
#include <print>
#include <cstring>
#include <memory>

struct YY
{
    int yy;
};

struct node
{
    int x;
    char y;
    long z;  // 64位
    YY k;
};

struct node2
{

    node2() = default;
    node2(int x,char y,long z,YY k) : x{ x },y{ y },z{ z },k{ k } {}

    int x;
    char y;
    long z;
    YY k;
};

node2 nd8;

auto main() -> int
{

    node nd1;
    node nd2;
    node nd3;
    node nd4;
    node nd5;
    node nd6;
    node2 nd7;
                                                                                                                                                    #define ad(x) (void*)std::addressof(x)
                                                                                                                                                        #define p(X) std::println(#X " {} -- {} -- {} -- {}",ad(X.x),ad(X.y),ad(X.z),ad(X.k.yy)); std::println("{}",*(__int128*)(std::addressof(X)))
                                                                                                                                                        p(nd1); p(nd2); p(nd3); p(nd4); p(nd5);  p(nd6); p(nd7); p(nd8);
    nd1 = {};
    std::memset(ad(nd2),0,sizeof nd2);
    nd3.x = 0, nd3.y = '\0', nd3.z = 0L, nd3.k.yy = 0;
    nd4 = (node) {};
    nd5 = (node) {
        .x = 0,
        .y = '\0',
        .z = 0L,
        .k = {
            .yy = 0
        },
    };
    nd6.x = 0, nd6.y = 0,nd6.z = 0,nd6.k.yy = 0;
    nd7 = {};
    nd8 = (node2) { 0,0,0,{ 0 } };

    std::println();

                                                                                                                                            p(nd1); p(nd2); p(nd3); p(nd4); p(nd5); p(nd6); p(nd7); p(nd8);


}