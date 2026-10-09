`timescale 1ns / 1ps
// -----------------------------------------------------------------------------
// P_alu.v : 32-bit ALU supporting a minimal subset of MIPS-like operations needed
//           for the provided code.mem self-test.
// -----------------------------------------------------------------------------
module P_alu(
    input      [3:0]  alu_ctrl,
    input      [31:0] op1,
    input      [31:0] op2,
    output reg [31:0] result,
    output            zero
);
    // ALU control encoding (4 bits)
    localparam ALU_ADD  = 4'b0000;
    localparam ALU_SUB  = 4'b0001;
    localparam ALU_SLT  = 4'b0010;
    localparam ALU_SLTU = 4'b0011;
    localparam ALU_AND  = 4'b0100;
    localparam ALU_OR   = 4'b0101;
    localparam ALU_XOR  = 4'b0110;
    localparam ALU_NOR  = 4'b0111;
    localparam ALU_SLL  = 4'b1000;
    localparam ALU_SRL  = 4'b1001;
    localparam ALU_SRA  = 4'b1010;
    localparam ALU_LUI  = 4'b1011;

    always @(*) begin
        case (alu_ctrl)
            ALU_ADD : result = op1 + op2;
            ALU_SUB : result = op1 - op2;
            ALU_SLT : result = ($signed(op1) < $signed(op2)) ? 32'd1 : 32'd0;
            ALU_SLTU: result = (op1 < op2) ? 32'd1 : 32'd0;
            ALU_AND : result = op1 & op2;
            ALU_OR  : result = op1 | op2;
            ALU_XOR : result = op1 ^ op2;
            ALU_NOR : result = ~(op1 | op2);
            // For all shift operations:
            // - op1[4:0] contains the shift amount (either from shamt field or rs register)
            // - op2 contains the value to be shifted
            ALU_SLL : begin
                result = op2 << op1[4:0]; // Shift left logical
            end
            ALU_SRL : begin
                result = op2 >> op1[4:0]; // Shift right logical
            end
            ALU_SRA : begin
                result = $signed(op2) >>> op1[4:0]; // Shift right arithmetic
            end
            ALU_LUI : result = {op2[15:0], 16'd0}; // Load upper immediate (bits 15:0 to 31:16)
            default : result = 32'd0;
        endcase
    end

    assign zero = (result == 32'd0);
endmodule
