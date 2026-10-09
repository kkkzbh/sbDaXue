module;

#include <iostream>

export module ktuple;

export
{
    #include <tuple>
}

export template<typename... Ts>
struct ktuple : std::tuple<Ts...>
{
    using super = std::tuple<Ts...>;
    using super::tuple;
    using super::operator=;
    using super::swap;

    constexpr operator super&() &
    { return *this; }

    constexpr operator super const&() const &
    { return *this; }

    template<std::integral T,T v>
    auto constexpr operator[](this auto&& self,std::integral_constant<T,v>)
    { return std::get<v>(self); }

    auto friend operator>>(std::istream& is,ktuple& kp) -> std::istream&
    {
        std::apply([&]<typename... Args>(Args&&... args) {
            (is >> ... >> args);
        },static_cast<super&>(kp));
        return is;
    }

    auto friend operator<<(std::ostream& os,ktuple const& kp) -> std::ostream&
    {
        std::apply([&]<typename... Args>(Args&&... args) {
            auto flag = false;
            ([&]<typename T>(T&& arg) {
                if(not flag) {
                    flag = true;
                } else {
                    os << " ";
                }
                os << std::forward<T>(arg);
            }(args),...);
        },static_cast<super const&>(kp));
        return os;
    }

};

export template<typename... Ts>
ktuple(Ts...) -> ktuple<Ts...>;

export template<typename... Ts>
auto make_ktuple(Ts&&... args)
{ return ktuple<typename std::__decay_and_strip<Ts>::__type...>{ std::forward<Ts>(args)... }; }

export namespace std
{
    template<typename... _Elements>
    bool constexpr inline __is_tuple_like_v<ktuple<_Elements...>> = true;

    template<typename... Ts>
    struct tuple_size<ktuple<Ts...>> : tuple_size<tuple<Ts...>> {}; // NOLINT

    template<size_t i,typename... Ts>
    struct tuple_element<i,ktuple<Ts...>> : tuple_element<i,tuple<Ts...>> {}; // NOLINT

    template<typename... Ts,typename CharT>
    struct formatter<ktuple<Ts...>,CharT> : formatter<tuple<Ts...>,CharT> // NOLINT
    {};
}

template<typename T>
struct tuple_traits_element {};

template<typename... Ts>
struct tuple_traits_element<std::tuple<Ts...>>
{
    template<template<typename...> typename Meta>
    using apply = Meta<Ts...>;
};

export struct kpack
{
    template<typename... Args>
    auto static constexpr operator[](Args&&... args)
    { return make_ktuple(std::forward<Args>(args)...); }

    template<typename... Args>
    auto static constexpr operator()(Args&... args)
    { return make_ktuple(std::ref(args)...); }

} constexpr pack;


export namespace ktuple_literals
{
    template<char... cs>
    auto consteval operator""i()
    {
        auto constexpr v = std::array{ cs...,'\0' };
        auto constexpr idx = [&] consteval {
            std::size_t ret;
            std::from_chars(std::begin(v),std::end(v),ret);
            return ret;
        }();
        return std::integral_constant<std::size_t,idx>{};
    }
}

using namespace ktuple_literals;

export template<typename... wi>
struct kweight
{
    using kweight_tag = void;

    template<std::size_t i>
    using index = std::integral_constant<std::size_t,i>;

    using base_t = ktuple<wi...>;

    explicit constexpr kweight(wi...) {}

    template<std::size_t... idx>
    explicit constexpr kweight(std::index_sequence<idx...>) {}

    auto constexpr static size = sizeof...(wi);

    template<std::integral T,T v>
    auto constexpr operator[](this auto&& self,std::integral_constant<T,v> i)
    { return self.idxs[i]; }

    auto constexpr operator()(this auto&& self)
    { return self.idxs; }

    base_t idxs;
};

export template<std::size_t... idx>
kweight(std::index_sequence<idx...>) -> kweight<std::integral_constant<std::size_t,idx>...>;

export template<typename Weight,typename... Cmps>
requires requires { typename Weight::kweight_tag; }
struct kcmp
{

    using base_t = ktuple<Cmps...>;

    explicit constexpr kcmp(Cmps... cmps) : cmps(std::move(cmps)...),weight(std::make_index_sequence<sizeof...(Cmps)>{}) {}

    explicit constexpr kcmp(Weight weight,Cmps... cmps) requires requires { typename Weight::kweight_tag; } : cmps(std::move(cmps)...),weight(weight) {}

    static_assert(Weight::size == sizeof...(Cmps), "kcmp: size of weight and cmps must be equal");

    template<std::size_t i,typename Tp,typename Cmp,typename W>
    auto static constexpr compare(Tp const& lhs,Tp const& rhs,Cmp const& cmp,W const weight) -> auto
    {
        if constexpr(i == std::tuple_size_v<Cmp>) {
            return 0;
        } else if constexpr(std::same_as<std::tuple_element_t<i,Cmp>,std::remove_cvref_t<decltype(std::ignore)>>) {
            return compare<i + 1>(lhs,rhs,cmp,weight);
        } else {
            using cmp_t = std::tuple_element_t<i,Cmp>;
            if constexpr(std::__tuple_like<cmp_t>) {
                if constexpr(requires { requires std::__tuple_like<std::tuple_element_t<i,W>>; }) {
                    auto constexpr tp = std::get<i>(weight);
                    auto constexpr idx = tp[0i];
                    static_assert(std::same_as<std::remove_cvref_t<decltype(idx)>,std::integral_constant<std::size_t,idx()>>);
                    auto constexpr wt = tp[1i];
                    static_assert(std::__tuple_like<decltype(wt)>);
                    using value_t = std::tuple_element_t<idx(),Tp>;
                    static_assert(std::__tuple_like<value_t>);
                    static_assert(std::tuple_size_v<cmp_t> <= std::tuple_size_v<value_t>);
                    static_assert(std::tuple_size_v<decltype(wt)> == std::tuple_size_v<cmp_t>);
                    auto ret = compare<0>(lhs[idx],rhs[idx],std::get<i>(cmp),wt);
                    if(ret != 0) {
                        return ret;
                    }
                    return compare<i + 1>(lhs,rhs,cmp,weight);
                } else {
                    auto constexpr idx = std::get<i>(weight);
                    using value_t = std::tuple_element_t<idx(),Tp>;
                    static_assert(std::__tuple_like<value_t>);
                    static_assert(std::tuple_size_v<cmp_t> <= std::tuple_size_v<value_t>);
                    auto ret = compare<0>(lhs[idx],rhs[idx],std::get<i>(cmp),kweight{ std::make_index_sequence<std::tuple_size_v<cmp_t>>{} }());
                    if(ret != 0) {
                        return ret;
                    }
                    return compare<i + 1>(lhs,rhs,cmp,weight);
                }
            } else {
                auto constexpr idx = std::get<i>(weight);
                if(lhs[idx] != rhs[idx]) {
                    return std::get<i>(cmp)(lhs[idx],rhs[idx]) ? 1 : -1;
                }
                return compare<i + 1>(lhs,rhs,cmp,weight);
            }
        }
    }

    template<std::__tuple_like Tp>
    auto constexpr operator()(Tp const& lhs,Tp const& rhs) const -> bool
    {
        static_assert(std::tuple_size_v<Tp> >= std::tuple_size_v<base_t>);
        return compare<0>(lhs,rhs,cmps,weight()) == 1;
    }

    base_t cmps;
    Weight weight;
};

export template<typename... Cmps>
kcmp(Cmps... cmps) -> kcmp<decltype(kweight{ std::make_index_sequence<sizeof...(Cmps)>{} }),Cmps...>;