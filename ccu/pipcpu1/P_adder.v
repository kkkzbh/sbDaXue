`timescale 1ns / 1ps
// -----------------------------------------------------------------------------
// P_adder.v : 32-bit adder used for PC + 4 and branch target calculation
// -----------------------------------------------------------------------------
module P_adder(
    input  [31:0] a,
    input  [31:0] b,
    output [31:0] y
);
    assign y = a + b;
endmodule
