

#ifndef LUOGU_COMPONENT_H
#define LUOGU_COMPONENT_H

#include"std.h"
#include"rand.h"

constexpr int component_n = 10000;

struct component
{
    double p;
    double buy_s;
    double check_s;
};


extern std::vector<component> components;

fun make_component(int i) -> bool;

fun make_components(int i) -> std::vector<bool>;

#endif
