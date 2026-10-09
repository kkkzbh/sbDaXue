



#ifndef STRING_BUFFER_H
#define STRING_BUFFER_H

/* ***************************** /*

    基于循环队列实现的字符串缓冲区
    实现并非本次主要 故不再给出过多注释

/* ***************************** */

#include"utility.h"

struct string_buffer
{

private:

    struct M_iterator
    {

        M_iterator() = default;
        M_iterator(char* p,char str[]) : ptr(p),s(str){}

        auto friend operator<=>(const M_iterator& ptr1,const M_iterator& ptr2) noexcept -> std::strong_ordering
        {
            return ptr1.ptr <=> ptr2.ptr;
        }

        auto friend operator==(const M_iterator& ptr1,const M_iterator& ptr2) noexcept -> bool
        {
            return ptr1.ptr == ptr2.ptr;
        }

        auto operator->() const noexcept -> char*
        {
            return ptr;
        }

        auto operator*() const noexcept -> char
        {
            return *ptr;
        }

        auto operator++() -> M_iterator&
        {
            if(++ptr == s + buffer_size)
            {
                ptr = s;
            }
            return *this;
        }

        auto operator++(int) -> M_iterator
        {
            M_iterator ret{ *this };
            ++*this;
            return ret;
        }

    private:

        char* s;
        char* ptr{ nullptr };

    };

public:

    using iterator = M_iterator;

    constexpr static uint64 buffer_size{ 128 };

    auto operator+=(const char* str) noexcept -> string_buffer&;

    auto operator+=(const char c) noexcept -> string_buffer&;

    operator bool () const;

    auto to_int() -> int;

    auto push(const char* str) noexcept -> void;

    auto push(const char c) noexcept -> void;

    auto ignore() -> void;  // the define is base in the realize of compress
    auto pop() -> void;
    auto move(uint64 dis) -> void;

    auto get() -> char;

    auto make() -> std::string;

    [[nodiscard]]
    auto size() const -> uint64;

    [[nodiscard]]
    auto empty() const noexcept -> bool;

    auto begin() -> iterator;

    auto end() -> iterator;

private:

    char s[buffer_size]; // if the buffer is full, the behavior is undefined.
    uint64 l{},r{};
    uint64 sz{};
};


#endif //STRING_BUFFER_H

