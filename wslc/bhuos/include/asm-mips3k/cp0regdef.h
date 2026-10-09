#ifndef _cp0regdef_h_ // 头文件防重包含开始
#define _cp0regdef_h_ // 定义本头文件的防重包含宏

#define CP0_INDEX     $0  // TLB 索引寄存器
#define CP0_RANDOM    $1  // TLB 随机索引
#define CP0_ENTRYLO0  $2  // TLB 偶数项低位
#define CP0_ENTRYLO1  $3  // TLB 奇数项低位
#define CP0_CONTEXT   $4  // 上下文寄存器
#define CP0_PAGEMASK  $5  // TLB 页大小掩码
#define CP0_WIRED     $6  // 固定 TLB 项个数
#define CP0_BADVADDR  $8  // 错误虚拟地址
#define CP0_COUNT     $9  // 计数器
#define CP0_ENTRYHI   $10 // TLB 高位（含 ASID）
#define CP0_COMPARE   $11 // 计数器比较寄存器
#define CP0_STATUS    $12 // 处理器状态
#define CP0_CAUSE     $13 // 异常原因
#define CP0_EPC       $14 // 异常返回地址
#define CP0_PRID      $15 // 处理器标识
#define CP0_CONFIG    $16 // 配置寄存器
#define CP0_LLADDR    $17 // LL 地址
#define CP0_WATCHLO   $18 // 访存监视（低）
#define CP0_WATCHHI   $19 // 访存监视（高）
#define CP0_XCONTEXT  $20 // 扩展上下文
#define CP0_FRAMEMASK $21 // 帧掩码
#define CP0_DIAGNOSTIC $22 // 诊断寄存器
#define CP0_PERFORMANCE $25 // 性能计数
#define CP0_ECC       $26 // ECC
#define CP0_CACHEERR  $27 // Cache 错误
#define CP0_TAGLO     $28 // Cache 标记低
#define CP0_TAGHI     $29 // Cache 标记高
#define CP0_ERROREPC  $30 // 异常时的 EPC 备份

#endif // 结束防重包含
