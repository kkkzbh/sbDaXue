

#include"menu.h"
#include"fun.h"
#include"clock.h"
#include<random>

#include"rle.h"
#include"lz77.h"
#include"deflate.h"

/* ********* /*
 *
 *  更多细节见 menu.h的注释说明
 *
 /* ******** */

std::function<void()> fpmenu;   // 以下变量.h中已说明 不在过多说明
std::function<void(std::ostringstream&)> fpmenu_buf;

bool menu::isrun;
bool menu::end_pm;
std::mutex menu::mx;
std::condition_variable menu::cv;

std::string flow_star{ "* * * * * * * * * * * * * * * * * * * ?_? * " }; // 44

namespace sentence      // sentence 命名空间 功能则是提供一些句子
{
    constexpr static char you_say_is_ok[]{ "你说的对,但是......................忘了。" };
    constexpr static char what_can_i_say[]{ "说实话，写的我有点相似             " };
    constexpr static char bu_hui_ba[]{ "不会吧,不会吧，不会真的有人盯着这个字体看吧 " };
    constexpr static char this_is_a_true[]{" 你说我怎么这么闲,写一堆这么没用的东西  " };
    constexpr static char OrzOrzOrz[]{ "对,说的就是你,请互评打个高分喵    " };
    constexpr static char caocaocao[]{ "真草了！ 高数tm的还没复习！ "} ;
    constexpr static char think_reverse_tian_kou1[]{ "认为作业逆天的扣1!! " };   // 我不敢加 别问为什么
    constexpr static char i_want_look_marry[]{ "想看马瑞亲 " };
    constexpr static char yuanshen_qi_ddddddong[]{ "原神，启动!!!!!!!!!!! " };
    constexpr static char hahahahahahahahahaha[]{ "哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈 " };
    constexpr static char ttttttttttttt[]{ "锟斤拷烫烫烫□烫烫烫□烫烫烫□烫烫烫□烫烫烫□烫烫烫□烫烫烫□" };
    constexpr static char de_bbbbbbbbbbbug[]{ "你可能看到有两个Input,我怎么知道怎么回事 " };
    constexpr static char tips0001[]{ "tips: 主界面按ESC也能关闭哦~~~" };
    constexpr static char i_do_not_say[]{ "是谁写大作业破防了我不说" };
    constexpr static char i_is_the_zuiqiang[]{ "有时打开这个程序,会显示65001然后直接关掉，亦或者是运行一会儿卡掉,反正我不会改(我是真不会" };
    constexpr static char add_extended[]{ "rle,lz77,deflate,写的很烂。" };
    constexpr static char ad_recruit[]{ "广告位待出租-----------------" };
    constexpr static char qiu_forgive[]{ "真的是一不小心就写多写杂了" };
    constexpr static char shen_jin[]{ "吴桐林是tm的神金病,还天天穿个拖鞋,能不能像个人" };
    constexpr static char rubbish[]{ "我知道我写的很烂,其他三个扩展的压缩 也没有进度条线程，实在是懒了呐！" };
    constexpr static char three[]{ "听说439三个王浩然 是真的吗？" };

    constexpr static char end[]{ "结束了，我却有点失落 " };
    constexpr static char discrete_math[]{ "打算明年离散数学继续选杨芳 " };
    constexpr static char data_struct[]{ "打算明年数据结构继续选lwj " };

    constexpr static const char* sentences[]{ you_say_is_ok,what_can_i_say,bu_hui_ba,
                                              this_is_a_true,OrzOrzOrz,caocaocao,
                                              i_want_look_marry,yuanshen_qi_ddddddong,
                                              hahahahahahahahahaha,ttttttttttttt,
                                              de_bbbbbbbbbbbug,tips0001,i_do_not_say,
                                              i_is_the_zuiqiang,add_extended,ad_recruit,
                                              qiu_forgive,shen_jin,rubbish,three,
                                                end,discrete_math,data_struct,
                                              };
    constexpr static std::size_t cnt{ sizeof(sentences) / sizeof(sentences[0]) };

    std::string buffer;
}

using sentence::sentences;


/* 以下三个变量 + 一个宏 目的是实现随机数的功能 rdv用以为引擎播种 mt19937作为随机数引擎 第三个变量则是分布器 利用引擎 产生对应分布的随机数     */
std::random_device rdv;
std::mt19937 mt19937{ rdv() };
std::uniform_int_distribution<> random_distribution{ 0,sentence::cnt };

#define MAKE_RANDOM random_distribution(mt19937);

menu::menu()    // menu的构造函数 以次程序调用oper 开启打印界面的线程 同时进入主要的操作区
{
    fpmenu = pmenu;
    fpmenu_buf = pmenu_buf;
    isrun = true;
    pm = std::thread{ pm_run };

    oper();
}

menu::~menu()   // 析构函数作用 便是停止 主界面线程
{
    end_pm = true;
    isrun = true;
    pm.join();
}

