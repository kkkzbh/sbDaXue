`timescale 1ns / 1ps
// -----------------------------------------------------------------------------
// P_InstructionMemory.v : simple synchronous read-only instruction memory
// depth = 1024 words (4 KB)
// -----------------------------------------------------------------------------
module P_InstructionMemory(
    input             clk,
    input      [31:0] addr,   // word-aligned byte address
    output reg [31:0] inst
);
    // 1024 x 32-bit memory
    reg [31:0] rom [0:1023];

    initial begin
        $readmemh("code.mem", rom);
    end

    wire [9:0] word_addr = addr[11:2]; // 4-byte aligned, 2^10=1024

    always @(posedge clk) begin
        inst <= rom[word_addr];
    end
endmodule
