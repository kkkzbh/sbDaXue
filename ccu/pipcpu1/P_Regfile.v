`timescale 1ns / 1ps
// -----------------------------------------------------------------------------
// P_Regfile.v : 32×32-bit general purpose register file.
// -----------------------------------------------------------------------------
module P_Regfile(
    input             clk,
    input             we,       // write enable
    input      [4:0]  raddr1,
    input      [4:0]  raddr2,
    input      [4:0]  waddr,
    input      [31:0] wdata,
    // debug read port
    input      [4:0]  test_addr,
    output     [31:0] test_data,
    output     [31:0] rdata1,
    output     [31:0] rdata2
);
    reg [31:0] rf[0:31];

    // read (async)
    assign rdata1 = (raddr1 == 5'd0) ? 32'd0 : rf[raddr1];
    assign rdata2 = (raddr2 == 5'd0) ? 32'd0 : rf[raddr2];
    // debug read
    assign test_data = (test_addr == 5'd0) ? 32'd0 : rf[test_addr];

    // write (sync)
    always @(posedge clk) begin
        if (we && (waddr != 5'd0))
            rf[waddr] <= wdata;
    end
endmodule
