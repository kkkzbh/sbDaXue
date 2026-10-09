
#include"fun.h"
#include<conio.h>
#include"menu.h"

/* ************ /*

    如果此前定义了宏 OPTIMISE 那么就会开启这两个函数的优化版本
    不过经实验表明,优化版本没有未优化版本的压缩效果好,但优化版本有应对更大文件的能力 (10G以上数量级的文件)

/* ************ */

#ifdef OPTIMISE

#include"string_buffer.h"
#include"hash.h"

#endif

constexpr static char star[]{ "*********************************************" };
constexpr static char blank[]{ "          " };
constexpr static uint64 M_byte{ 8 };
constexpr static uint64 buf_sz{ M_byte * sizeof(int) };


/*    这个就是压缩函数了,实现思路很大众 不过我会尽可能的给出较多的注释说明       */
auto compress(const std::string_view file,const std::string_view output) -> bool
{

    progress::bar = std::thread{ progress::pcompress }; // 开始 进度条线程  对于了解压缩函数而言 这个可以选择忽略


    /*
     *  以下语句 主要是在一个try-catch语句块中构造哈夫曼树 这里使用一个词频表构造哈夫曼树
     *  关于哈夫曼树更多的信息 详见 huftree.h和cpp
     *  如果file无法正常打开 word_frequncy(统计词频的函数，返回一个词频表 详见 statistics.h和cpp )  那么就会抛出异常
     *  接受 异常后 关闭进度条线程 退出程序
     */
    huftree tree;
    try
    {
        tree = huftree{word_frequency(file)};
    }
    catch(std::invalid_argument& e)
    {

        progress::end = true;   //   关闭加载线程
        progress::bar.join();   // 等待记载线程 被关闭
        progress::end = false;  // 恢复end变量

        std::this_thread::sleep_for(std::chrono::seconds{ 1 });
        system("cls");
        std::cerr << e.what() << "\npress enter for continuing..." << std::endl;
        std::cin.ignore();
        std::cin.get();

        return false;
    }

    //  这里在哈夫曼树 可以正常构造时 利用这棵哈夫曼树 构造类 哈夫曼编码 详见huftree.h和.cpp
    //  简要起见 hufcode 存储了 每个字符对应的01字符串 和 每个01字符串对应的字符 且重载了[] 根据[]内的参数 选择性返回对应的值
    hufcode huf{ tree };

    progress::compress_bar.replace(progress::st_index,3," 10"); // 更新进度... 可以不必了解

    // 这里尝试打开文件
    std::ifstream ifs{ file.data(), std::ios::binary };
    if(!ifs)    // 如果文件打开不成功 关闭线程 退出函数  析构函数会自动关闭打开的文件 下方不在过多说明
    {
        progress::end = true;   //   关闭加载线程
        progress::bar.join();   // 等待记载线程 被关闭
        progress::end = false;  // 恢复end变量

        std::this_thread::sleep_for(std::chrono::seconds{ 1 });
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x04);
        std::cerr << "Can not open the file!\n"
                     "press enter for continuing..." << std::ends;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x00);
        std::cin.ignore();
        std::cin.get();

        return false;
    }

    char c;

    //progress::compress_bar.replace(progress::st_index,3," 21"); // 更新进度条 不必过多关注

    /* ****************************** /*

     以下就是来到了两个分支
     如果没有定义宏 OPTIMISE 走未优化版本
     如果定义宏 OPTIMISE 走优化版本
     这个宏 要在utility.h 中被定义
     不过目前实验表明 未优化的目前压缩效果更好
     但在此简要解释他们两个的区别

     未优化版 : 把全部的外村都读到了内存中处理  实现更为简单  但缺点显而易见
     优化版 : 改成读一段外存 就压缩一点 然后重复操作，为了高效率的动态处理
            采用了基于循环队列实现的字符串缓冲类 string_buffer 详见string_buffer.h和.cpp

     是的 我处理他们两个版本 只有这点儿区别 但确实神奇的是 未优化版的压缩效果更好
     但多说一句 还有另一个优化版本 不过我没有在哈夫曼编码这里写出
     以上的两个版本 存入的解码器都是一个 基于散列查找实现的map 详见map.h (没有.cpp 因为是模板)
     然后解压时 利用这个map 去实现解码
     不过众所周知 基于散列查找实现的一个特点就是 空间换时间
     所以还有第三个优化版本 存入的解码器不是map 而是一棵哈夫曼树
     解码时 则是利用一个哈夫曼树迭代器 在树上游走实现解码  关于这个迭代器 详见huftree.h
     不过这个优化的实现 我放入了 deflate相关压缩解压的优化版本中 详见 deflate.h和.cpp
     不过实验表明 可能是我哈夫曼树 底层采用的 std::vector存储数据 因而效果不如静态的512固定大小的 C风格数组效果好
     对于小文件而言 差距很大的 但是考虑到 对于稍大文件而言 这点差距并不算大 故因而没有大改代码

    /* ****************************** */

