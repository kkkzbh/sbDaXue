export module print;

export import <iostream>;
import <format>;
import <string_view>;

export
{

    template<typename... Args>
    void print(const std::string_view fmt_str, Args&&... args)
    {
        fputs(std::vformat(fmt_str, std::make_format_args(args...)).data(), stdout);
    }


    void print(char c)
    {
        fputc(c, stdout);
    }

    void print(const std::string_view s)
    {
        fputs(s.data(), stdout);
    }


    template<typename Value>
    void print(Value&& i)
    {
        print("{}", i);
    }

    template<typename... Args>
    void println(Args&&... args)
    {
        print(args...);
        fputc('\n', stdout);
    }


    void println()
    {
        fputc('\n', stdout);
    }


    struct M_System
    {
        struct M_Out
        {
            template<typename... Args>
            void println(Args&&... args) const
            {
                ::println(args...);
            }


            template<typename... Args>
            void print(Args&&... args) const
            {
                ::print(args...);
            }

            void println()
            {
                fputc('\n', stdout);
            }
        }out;
    }System;

}