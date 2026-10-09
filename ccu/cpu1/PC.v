`timescale 1ns / 1ps

module PC(
    input clk,
    input rst,         // Use a consistent reset signal name
    input PCWre,       // PC write enable
    input [1:0] PCSrc,   // PC source selection
    input [31:0] Imm,       // Sign-extended immediate for branches
    input [31:0] instruction, // Instruction for J-type jumps
    output reg [31:0] addr = 32'd0 // PC output address, initialized
);

    // Use an intermediate wire for PC + 4 to avoid synthesis issues
    // with slicing from an arithmetic result.
    wire [31:0] pc_plus_4 = addr + 4;

    // PC update logic
    always @(posedge clk or posedge rst)
    begin
        if (rst) // Asynchronous reset
        begin
            addr <= 32'd0;
        end
        else if (PCWre) // Update PC if enabled
        begin
            case(PCSrc)
                // PC = PC + 4
                2'b00:   addr <= pc_plus_4;
                // Branch: PC = PC + 4 + (offset << 2)
                2'b01:   addr <= pc_plus_4 + (Imm << 2);
                // Jump: PC = { (PC+4)[31:28], addr, 00 }
                2'b10:   addr <= { pc_plus_4[31:28], instruction[25:0], 2'b00 };
                // Stall: PC holds its value
                2'b11:   addr <= addr;
                default: addr <= pc_plus_4;
            endcase
        end
    end

endmodule
