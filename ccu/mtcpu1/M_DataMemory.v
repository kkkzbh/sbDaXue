`timescale 1ns / 1ps
//
// M_DataMemory.v: 多周期 CPU 兼容的数据存储器
//
module M_DataMemory(
    input clk,
    input wenr,         // 读使能
    input wenw,         // 写使能
    input [31:0] DAddr,
    input [31:0] DataIn,
    output [31:0] DataOut,

    // 调试端口
    input [31:0] test_addr,
    output [31:0] test_data
    );

    reg [31:0] ram[255:0];
    integer i;

    initial begin
        for(i=0; i<256; i=i+1) begin
            ram[i] = 32'd0;
        end
    end

    // 同步写
    always @(posedge clk) begin
        if (wenw) begin
            ram[DAddr[7:0]] = DataIn; // 地址简化为低8位
        end
    end

    // 异步读
    // 当 wenr 无效时输出 0，而不是高阻态 'z'
    assign DataOut = wenr ? ram[DAddr[7:0]] : 32'd0;

    // 调试端口的输出
    assign test_data = ram[test_addr[7:0]];

endmodule 