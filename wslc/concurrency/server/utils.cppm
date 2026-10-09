module;

#include <arpa/inet.h>
#include <string_view>
#include <chrono>
#include <utility>
#include <filesystem>

export module utils;

import net;

using namespace std::string_view_literals;
using namespace std::filesystem;

export using i64 = long long;
export using u16 = unsigned short;

export auto constexpr BUF_SIZE = 2048;

auto constexpr server_ip = ton(INADDR_ANY);
auto constexpr server_port = ton(u16{ 21455 });

auto constexpr server_addr_in = sockaddr_in {
    AF_INET,server_port,server_ip
};

export auto server_addr = reinterpret_cast<sockaddr const*>(&server_addr_in);
export auto constexpr server_addrsz = sizeof server_addr_in;

export auto constexpr time_format = "[{:%Y-%m-%d %H:%M:%S}]"sv;

export auto get_time()
{
    using namespace std::chrono;
    return std::format(time_format,floor<seconds>(system_clock::now()));
}

export auto base_root = path{ BASE_ROOT };