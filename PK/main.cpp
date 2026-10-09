

#include <bits/stdc++.h>

#define fun auto

// Random engine
std::random_device rdv;
std::mt19937 mt{ rdv() };

// Distributions, renamed to avoid collision with macros
static std::uniform_int_distribution<> dist1{1, 100};  // was r1 range [1..100]
static std::uniform_int_distribution<> dist2{1, 200};  // was r2 range [0..200]
static std::uniform_int_distribution<> dist3{0, 1000000007};    // was r3 range [1..3]
static std::uniform_int_distribution<> dist4{1, 1000000000};    // was r4 range [1..3]

// Macros to expand to random draws
#define r1 dist1(mt)
#define r2 dist2(mt)
#define r3 dist3(mt)
#define r4 dist4(mt)

// Provide stubs for main1(), main2() if needed
extern fun main1() -> int;
extern fun main2() -> int;

// Bounds from your code
#define flo1 1
#define cei1 100
#define flo2 0
#define cei2 200
#define flo3 1
#define cei3 3
#define flo4 1
#define cei4 3

fun make()
{
    // We will generate one test file: "../i"
    std::ofstream os{"../i"};
    if (!os.is_open()) {
        std::cerr << "Cannot open output file ../i\n";
        return;
    }

    os << r1 << ' ' << r2 << ' ' << r3 << ' ' << r4 << '\n';
}

fun main() -> int
{

    auto constexpr sec = 0;


    if constexpr(sec == 0) {
        auto i = 0;
        auto constexpr step = 10000;
        for(; i != step ; ++i)
        {
            make();
            auto i1 = freopen("../i", "r", stdin);
            auto o1 = freopen("../o1", "w", stdout);
            main1();
            std::cout << std::flush;
            fclose(o1);
            fclose(i1);
            auto i2 = freopen("../i", "r", stdin);
            auto o2 = freopen("../o2", "w", stdout);
            main2();
            std::cout << std::flush;
            fclose(o2);
            fclose(i2);

            std::ifstream is1{ "../o1" };
            std::ifstream is2{ "../o2" };
            char x1, x2;

            while(is1 >> x1 and is2 >> x2) {
                if(x1 != x2) {
                    break;
                }
            }
            is2 >> x2;
            if(!is1.eof() or !is2.eof()) {
                break;
            }
        }
        if(i == step) {
            freopen("../i","w",stdout);
            std::cout << "完全相等！" << std::endl;
        }
    }
    if constexpr(sec == 1) {
        make();
    }
    if constexpr(sec == 2) {
        freopen("../i","r",stdin);
        freopen("../o1","w",stdout);
        main1();
        std::cout << std::flush;
    }
    if constexpr(sec == 3) {
        freopen("../i","r",stdin);
        freopen("../o2","w",stdout);
        main2();
        std::cout << std::flush;
    }

    return 0;
}
