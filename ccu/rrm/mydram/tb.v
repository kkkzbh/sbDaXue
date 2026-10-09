`timescale 1ns / 1ps
//
// Company: 
// Engineer: 
// 
// Create Date: 2021/10/05 22:19:41
// Design Name: 
// Module Name: tb
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


module tb;
    //inputs
    reg clk;
    reg  [3:0] wen;//写使能
    reg  [31:0] addr;
    reg  [31:0] wdata;
    reg  [31:0] test_addr;
    reg  [1:0] sec; // 仍然保留SEC作为测试信号
    
    wire [31:0] rdata;
    wire [31:0] test_data;
    
    // 根据SEC生成实际的写使能信号
    reg [3:0] actual_wea;
    
    always @(*)
    begin
        case(sec)
            2'd0: begin  // 1字节模式
                case(addr[1:0])
                    2'b00: actual_wea = {3'b000, wen[0]};
                    2'b01: actual_wea = {2'b00, wen[0], 1'b0};
                    2'b10: actual_wea = {1'b0, wen[0], 2'b00};
                    2'b11: actual_wea = {wen[0], 3'b000};
                endcase
            end
            2'd1: begin  // 2字节模式
                case(addr[1])
                    1'b0: actual_wea = {2'b00, {2{wen[0]}}};
                    1'b1: actual_wea = {{2{wen[0]}}, 2'b00};
                endcase
            end
            default: begin  // 4字节模式 (SEC=2)
                actual_wea = wen;
            end
        endcase
    end

    // 添加掩码处理逻辑，确保只有选定的字节被写入，其他字节正确保留
    reg [31:0] wdata_masked;
    
    always @(*) begin
        case(sec)
            2'd0: begin  // 1字节模式
                case(addr[1:0])
                    2'b00: wdata_masked = {rdata[31:8], wdata[7:0]};
                    2'b01: wdata_masked = {rdata[31:16], wdata[7:0], rdata[7:0]};
                    2'b10: wdata_masked = {rdata[31:24], wdata[7:0], rdata[15:0]};
                    2'b11: wdata_masked = {wdata[7:0], rdata[23:0]};
                endcase
            end
            2'd1: begin  // 2字节模式
                case(addr[1])
                    1'b0: wdata_masked = {rdata[31:16], wdata[15:0]};
                    1'b1: wdata_masked = {wdata[15:0], rdata[15:0]};
                endcase
            end
            default: begin  // 4字节模式 (SEC=2)
                wdata_masked = wdata;
            end
        endcase
    end
    
    data_ram uut (//仿真IP核，自动仿真用uut，IP核必须为同名才行
       .clka(clk),    // input wire clka
       .wea(actual_wea),      // input wire [3 : 0] wea
       .addra({3'b0,addr[6:2]}),  // input wire [7 : 0] addra
       .dina(wdata_masked),    // 使用掩码处理后的数据
       .douta(rdata),  // output wire [31 : 0] douta
       .clkb(clk),    // input wire clkb
       .web(4'b0000),  // 修改：B端口设置为只读
       .addrb({3'b0,test_addr[6:2]}),  // input wire [7 : 0] addrb
       .dinb(32'b0),
       .doutb(test_data)  // output wire [31 : 0] doutb
    );
    initial begin
    clk = 0;
    wen = 0;
    addr = 0;
    wdata = 0;
    test_addr = 0;
    sec = 2'd2; // 默认4字节模式
    
    #100
    wen = 4'b0001;
    addr = {8'd8, 2'b00};  // 确保4字节对齐 (0x20)
    test_addr = 8'd32;    // 读地址不需要特别对齐
    wdata = 32'd16;
    
    #100
    sec = 2'd0; // 切换到1字节模式
    addr = 8'd64;  // 1字节模式可以任意地址
    wdata = 32'd12;
    
    #100
    sec = 2'd1; // 切换到2字节模式
    test_addr = 8'd64;    // 读地址不需要特别对齐
    addr = {8'd17, 1'b0};  // 确保2字节对齐 (0x44)
    wdata = 32'hABCD1234;
    
    end
   always #5 clk = ~clk;

endmodule
