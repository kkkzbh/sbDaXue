#pragma once

#include<iostream>
#include<chrono>

#define NOW std::chrono::high_resolution_clock::now()
#define PTIME \
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(___ED-___ST); \
    std::cout << "总计用时 : " << duration.count() << " ms\n"

#define START auto ___ST = std::chrono::high_resolution_clock::now()
#define END auto ___ED = std::chrono::high_resolution_clock::now()


inline auto now()
{
    return std::chrono::high_resolution_clock::now();
}

inline void ptime(decltype(std::chrono::high_resolution_clock::now()) start,decltype(std::chrono::high_resolution_clock::now()) end)
{
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout << duration.count() << " ms\n";
}