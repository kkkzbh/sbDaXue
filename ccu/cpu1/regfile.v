`timescale 1ns / 1ps
//
// Company: 
// Engineer: 
// 
// Create Date: 2021/10/05 15:22:20
// Design Name: 
// Module Name: regfile
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//
module regfile(
    input clk,
    input RegWre,           // 寄存器写使能信号
    input [4:0] raddr1,     // 读地址1 (通常为rs)
    input [4:0] raddr2,     // 读地址2 (通常为rt)
    output reg[31:0] rdata1, // 读端口1输出数据
    output reg[31:0] rdata2, // 读端口2输出数据
    input [4:0] test_addr,  // 板上测试用读地址
    output reg[31:0] test_data, // 板上测试用读数据
    input [4:0] waddr,      // 写地址 (rd或rt)
    input [31:0] wdata      // 待写入的数据
    );

    // 定义32个32位的通用寄存器
reg [31:0] memory[31:0];
    
    // 初始化所有寄存器为0 (主要用于仿真)
integer i;
initial begin
        for(i=0; i<=31; i=i+1)
        begin
            memory[i] = 32'h0;
        end
    end

    // 读端口1 (异步读)
    always@(*)
    begin
        rdata1 = memory[raddr1];
    end

    // 读端口2 (异步读)
always@(*)
begin
        rdata2 = memory[raddr2];
end
    
    // 测试端口 (异步读)
always@(*)
 begin
        test_data = memory[test_addr];
 end

    // 写端口 (同步写)
 always@(posedge clk)
 begin
        // 当写使能有效且目标地址不为0时，在时钟上升沿写入数据
        // MIPS架构中，0号寄存器($zero)恒为0，不可写入
        if(RegWre == 1 && waddr != 5'b0)
     begin
            memory[waddr] <= wdata;
     end 
end

endmodule