auto menu::pmenu() -> void          // the function is deleted
{
    print("{}\n",star);
    pblank;
    print("{}1.compress    {}\n",blank,blank);
    print("{}2.decpress    {}\n",blank,blank);
    print("{}0.exit        {}\n",blank,blank);
    pblank;
    print("{}\n",star);
    print("Input :>");
};

auto menu::pmenu_buf(std::ostringstream& os) -> void
{
    os << std::format("{}{}\n",blank,flow_star);
    os << std::format("{}*{}                       {}*\n",blank,blank,blank);
    os << std::format("{}*{}  >>file processing<<  {}*\n",blank,blank,blank);
    os << std::format("{}*{}   *****************   {}*\n",blank,blank,blank);
    os << std::format("{}*{}     1.compress        {}*\n",blank,blank,blank);
    os << std::format("{}*{}     2.decpress        {}*\n",blank,blank,blank);
    os << std::format("{}*{}     3.rle_compress    {}*\n",blank,blank,blank);
    os << std::format("{}*{}     4.rle_decpress    {}*\n",blank,blank,blank);
    os << std::format("{}*{}     5.lz77_compress   {}*\n",blank,blank,blank);
    os << std::format("{}*{}     6.lz77_decpress   {}*\n",blank,blank,blank);
    os << std::format("{}*{}     7.deflate_compress          *\n",blank,blank);
    os << std::format("{}*{}     8.deflate_decpress          *\n",blank,blank);
    os << std::format("{}*{}     0.exit            {}*\n",blank,blank,blank);
    os << std::format("{}*{}                       {}*\n",blank,blank,blank);
    os << std::format("{}{}\n",blank,star);

    constexpr static uint64 TIME_INTERVAL{ 20 };

    static uint64 cnt = TIME_INTERVAL;  // 该变量就是用以控制 语句变换的时间 具体实现操作 可见如下代码 不难理解
    static int val{};
    if(cnt == TIME_INTERVAL)
    {
        val = MAKE_RANDOM;
        cnt = 0;
        sentence::buffer = std::string{} + "                                                               " + sentences[val];
    }
    else
    {
        ++cnt;
        auto c{ sentence::buffer.substr(0,1) };
        sentence::buffer.erase(0,1);
        sentence::buffer.append(c);
    }

    char c{ flow_star.front() };
    flow_star.erase(0,1);
    flow_star.push_back(c);

    os << std::format("{}                           \n",sentence::buffer);
    os << "          >>>>Input :";
};

namespace progress
{
    std::string compress_bar{ "wait.compressing...   0% " };
    std::string decpress_bar{ "wait.decpressing...   0% " };

    std::mutex mux;
    std::condition_variable cdv;

    std::thread bar;

    bool run{ true };
    bool end;

    std::function<void ()> pcompress{ []() -> void
    {
        int val{ 3 };
        while(!end)
        {
            std::unique_lock lock(mux);
            //cdv.wait(lock,[]{ return run; });
            std::ostringstream os;
            os << compress_bar;
            system("cls");
            print(os.str());
            compress_bar.replace(point_index,3,flow_point[val = (val + 1) % 4]);
            std::this_thread::sleep_for(std::chrono::duration<double>{ sleep_time });
        }
    }};

    std::function<void ()> pdecpress{ []() -> void
    {
        int val{ 3 };
        while(!end)
        {
            std::unique_lock lock(mux);
            std::ostringstream os;
            os << decpress_bar;
            system("cls");
            print(os.str());
            decpress_bar.replace(point_index,3,flow_point[val = (val + 1) % 4]);
            std::this_thread::sleep_for(std::chrono::duration<double>{ sleep_time });
        }
    }};

}

/*    该函数就是不论是按1还是按2时 弹出的界面了  里面便连接上了 压缩的接口              */
auto menu::pcompress(const std::function<bool (const std::string_view file,const std::string_view output)>& fun) -> void
{

    /*  这里是准备工作 打印界面   */
    std::string f,opt;
    print("{}{}\n",blank,star);
    print("\n");
    print("{}*{}  >>file processing<<  {}*\n",blank,blank,blank);
    print("\n");
    print("{}>>>>please input the path of compression file:",blank);
    std::cin >> f;
    print("{}>>>>please input the output path:",blank);
    std::cin >> opt;
    system("cls");


    /*   这个fun是函数接受的参数, 我将这个函数控制的界面 与压缩和解压两个功能共用
     *   所以这个fun来源于 你按的到底是1 还是2  那么这个fun 就是实现压缩(解压)功能的函数 关于这两个函数 请看 fun.h 和 fun.cpp
     *                                                                      */


    START;  // 开始计时
    bool tag{ fun(f,opt) }; // 同时开始压缩
    END;

    system("cls");

    if(tag) // 如果压缩成功 fun 会返回tag
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x02);
        print("{}{}\n",blank,star);
        print("          *                                           *\n");
        print("{}*{}  >>file processing<<  {}*\n",blank,blank,blank);
        print("           The process is true,and the output in {}\n",opt);
        print("{}*{}                       {}*\n",blank,blank,blank);
        print("          *        press enter for continuing...      *\n");
        print("{}*{}                       {}*\n",blank,blank,blank);
        print("{}*{}                       {}*\n",blank,blank,blank);
        print("{}{}\n",blank,star);

        PTIME;

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x00);
        std::cin.ignore();
        std::cin.get();
    }


    progress::compress_bar.replace(progress::st_index,2," 0");  // 恢复加载字符串

}



