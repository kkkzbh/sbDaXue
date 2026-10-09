module;

#include <iostream>
#include <print>
#include <fstream>

export module log;

export namespace log
{
    template<typename... Args>
    auto write(std::format_string<Args...> fmt,Args&&... args) -> void
    {
        std::println(fmt, std::forward<Args>(args)...);
        std::fflush(stdout);
    }

    template<typename... Args>
    auto error(std::format_string<Args...> fmt,Args&&... args) -> void
    {
        std::println(stderr,fmt, std::forward<Args>(args)...);
    }
}