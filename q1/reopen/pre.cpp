

#include <iostream>

namespace {
    auto re = []() {
        std::freopen("../reopen/in","r",stdin);
        std::freopen("../reopen/out","w",stdout);
        return true;
    }();
}