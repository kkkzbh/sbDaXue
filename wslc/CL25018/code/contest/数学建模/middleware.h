

#ifndef LUOGU_MIDDLEWARE_H
#define LUOGU_MIDDLEWARE_H

#include"std.h"

struct middleware
{
    double p;
    double fit_s;
    double check_s;
    double dis_s;
    std::vector<int> need;
};

extern std::vector<std::vector<middleware>> middlewares;



#endif
