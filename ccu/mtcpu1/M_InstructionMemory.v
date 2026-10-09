`timescale 1ns / 1ps
// Simple read-only instruction memory for MultiCycleCPU
// Address input is word-addressed (already >>2 in top module)
// The memory is initialised from "code.mem" in hex format.
// You may generate code.mem with an assembler or hand-crafted values.
module M_InstructionMemory(
    input  [9:0]  addr,        // 1024 words max (4 KB)
    output [31:0] instruction
);
    reg [31:0] rom [0:1023];

    initial begin
        // If file not found, memory will be X on most simulators.
        // Each line in code.mem should contain one 32-bit hex value.
        $readmemh("code.mem", rom);
    end

    assign instruction = rom[addr];
endmodule
