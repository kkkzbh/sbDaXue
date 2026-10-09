

#include <bits/stdc++.h>

#define fun auto

// Random engine
std::random_device rdv;
std::mt19937 mt{ rdv() };

// Distributions, renamed to avoid collision with macros
static std::uniform_int_distribution<> dist1{1, 100};  // was r1 range [1..100]
static std::uniform_int_distribution<> dist2{0, 200};  // was r2 range [0..200]
static std::uniform_int_distribution<> dist3{1, 3};    // was r3 range [1..3]
static std::uniform_int_distribution<> dist4{1, 3};    // was r4 range [1..3]

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

    // 1) Pick n in [2..100]
    int n = r1; // r1 is in [1..100]
    if (n < 2) n = 2;  // Ensure at least 2

    // 2) Pick M in [n-1,  min(n*(n-1), (n-1 + something up to 200))]
    int extra = r2; // random [0..200]
    int M = (n - 1) + extra;
    int maxPossible = n * (n - 1); // ignoring parallel edges
    if (M > maxPossible) {
        M = maxPossible;  // clamp
    }

    // We want to ensure the undirected version is connected.
    // So we start by building a spanning tree ignoring direction,
    // and then randomly assigning directions.
    // We'll store edges in a set to avoid duplicates.
    // Edges are 1-based: from 1..n
    auto edgeHash = [ ](const std::pair<int,int> &p){
        // A simple combination hash for (u,v)
        // Not strictly necessary, but good practice for an unordered set
        // or we could use std::set<std::pair<int,int>> with operator<.
        // We'll just use a string approach for simplicity:
        auto h1 = std::hash<std::string>{}(
            std::to_string(p.first) + "_" + std::to_string(p.second)
        );
        return h1;
    };
    auto edgeEq = [ ](const std::pair<int,int> &a, const std::pair<int,int> &b){
        return (a.first == b.first && a.second == b.second);
    };
    std::unordered_set<std::pair<int,int>, decltype(edgeHash), decltype(edgeEq)>
        edges(0, edgeHash, edgeEq);

    // 3) Build a random spanning tree (n-1 edges):
    //    For each i from 2..n, pick random parent p in [1..i-1],
    //    then randomly direct p->i or i->p.
    for (int i = 2; i <= n; ++i) {
        int p = std::uniform_int_distribution<int>(1, i - 1)(mt);
        // random direction
        bool dir = (std::uniform_int_distribution<int>(0, 1)(mt) == 0);
        if (dir) {
            edges.insert({p, i});
        } else {
            edges.insert({i, p});
        }
    }

    // If n=2, we already have 1 edge. If M>1, we need to add more below.

    // 4) Add random edges until we reach M or run out of possibilities
    //    We never add an edge (u->v) that already exists.
    std::uniform_int_distribution<int> distN(1, n);
    while ((int)edges.size() < M) {
        int u = distN(mt), v = distN(mt);
        if (u == v) {
            continue; // skip self-loop
        }
        // Insert only if not already present
        auto pr = std::make_pair(u, v);
        if (edges.find(pr) == edges.end()) {
            edges.insert(pr);
        }
        // If we have exhausted all possible distinct edges, break
        if ((int)edges.size() == maxPossible) {
            break;
        }
    }

    // Now we have a random connected directed graph in terms of ignoring direction.
    // 5) Write out the data
    // n, M
    // then M lines of "u v"
    int finalM = (int)edges.size();
    os << n << " " << finalM << "\n";
    for (auto & e : edges) {
        os << e.first << " " << e.second << "\n";
    }

    os.close();
    std::cout << "Test data generated. (n=" << n
              << ", M=" << finalM << ") -> ../i\n";
}

fun main() -> int
{

    auto constexpr sec = 1;


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
