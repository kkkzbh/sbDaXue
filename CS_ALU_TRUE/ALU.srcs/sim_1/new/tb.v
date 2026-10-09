`timescale 1ns / 1ps
module tb;
    reg   [11:0] alu_control;  // ALU控制信号
    reg   [31:0] alu_src1;     // ALU操作数1
    reg   [31:0] alu_src2;     // ALU操作数2
    wire  [31:0] alu_result;   // ALU结果
    wire  [1:0]  overflow;     // 溢出标志 [1]:有符号溢出 [0]:无符号溢出
    
    alu alu_module(
        .alu_control(alu_control),
        .alu_src1   (alu_src1   ),
        .alu_src2   (alu_src2   ),
        .alu_result (alu_result ),
        .overflow   (overflow   )
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
        alu_control=12'b000000000011;   // 3 - 新增的取反功能
            #10;
            alu_src1=32'h5A5A5A5A; // 测试取反
            #10;
            alu_src1=32'hFFFFFFFF;
            #10;
            alu_src1=32'h00000000;
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
        alu_control=12'b010000000000;     // 1024 - 加法，测试溢出
            #10;
            alu_src1=32'd1;
            alu_src2=32'd1;
            #10;
            alu_src1=32'h7FFFFFFF; // 最大正数
            alu_src2=32'd1;       // 加1应该有符号溢出
            #10;
            alu_src1=32'h80000000; // 最小负数
            alu_src2=32'hFFFFFFFF; // -1，加法应该有符号溢出
            #10;
            alu_src1=32'hFFFFFFFF; // 无符号最大值
            alu_src2=32'h1;       // 加1应该无符号溢出
            #10;
            alu_src1=32'hFFFFFFFF;
            alu_src2=32'hFFFFFFFF; // 两个最大无符号数相加，应该无符号溢出
        #50;
        alu_control=12'b100000000000;     // 2048 - 减法，测试溢出
            #10;
            alu_src1=32'd10;
            alu_src2=32'd5;      // 正常减法，不溢出
            #10;
            alu_src1=32'h80000000; // 最小负数
            alu_src2=32'd1;       // 减1应该有符号溢出
            #10;
            alu_src1=32'h7FFFFFFF; // 最大正数
            alu_src2=32'hFFFFFFFF; // -1，减法应该有符号溢出
            #10;
            alu_src1=32'd5;
            alu_src2=32'd10;     // 5-10应该无符号溢出
    end
endmodule