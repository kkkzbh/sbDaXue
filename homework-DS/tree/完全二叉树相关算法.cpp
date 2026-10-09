

// 0 开始下标

#define LEFT(i) ((i << 1) + 1)
#define RIGHT(i) (LEFT(i) + 1)
#define UP(i) ((i - 1) >> 1)

// 1 开始下标

#define LEFT(i) (i << 1)
#define RIGHT(i) (LEFT(i) + 1)
#define UP(i) (i >> 1)
