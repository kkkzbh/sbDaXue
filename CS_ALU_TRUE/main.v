module alu(alu_control,alu_src1,alu_src2,alu_result,overflow);
    input  [11:0] alu_control;  // ALU控制信号
    input  [31:0] alu_src1;     // ALU操作数1
    input  [31:0] alu_src2;     // ALU操作数2
    output [31:0] alu_result;   // ALU结果
    output [1:0]  overflow;     // 溢出标志 [1]:有符号溢出 [0]:无符号溢出
    
    reg [31:0] alu_result;
    reg [1:0]  overflow;
    
    // 组合逻辑电路
    always @(*)
    begin
        // 默认不溢出
        overflow <= 2'b00;
        
        case(alu_control)   // 控制码1，2指控制码第1位，第二位
            12'b000000000001:alu_result<=alu_src1<<16;         // 左移定长       1
            12'b000000000010:alu_result<=alu_src1>>>alu_src2;         // 算术右移       2
            12'b000000000011:alu_result<=~alu_src1;            // 取反功能       3
            12'b000000000100:alu_result<=alu_src1>>alu_src2; // 逻辑右移      4
            12'b000000001000:alu_result<=alu_src1<<alu_src2; // 逻辑左移      8
            12'b000000010000:alu_result<=alu_src1^alu_src2; // 按位异或    16
            12'b000000100000:alu_result<=alu_src1|alu_src2;// 按位或    32
            12'b000001000000:alu_result<=~(alu_src1|alu_src2); // 按位或非       64
            12'b000010000000:alu_result<=alu_src1&alu_src2; // 按位与       128
            12'b000100000000:alu_result<=alu_src1<alu_src2?32'd1:32'd0;// 无符号比较，小则置位  256
            12'b001000000000:alu_result<=$signed(alu_src1)<$signed(alu_src2)?32'd1:32'd0;// 有符号比较，小则置位  512
            12'b010000000000:begin // 加法     1024
                alu_result <= alu_src1 + alu_src2;
                
                // 有符号加法溢出检测：两正数相加为负或两负数相加为正
                overflow[1] <= (alu_src1[31] == alu_src2[31]) && (alu_result[31] != alu_src1[31]);
                
                // 无符号加法溢出检测：结果小于任一操作数
                overflow[0] <= (alu_result < alu_src1) || (alu_result < alu_src2);
            end
            12'b100000000000:begin // 减法     2048
                alu_result <= alu_src1 - alu_src2;
                
                // 有符号减法溢出检测：正减负为负或负减正为正
                overflow[1] <= (alu_src1[31] != alu_src2[31]) && (alu_result[31] != alu_src1[31]);
                
                // 无符号减法溢出检测：如果第一个操作数小于第二个操作数
                overflow[0] <= (alu_src1 < alu_src2);
            end
            default: alu_result<=alu_src1;
        endcase
    end
endmodule