/*    这个函数就是操作区的函数了  实现其实较为简单   只有一些常见的switch case        */
auto menu::oper() -> void
{
    enum select
    {
        COMPRESS = '1',
        DECPRESS = '2',
        RLE_COMPRESS = '3',
        RLE_DECPRESS = '4',
        LZ77_COMPRESS = '5',
        LZ77_DECPRESS = '6',
        DEFLATE_COMPRESS = '7',
        DEFLATE_DECPRESS = '8',
        EXIT = '0',
        EXIT_2 = 27,    // 提供使用ESC键关闭程序
    };

    int sec;
    do
    {
        sec = _getch();
        switch (sec)
        {
            case COMPRESS:
            {
                isrun = false;  // 阻塞 流动线程
                {
                    std::unique_lock lock{mx }; // 加锁
                    system("cls");
                    pcompress(std::function{compress }); // 进入新界面
                    isrun = true; // 允许流动线程的运行
                } // 析构 放锁
                system("cls");
                std::this_thread::sleep_for(std::chrono::duration<double>{ 0.5 });
                //cv.notify_one();    // 唤醒被阻塞的流动线程--------------- 怎么唤不醒？？？
                break;
            }
            case DECPRESS:
            {
                isrun = false;
                {
                    std::unique_lock lock{ mx };
                    system("cls");
                    pcompress(std::function{ depress });
                    isrun = true;
                }
                system("cls");
                std::this_thread::sleep_for(std::chrono::duration<double>{ 0.5 });
                break;
            }
            case RLE_COMPRESS:
            {
                isrun = false;
                {
                    std::unique_lock lock{ mx };
                    system("cls");
                    pcompress(std::function{ rle_compress });
                    isrun = true;
                }
                system("cls");
                std::this_thread::sleep_for(std::chrono::duration<double>{ 0.5 });
                break;
            }
            case RLE_DECPRESS:
            {
                isrun = false;
                {
                    std::unique_lock lock{ mx };
                    system("cls");
                    pcompress(std::function{ rle_depress });
                    isrun = true;
                }
                system("cls");
                std::this_thread::sleep_for(std::chrono::duration<double>{ 0.5 });
                break;
            }
            case LZ77_COMPRESS:
            {
                isrun = false;
                {
                    std::unique_lock lock{ mx };
                    system("cls");
                    pcompress(std::function{ lz_compress });
                    isrun = true;
                }
                system("cls");
                std::this_thread::sleep_for(std::chrono::duration<double>{ 0.5 });
                break;
            }
            case LZ77_DECPRESS:
            {
                isrun = false;
                {
                    std::unique_lock lock{ mx };
                    system("cls");
                    pcompress(std::function{ lz_depress });
                    isrun = true;
                }
                system("cls");
                std::this_thread::sleep_for(std::chrono::duration<double>{ 0.5 });
                break;
            }
            case DEFLATE_COMPRESS:
            {
                isrun = false;
                {
                    std::unique_lock lock{ mx };
                    system("cls");
                    pcompress(std::function{ deflate_compress });
                    isrun = true;
                }
                system("cls");
                std::this_thread::sleep_for(std::chrono::duration<double>{ 0.5 });
                break;
            }
            case DEFLATE_DECPRESS:
            {
                isrun = false;
                {
                    std::unique_lock lock{ mx };
                    system("cls");
                    pcompress(std::function{ deflate_depress });
                    isrun = true;
                }
                system("cls");
                std::this_thread::sleep_for(std::chrono::duration<double>{ 0.5 });
                break;
            }
            case EXIT:
            case EXIT_2:
            {
                isrun = false;
                std::unique_lock lock{ mx };
                system("cls");
                print("{}{}\n",blank,star);
                print("          *                                           *\n");
                print("{}*{}  >>file processing<<  {}*\n",blank,blank,blank);
                print("{}*{}                       {}*\n",blank,blank,blank);
                print("{}*{}                       {}*\n",blank,blank,blank);
                print("          *             wait to exiting...            *\n");
                print("{}*{}                       {}*\n",blank,blank,blank);
                print("{}*{}                       {}*\n",blank,blank,blank);
                print("{}{}\n",blank,star);

                std::this_thread::sleep_for(std::chrono::seconds{ 1 });
                isrun = true;
                lock.unlock();
                break;
            }
            default:{}
        }
    }while(sec != EXIT and sec != EXIT_2);

}