#ifndef OPTIMISE

    std::string data;   // 该字符串data 就是把全部外存读到这个字符串的内存中去 但不是无脑读 是带着编码读
    while(ifs.get(c))
    {
        data += huf[c];   // huf[c] 返回一个 c字符对应的 编码  不必担心c(char)可以是负数导致越界 因为[]接受的参数是 unsinged chare
    }
    std::ofstream ofs{ output.data(),std::ios::binary };    // 打开输出文件
    write(huf.map,ofs); // 先写入解码器

    progress::compress_bar.replace(progress::st_index,3," 40"); // 忽略 加载进度条

    uint64 sz{ data.size() };  // data总的长度 写入文件

    ofs.write(reinterpret_cast<const char*>(&sz),sizeof(sz));
    uint64 i{};

    progress::compress_bar.replace(progress::st_index,3," 67");

    for(; sz >= buf_sz; sz -= buf_sz,i += buf_sz) // 开始以块的方式 写入  这里我与大多数采用char 8位块不同 我改用了32位的 int块
    {
        int put{ to_int(i,data) };  // to_int 函数用于接受一个字符串 并根据其前32个01序列 返回一个int 详见 utility.h和.cpp
        ofs.write(reinterpret_cast<const char*>(&put),sizeof(int)); // 写入int
    }

    progress::compress_bar.replace(progress::st_index,3," 99");

    ofs.write(data.data() + i,static_cast<int64>(sz));  // 剩余不足32位的 全部按01字节写入文件

    progress::compress_bar.replace(progress::st_index,3,"100");

    /*              至此，解压结束 下面则是优化版本的实现                             */
#endif
#ifdef OPTIMISE

    std::ofstream ofs{ "buff",std::ios::binary };    // !!!!!! 注意这里我打开了一个buff文件 用于先写入临时文件 这一切都是服务于 最后不满32位的判断

    progress::compress_bar.replace(progress::st_index,3," 24");

    string_buffer buf;  // 基于循环队列实现
    uint cnt{}; // 记录写入了几次int  这个对于最后不满32位时 判断到底有几位起着一个作用

    while(ifs.get(c))
    {
        const std::string& str{ huf[static_cast<uint8>(c)] }; // 把 c 字符的01序列 先生成一个小字符串
        buf.push(str.data());   // 01序列追加到buf中
        while(buf.size() >= buf_sz)    // buf_sz = 32  也就是buf说大于一个int字节时 直接开始压缩处理
        {
            int put{ buf.to_int() };    // buf.to_int() 是buf类内的函数 这个to_int 详见 string_buffer.h和.cpp
            ofs.write(reinterpret_cast<const char *>(&put), sizeof(put));
            ++cnt;
        }
    }

    progress::compress_bar.replace(progress::st_index,3," 48");

    ofs.close();
    ifs.close();
    ifs.open("buff",std::ios::binary);   // ifs打开buff文件
    ofs.open(output.data(),std::ios::binary);   // 这是正常打开output文件

    write(huf.map,ofs); // 写入解码器
    ofs.write(reinterpret_cast<const char*>(&cnt),sizeof(cnt)); // 写入 写了几个int

    while(ifs.get(c))
    {
        ofs.write(&c, sizeof(c));   // 把buff文件 写到output里
    }

    progress::compress_bar.replace(progress::st_index,3," 82");

    uint8 sz{ static_cast<uint8>(buf.size()) }; // 这里是 循环队列中剩余的字符数量

    if (sz)  // 如果sz不为0  则最后共写5个字节
    {
        ofs.write(reinterpret_cast<const char *>(&sz), sizeof(sz)); // uint8 一个字节 存大小
        int put{buf.to_int()};  // buf.to_int() 即使 buf不够32位 也能正常处理返回一个int 自动补充尾后0 是尾后0
        ofs.write(reinterpret_cast<const char *>(&put), sizeof(put));   // 写入这个残次的int
    };

    progress::compress_bar.replace(progress::st_index,3,"100");

    /*                至此，优化版本的压缩结束               */
#endif


    progress::end = true;   //   关闭加载线程
    progress::bar.join();   // 等待记载线程 被关闭
    progress::end = false;  // 恢复end变量

    progress::compress_bar.replace(progress::st_index,3,"  0");

    return true;
}


/*   !!!!    基于compress 函数已经给出了足够多的注释  以下解压函数则只选取必要的给出注释          !!!!          */

