`timescale 1ns / 1ps
// -----------------------------------------------------------------------------
// P_DataMemory.v : 4 KB data RAM with synchronous write, asynchronous read.
//                  Only word store (sw) is needed for the self-test.
// -----------------------------------------------------------------------------
module P_DataMemory(
    input             clk,
    input             we,     // write enable
    input      [31:0] addr,   // byte address
    input      [31:0] wdata,
    output     [31:0] rdata,
    // debug port
    input      [31:0] test_addr,
    output     [31:0] test_data
);
    reg [31:0] ram [0:1023]; // 4 KB
    integer i;
    initial begin
        for (i = 0; i < 1024; i = i + 1) begin
            ram[i] = 32'h00000000;
        end
    end

    // 计算字地址，只取地址的高位，忽略低2位（字节偏移）
    wire [9:0] word_addr = addr[11:2];

    // 确保写入时同步并且能立即反映在读取上
    always @(posedge clk) begin
        if (we) begin
            ram[word_addr] <= wdata;
            $display("Writing memory: addr=%h, data=%h, actual_index=%d", addr, wdata, word_addr);
        end
    end

    // 读取数据时，确保使用字地址
    assign rdata = ram[word_addr];
    // debug read (word addressing)
    assign test_data = ram[test_addr[11:2]];
endmodule
