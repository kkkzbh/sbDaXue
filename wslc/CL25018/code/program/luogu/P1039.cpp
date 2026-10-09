

#include<iostream>
#include<algorithm>
#include<ranges>
#include<string_view>
#include<unordered_map>
#include<vector>
#include<functional>
#include<map>

#define fun auto
#define let auto
#define in :

fun solve() -> void
{
    using namespace std::views;
    using namespace std::string_literals;
    let scan = []<typename... T>(T&... vs) { (std::cin >> ... >> vs); };
    let sscan = []<typename... T>(T&... str) { (std::getline(std::cin,str),...); };
    int n,m,p;
    scan(m,n,p);

    let constexpr week = std::array {
            "",
            "Monday",
            "Tuesday",
            "Wednesday",
            "Thursday",
            "Friday",
            "Saturday",
            "Sunday",
    };

    #define set(A) { week[A],A }
    let const weekm = std::map<std::string_view,int> {
            set(1),
            set(2),
            set(3),
            set(4),
            set(5),
            set(6),
            set(7),
    };

    let name = std::vector(m,""s);
    std::ranges::for_each(name,scan);
    let map = std::unordered_map<std::string,int>{};
    std::ranges::for_each(iota(0,m),[&](int i){ map[name[i]] = i; });
    using node = std::tuple<int,bool,bool,int>;
    let info = std::vector<node>{};
    std::cin.ignore();
    for(let i in iota(0,p)) {
        let s = ""s;
        sscan(s);
        while(s.back() == '\r' or s.back() == '\n') {
            s.pop_back();
        }
        if(s.back() != '.') {
            continue;
        }
        let it = 0ull;
        let find = s.find(':',it);
        let end = std::string::npos;
        let ns = s.substr(it,find - it);
        let id = map[ns];
        find += 2;
        let say = s.substr(find);
        if(say == "I am guilty.") {
            info.emplace_back(id,false,true,id);
        } else if(say == "I am not guilty.") {
            info.emplace_back(id,false,false,id);
        } else if(say.starts_with("Today is ")) {
            let monicker = say.substr(9);
            monicker.pop_back();
            info.emplace_back(id,true,bool{},weekm.at(std::string_view{ monicker }));
        } else if(say.ends_with(" is guilty.")) {
            find = say.find(' ');
            let monicker = say.substr(0,find);
            info.emplace_back(id,false,true,map[monicker]);
        } else if(say.ends_with(" is not guilty")) {
            find = say.find(' ');
            let monicker = say.substr(0,find);
            info.emplace_back(id,false,false,map[monicker]);
        }
    }

    enum {
        no,
        yes,
        nosay,
    };

    let vis = std::vector(m,nosay);
    let ans = -1;

    for(let i in iota(0,m)) {
        for(let day in iota(0,7 + 1)) {
            let ret = [&] {
                for(let const& [si,isday,is,id] in info) {
                    if(isday) {
                        if(id == day) {
                            switch(vis[si])
                            {
                                case nosay:
                                    vis[si] = yes;
                                    break;
                                case no:
                                    return -1;
                                case yes:
                                    break;
                            }
                        } else {
                            switch(vis[si])
                            {
                                case nosay:
                                    vis[si] = no;
                                    break;
                                case no:
                                    break;
                                case yes:
                                    return -1;
                            }
                        }
                    } else {
                        if(id == i) {
                            switch(vis[si])
                            {
                                case nosay:
                                    if(is) {
                                        vis[si] = yes;
                                    } else {
                                        vis[si] = no;
                                    }
                                    break;
                                case yes:
                                    if(not is) {
                                        return -1;
                                    }
                                    break;
                                case no:
                                    if(is) {
                                        return -1;
                                    }
                                    break;
                            }
                        } else {
                            switch(vis[si])
                            {
                                case nosay:
                                    if(is) {
                                        vis[si] = no;
                                    } else {
                                        vis[si] = yes;
                                    }
                                    break;
                                case yes:
                                    if(is) {
                                        return -1;
                                    }
                                    break;
                                case no:
                                    if(not is) {
                                        return -1;
                                    }
                                    break;
                            }
                        }
                    }
                }

                let cnt = std::ranges::count(vis,no);
                if(cnt == n or cnt + std::ranges::count(vis,nosay) >= n) {
                    return i;
                }
                return -1;

            }();
            if(ret != -1) {
                if(ans == -1) {
                    ans = ret;
                } else if(ans != ret) {
                    std::cout << "Cannot Determine";
                    return;
                }
            }
            std::ranges::fill(vis,nosay);
        }
    }
    if(ans == -1) {
        std::cout << "Impossible";
        return;
    }

    std::cout << name[ans];

};

fun main() -> int
{
    std::ios::sync_with_stdio(false),std::cin.tie(nullptr);

    std::invoke(solve);

    return 0;
};