auto depress(const std::string_view file,const std::string_view output) -> bool
{

    progress::bar = std::thread{ progress::pdecpress }; // 开始 加载线程

    std::ifstream ifs{ file.data(),std::ios::binary };
    if(!ifs)
    {
        progress::end = true;   //   关闭加载线程
        progress::bar.join();   // 等待记载线程 被关闭
        progress::end = false;  // 恢复end变量

        std::this_thread::sleep_for(std::chrono::seconds{ 1 });
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x04);
        print("{}{}\n",blank,star);
        print("          *                                           *\n");
        print("{}*{}  >>file processing<<  {}*\n",blank,blank,blank);
        print("           *           Can not open the file!         *\n");
        print("{}*{}                       {}*\n",blank,blank,blank);
        print("          *        press enter for continuing...      *\n");
        print("{}*{}                       {}*\n",blank,blank,blank);
        print("{}*{}                       {}*\n",blank,blank,blank);
        print("{}{}\n",blank,star);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x00);
        std::cin.ignore();
        std::cin.get();

        return false;
    }

    progress::compress_bar.replace(progress::st_index,3,"  2");

    hufcode huf{ ifs };

#ifndef OPTIMISE

    std::string data;
    uint64 sz;
    ifs.read(reinterpret_cast<char*>(&sz),sizeof(sz));

    progress::compress_bar.replace(progress::st_index,3," 27");

    uint64 int_cnt{ sz / buf_sz };
    while(int_cnt--)
    {
        uint get;
        ifs.read(reinterpret_cast<char*>(&get),sizeof(int));
        data += std::bitset<buf_sz>{ get }.to_string();
    }

    char c;
    while(ifs.get(c))
    {
        data += c;
    }

    progress::compress_bar.replace(progress::st_index,3," 41");

    progress::compress_bar.replace(progress::st_index,3," 73");

    std::string buffer;
    std::ofstream ofs{ output.data(),std::ios::binary };

    // 以下就是解码了

    for(const auto ch : data)   // 遍历data这个01序列
    {
        buffer.push_back(ch); // 插入01 到buffer中
        auto it{ huf.map.find(buffer) }; // 散列查找目前的buffer是否可以匹配一个字符 该迭代器是map的一个迭代器 详见map.h
        if(it != huf.map.end()) // 如果匹配到了
        {
            ofs.write(reinterpret_cast<const char*>(&it->second),sizeof(it->second)); // 写入字符
            buffer.clear(); // 清空buffer
        }
    }

    progress::compress_bar.replace(progress::st_index,3," 99");

#endif

#ifdef OPTIMISE

    string_buffer buf;
    uint block;
    uint cnt;

    ifs.read(reinterpret_cast<char*>(&cnt),sizeof(cnt));

    std::ofstream ofs{ output.data(),std::ios::binary };

    while(cnt-- and ifs.read(reinterpret_cast<char*>(&block),sizeof(block)))
    {
        buf += std::bitset<M_byte * sizeof(block)>{ block }.to_string().data();
        std::string b;
        uint64 key{};
        // 这里的思路一样 也是走一个字符 往b插一个 然后散列查找
        // 但是为什么长了这么多
        // 每次散列查找 都需要计算字符串的哈希值
        // 我为了提高效率 那么就在现在这个外层 提前的以dp的方式计算哈希值
        // 每次新插入字符时 利用已有的哈希值 O(1)生成新的哈希值 去帮助map散列查找
        // 这样实现效率会更高, 也是优化版本中 基于解压速率作出的一个优化
        for(const auto it : buf)
        {
            key *= prime;
            key += it;
            b += it;
            auto i{ huf.map.find(key,b) };
            if(i != huf.map.end())
            {
                ofs.write(reinterpret_cast<const char*>(&i->second),sizeof(i->second));
                buf.move(b.size());
                b.clear();
                key = 0;
            }
        }
    }
    char sz;
    // 这里就是对剩余不够32个的 处理了 不过我与未优化版不同 这里最后是插了一个 含尾后0的int
    // 故下面会有位运算 int 转 string 利用 现在从文件读入的第一个字节得到 这个int前几位是有效的
    // 下面的if其实有些巧妙  在上面的压缩时 如果sz为0 我们不会压缩 这里的 ifs.get(sz) 直接false跳过
    // 如果有sz 则直接ifs.get(sz) 读入了第一个字节(存储这个int是几位有效的） 然后函数体内直接读入int
    if(ifs.get(sz))
    {
        int get;
        ifs.read(reinterpret_cast<char*>(&get),sizeof(get));
        uint tag{ 1u << 31 };
        for(uint8 i{ 1 }; i <= sz; ++i) // 转字符串
        {
            buf += static_cast<char>(((get & tag) >> 31u) ^ 48);
            get <<= 1;
        }
        std::string b;
        uint64 key{};
        for(const auto it : buf)    // 解码
        {
            key *= prime;
            key += it;
            b += it;
            auto i{ huf.map.find(key,b) };
            if(i != huf.map.end())
            {
                ofs.write(reinterpret_cast<const char*>(&i->second),sizeof(i->second));
                buf.move(b.size());
                b.clear();
                key = 0;
            }
        }
    }

#endif


    progress::compress_bar.replace(progress::st_index,3,"100");

    progress::end = true;   //   关闭加载线程
    progress::bar.join();   // 等待记载线程 被关闭
    progress::end = false;  // 恢复end变量

    progress::decpress_bar.replace(progress::st_index,3,"  0");

    return true;
}