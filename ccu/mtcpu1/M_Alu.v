`timescale 1ns / 1ps
//
// M_Alu.v: 多周期 CPU 的运算器
//
module M_Alu(
    input [31:0] A,
    input [31:0] B,
    input [3:0]  Alu_Op,
    output reg zero,
    output reg [31:0] Alu_Result
    );

    always @(*) begin
        case (Alu_Op)
            4'b0000: Alu_Result = B;                           // pass-through (JR/LUI pre)
            4'b0001: Alu_Result = A + B;                       // add / addi / addu / addiu
            4'b0010: Alu_Result = A - B;                       // sub / subu / beq / bne
            4'b0011: Alu_Result = ($signed(A) < $signed(B)) ? 32'd1 : 32'd0; // slt / slti
            4'b0100: Alu_Result = A & B;                       // and / andi
            4'b0101: Alu_Result = A | B;                       // or  / ori
            4'b0110: Alu_Result = A ^ B;                       // xor / xori
            4'b0111: Alu_Result = ~(A | B);                    // nor
            4'b1000: Alu_Result = (A < B) ? 32'd1 : 32'd0;     // sltu / sltiu (无符号比较)
            // 移位类：对 B 的低 5 位或 shamt 进行操作
            4'b1001: Alu_Result = B << A[4:0];                 // sllv / sll (后续 datapath 提供 shamt 至 A)
            4'b1010: Alu_Result = B >> A[4:0];                 // srlv / srl
            4'b1011: Alu_Result = $signed(B) >>> A[4:0];       // srav / sra
            4'b1100: Alu_Result = A << B[4:0];                 // sll (A=shamt, B=reg) 备用
            4'b1101: Alu_Result = A >> B[4:0];                 // srl 备用
            4'b1110: Alu_Result = $signed(A) >>> B[4:0];       // sra 备用
            4'b1111: Alu_Result = {B[15:0], 16'd0};            // lui
            default: Alu_Result = 32'hdeadbeef;                // 未定义
        endcase

        if (Alu_Result == 32'd0)
            zero = 1'b1;
        else
            zero = 1'b0;
    end
endmodule 