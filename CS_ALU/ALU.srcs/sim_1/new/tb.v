`timescale 1ns / 1ps
module tb;
    reg   [11:0] alu_control;  // ALU�����ź�
    reg   [31:0] alu_src1;     // ALU������1
    reg   [31:0] alu_src2;     // ALU������2
    wire  [31:0] alu_result;   // ALU���
    alu alu_module(
        .alu_control(alu_control),
        .alu_src1   (alu_src1   ),
        .alu_src2   (alu_src2   ),
        .alu_result (alu_result )
    );
 
    initial begin
        alu_control=12'd0;
        alu_src1=32'd0;
        alu_src2=32'd0;
        #10;
		alu_control=12'b000000000001;     // 1
            #10;
            alu_src1=32'd1024;
            #10;
            alu_src1=32'd512;
            #10;
            alu_src2=32'd64;
		#50;
        alu_control=12'b000000000010;   // 2
            #10;
            alu_src2=32'd1024;
            #10;
            alu_src2=32'd512;
            #10;
            alu_src1=32'd64;
        #50;
        // 添加新的测试用例，测试按位取反操作 (control = 3)
        alu_control=12'b000000000011;     // 3
            #10;
            alu_src1=32'h0000FFFF;        // 测试取反操作 0000FFFF -> FFFF0000
            #10;
            alu_src1=32'hAAAA5555;        // 测试取反操作 AAAA5555 -> 5555AAAA
            #10;
            alu_src1=32'h00000000;        // 测试取反操作 00000000 -> FFFFFFFF
        #50;
        alu_control=12'b000000000100;     // 4
            #10;
            alu_src1=32'd192;
            #10;
            alu_src2=32'd192;
            #10;
            alu_src2=32'd16;
        #50;
        alu_control=12'b000000001000;     // 8
            #10;
            alu_src1=32'd192;
            #10;
            alu_src2=32'd192;
            #10;
            alu_src2=32'd16;
        #50;
        alu_control=12'b000000010000;     // 16
            #10;
            alu_src1=32'd128;
            #10;
            alu_src2=32'd127;
            #10;
            alu_src2=32'd0;
        #50;
        alu_control=12'b000000100000;     // 32
            #10;
            alu_src1=32'd128;
            #10;
            alu_src2=32'd127;
            #10;
            alu_src2=32'd0;
        #50;
        alu_control=12'b000001000000;     // 64
            #10;
            alu_src1=32'hffffffff;
            #10;
            alu_src2=32'h1;
            #10;
            alu_src2=32'hffffffff;
        #50;
        alu_control=12'b000010000000;     // 128
            #10;
            alu_src1=32'h0fffffff;
            #10;
            alu_src2=32'h1;
            #10;
            alu_src1=32'h0;
        #50;
        alu_control=12'b000100000000;     // 256
            #10;
            alu_src1=32'hffffffff;
            alu_src2=32'd1;
            #10;
            alu_src2=32'd3;
            #10;
            alu_src2=32'd5;
        #50;
        alu_control=12'b001000000000;     // 512
            #10;
            alu_src1=32'd1;
            #10;
            alu_src1=32'd3;
            alu_src2=32'hffffffff;
            #10;
            alu_src1=32'd5;
        #50;
        alu_control=12'b010000000000;     // 1024
            #10;
            alu_src1=32'd1;
            #10;
            alu_src1=32'd2048;
            #10;
            alu_src1=32'hf0000000;
        #50;
        alu_control=12'b100000000000;     // 2048
            #10;
            alu_src1=32'd1;
            #10;
            alu_src1=32'd2048;
            #10;
            alu_src1=32'hf0000000;
    end
endmodule