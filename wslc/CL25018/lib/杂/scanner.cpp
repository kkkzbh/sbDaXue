//
// Created by kkkzbh on 25-5-25.
//

struct scanner
{

    auto operator()(auto&& v) const -> void
    { std::cin >> v; }

    template<typename T>
    auto operator()(T&& tp) const -> void
    requires requires(T tp) { typename std::tuple_size<std::remove_cvref_t<T>>::type; }
{ std::apply(*this,tp); }

    template<typename R>
    auto operator()(R&& r) const -> void
    requires std::ranges::output_range<R,std::ranges::range_value_t<R>>
    { std::ranges::for_each(r,*this); }

    template<typename... Args>
    auto operator()(Args&&... args) const -> void
    requires (sizeof...(args) > 1)
    { ((*this)(args),...); }

};


auto constexpr scan = scanner{};