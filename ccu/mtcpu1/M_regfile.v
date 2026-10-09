`timescale 1ns / 1ps
//
// M_regfile.v: 带写前馈的寄存器堆
//
module M_regfile(
    input clk,
    input RegWre,
    input [4:0] raddr1,
    input [4:0] raddr2,
    input [4:0] waddr,
    input [31:0] wdata,
    output [31:0] rdata1,
    output [31:0] rdata2,

    // 调试端口
    input [4:0] test_addr,
    output [31:0] test_data
    );

    reg [31:0] registers[31:0];
    integer i;

    // 初始化寄存器
    initial begin
        for (i = 0; i < 32; i = i + 1) begin
            registers[i] = 32'd0;
        end
    end

    // 同步写
    always @(posedge clk) begin
        if (RegWre && waddr != 5'd0) begin // $0 永远是 0
            registers[waddr] <= wdata;
        end
    end

    // 异步读，带写前馈逻辑
    // 如果读地址和写地址相同，且写使能有效，则直接输出正在写入的数据
    assign rdata1 = (RegWre && raddr1 != 5'd0 && raddr1 == waddr) ? wdata : registers[raddr1];
    assign rdata2 = (RegWre && raddr2 != 5'd0 && raddr2 == waddr) ? wdata : registers[raddr2];

    // 调试端口的输出
    assign test_data = registers[test_addr];

endmodule 