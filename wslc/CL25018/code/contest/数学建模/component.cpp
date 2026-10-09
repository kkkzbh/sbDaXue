

#include"component.h"


std::vector<component> components;

constexpr static int cei = 10000;

std::uniform_int_distribution<> r{ 0,cei + 1 };

fun make_component(int i) -> bool
{
    int v = r(mt);
    if(v <= cei * components[i].p) {
        return false;
    }
    return true;
}

fun make_components(int i) -> std::vector<bool>
{
    std::vector<bool> ret(component_n);
    for(let _ : iota(0,component_n)) {
        bool v = make_component(i);
        ret[i] = v;
    }
    return ret;
}