module alu(alu_control,alu_src1,alu_src2,alu_result);
    input  [11:0] alu_control;  // ALU控制信号
    input  [31:0] alu_src1;     // ALU操作数1
    input  [31:0] alu_src2;     // ALU操作数2
    output [31:0] alu_result;   // ALU结果
    reg [31:0] alu_result;
    // 组合信号为组合逻辑
    always @(*)
    begin
        case(alu_control)   // 控制信号指示操作类型
            12'b000000000001:alu_result<=alu_src1<<16;         // 左移16位       1
            12'b000000000010:alu_result<=alu_src1>>>alu_src2;  // 算术右移       2
            12'b000000000011:alu_result<=~alu_src1;            // 按位取反       3
            12'b000000000100:alu_result<=alu_src1>>alu_src2;   // 逻辑右移       4
            12'b000000001000:alu_result<=alu_src1<<alu_src2;   // 逻辑左移       8
            12'b000000010000:alu_result<=alu_src1^alu_src2;    // 按位异或      16
            12'b000000100000:alu_result<=alu_src1|alu_src2;    // 按位或        32
            12'b000001000000:alu_result<=~(alu_src1|alu_src2); // 按位或非      64
            12'b000010000000:alu_result<=alu_src1&alu_src2;    // 按位与       128
            12'b000100000000:alu_result<=alu_src1<alu_src2?32'd1:32'd0;                  // 无符号比较（小于置位）  256
            12'b001000000000:alu_result<=$signed(alu_src1)<$signed(alu_src2)?32'd1:32'd0;// 有符号比较（小于置位）  512
            12'b010000000000:alu_result<=alu_src1+alu_src2;    // 加法        1024
            12'b100000000000:alu_result<=alu_src1-alu_src2;    // 减法        2048
            default: alu_result<=alu_src1;
        endcase
    end
endmodule