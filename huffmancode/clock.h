


#ifndef CLOCK_H
#define CLOCK_H

/* ****************** /*

    主要作用就是计算解压 压缩所用的时间
    不是本次主要 不做过多注释

/* ****************** */


#include<iostream>
#include<chrono>

#define NOW std::chrono::high_resolution_clock::now()
#define PTIME \
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(___ED-___ST); \
    std::cout << "Take : " << duration.count() << " ms\n"

#define START auto ___ST = std::chrono::high_resolution_clock::now()
#define END auto ___ED = std::chrono::high_resolution_clock::now()

auto now();

auto ptime(decltype(std::chrono::high_resolution_clock::now()) start,decltype(std::chrono::high_resolution_clock::now()) end) -> void;

#endif
