



#ifndef MENU_H
#define MENU_H

#define MENU_INTERFACE

#include"print.h"
#include<thread>
#include<functional>
#include<chrono>
#include"utility.h"
#include<conio.h>
#include<condition_variable>
#include<mutex>
#include"time"
#include<windows.h>

/* ********************************************************* /*
 *
 *  menu.h 结合menu.cpp 该文件的主要作用是提供一个界面管理
 *  在这个界面中 拥有调用整个程序实现压缩的接口的能力
 *
 /* ********************************************************* */

#define pblank print("{}      {}\n",blank,blank)

extern std::function<void()> fpmenu;        // 这两个变量都是一个函数 打印界面使用
extern std::function<void(std::ostringstream&)> fpmenu_buf;

namespace progress  // progress命名空间内部的全部东西 只有一个作用  程序正在压缩时  打印一个进度条 当然只有在比较大的文件被压缩时 才能清晰的看到该进度条
{

    extern std::string compress_bar;
    extern std::string decpress_bar;
    constexpr inline char flow_point[][4]{ "   ",".  ",".. ","..." };
    constexpr inline uint64 st_index{ 16ull + 5ull - 1ull };
    constexpr inline uint64 point_index{ 11ull + 5ull + 1ull };

    constexpr inline double sleep_time{ 0.3 };

    extern std::mutex mux;   // 多线程工具  线程 互斥锁 条件变量  目的是为了实现并发程序设计 使进度条为动态的
    extern std::condition_variable cdv;
    extern std::thread bar;

    extern bool run;
    extern bool end;

    extern std::function<void ()> pcompress;
    extern std::function<void ()> pdecpress;

}

struct menu
{

    constexpr static char star[]{ "* * * * * * * * * * * * * * * * * * * * * * * " };   // 打印界面用
    constexpr static char blank[]{ "          " };

    menu();     // 此为menu的构造函数  顺便说 有关函数的定义 有很多放到了menu.cpp 中  类内主要放置声明
    ~menu();

    auto static pmenu() -> void;    // 这个函数是不使用的 但我是保留了下来
    auto static pmenu_buf(std::ostringstream& os) -> void;  // 这个函数主要是 提供一个主界面的一部分打印的 接口

    auto oper() -> void;        // 实现 在界面的操作
    auto static pcompress   // 该函数是 打印oper有关压缩的 界面
    (const std::function<bool (const std::string_view file,const std::string_view output)>& fun)
    -> void;

private:

    std::mutex static mx;
    std::condition_variable static cv;
    bool static isrun;
    bool static end_pm;

    std::function<void()> pm_run{ []() -> void          // 从下面的内容也可以看到 这个函数就是打印主界面的
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x00);
        std::string flows{ "        Welcome!     ^o^             " };
        std::string buffer;
        HANDLE OUTPUT_HANDLE = GetStdHandle(STD_OUTPUT_HANDLE);
        while(!end_pm)
        {
            std::unique_lock lock{ mx };

            std::ostringstream os;
            referesh();
            os << std::format("{}{}|{}  \n",blank,flows,M_time.tim->hms);
            fpmenu_buf(os);
            char c{flows.front()};
            flows.erase(flows.begin());
            flows.push_back(c);
            //system("cls");
            SetConsoleCursorPosition(OUTPUT_HANDLE,{ 0,0 });
            print(os.str());
            std::this_thread::sleep_for(std::chrono::duration<double>{ 0.5 });

            //cv.wait(lock,[]{ return isrun; });
            if(!isrun)
            {
                lock.unlock();
                std::this_thread::sleep_for(std::chrono::duration<double>{ 0.1 });
            }
        }
    }};

    std::thread pm;

};

#endif
