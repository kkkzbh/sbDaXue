`timescale 1ns / 1ps

module SignZeroExtend(
    input [15:0] Imm,       // 输入的16位立即数
    input Extsel,           // 扩展模式选择 (1: 符号扩展, 0: 零扩展)
    output [31:0] extendImm // 输出的32位扩展结果
    );
    
    // 将16位立即数的低16位直接赋给输出
    assign extendImm[15:0] = Imm;
    
    // 根据Extsel信号决定高16位的扩展方式
    // 如果Extsel为1，进行符号扩展：如果Imm的最高位(Imm[15])为1，则高16位全为1，否则全为0
    // 如果Extsel为0，进行零扩展：高16位全为0
    assign extendImm[31:16] = Extsel ? (Imm[15] ? 16'hffff : 16'h0000) : 16'h0000;
    
endmodule
