

#include <bits/stdc++.h>

class Solution {

public:
    int countPrimes(int n) {
        if(n <= 2) {

            return 0;
        }
        auto primes = std::vector(n,true);
        primes[0] = primes[1] = false;
        auto ans = 1;
        for(auto i = 3; i < n; i += 2) {
            if(not primes[i]) {
                continue;
            }
            ++ans;
            for(auto j = 1ull * i * i; j < n; j += i) {
                primes[j] = false;
            }
        }
        return ans;
    }

};
