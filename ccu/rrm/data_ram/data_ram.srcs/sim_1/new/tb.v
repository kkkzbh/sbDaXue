`timescale 1ns / 1ps
//
// Company: 
// Engineer: 
// 
// Create Date: 2021/11/07 20:57:41
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


module tb();
    reg clk;
    reg [31:0]addr;
    wire [31:0]inst;
    inst_rom inst_rom_module(
        .clka  (clk),
        .addra  ({3'b0,addr[6:2]}),//赋值范围4-64对应addra:8-256，转换成十六进制0008-0100
        .douta (inst[31:0])
    );
    initial begin
    clk=0;
    addr=0;
    #100//4对应1，8对应2，16对应4，范围4-64
    addr=4;
    #100
    addr=8;
    
    
    end
   always #5 clk = ~clk;
endmodule

