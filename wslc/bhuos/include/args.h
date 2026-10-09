
#define _ARGSET(x) (x) = 0              // 将变量清零（用于宏内部临时变量）
#define _ARGUSED(x) if (x) {} else      // 使用变量避免未使用警告

// 简化的命令行参数解析宏（Plan 9 风格）
#define ARGBEGIN \
    for ((argv ? 0 : (argv = (void*)&argc)), \
         argv++, argc--; \
         argv[0] && argv[0][0] == '-' && argv[0][1]; \
         argc--, argv++) { \
        char* _args, *_argt; \
        char  _argc; \
        _args = &argv[0][1]; \
        if (_args[0] == '-' && _args[1] == 0) { \
            argc--; argv++; break; \
        } \
        _argc = 0; \
        while (*_args && (_argc = *_args++)) \
        switch (_argc)

#define ARGEND \
    _ARGSET(_argt); _ARGUSED(_argt); _ARGUSED(_argc); _ARGUSED(_args); } _ARGUSED(argv); _ARGUSED(argc) // 结束参数解析

#define ARGF() \
    (_argt = _args, _args = "", (*_argt ? _argt : argv[1] ? (argc--, *++argv) : 0)) // 获取选项参数（可空）

#define EARGF(x) \
    (_argt = _args, _args = "", (*_argt ? _argt : argv[1] ? (argc--, *++argv) : ((x), abort(), (char*)0))) // 获取必选参数

#define ARGC() _argc // 当前处理的选项字符
