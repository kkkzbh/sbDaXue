`timescale 1ns / 1ps
// Testbench for MultiCycleCPU with 32-instruction support.
// Place your program in code.mem (hex, word per line).
module tb_multicycle32;
    reg clk = 0;
    reg rst = 1;

    // debug ports
    reg  [31:0] data_addr = 32'd0;
    reg  [4:0]  reg_addr  = 5'd0;
    wire [31:0] data_out;
    wire [31:0] reg_out;

    // DUT
    MultiCycleCPU dut(
        .clk(clk), .rst(rst),
        .test_data_addr(data_addr),
        .test_reg_addr(reg_addr),
        .test_data_out(data_out),
        .test_reg_out(reg_out)
    );

    // Clock generation
    always #5 clk = ~clk; // 100 MHz

    integer cycle;
    integer idx;
    initial begin
        $dumpfile("wave.vcd");
        $dumpvars(0, tb_multicycle32);

        // Release reset after a few cycles
        #20 rst = 0;

        #1000;

        // Run for 500 cycles then finish
        for (cycle = 0; cycle < 500; cycle = cycle + 1) begin
            @(negedge clk);
            // 打印 PC 与控制器当前状态
            $display("cycle=%0d pc=%h state=%0d", cycle, dut.pc, dut.u_control.current_state);
            if (cycle % 10 == 0)
                reg_addr = (reg_addr + 5'd1) % 32;   // 轮询 R0–R31
            if (cycle % 10 == 0)
                data_addr = (data_addr + 5'd4) % (32 << 2); // 轮询 D0–D31
        end

        // Optional: display some registers / memory
        $display("$t0 = %h", dut.u_regfile.registers[8]);
        $display("$t1 = %h", dut.u_regfile.registers[9]);
        $display("$t2 = %h", dut.u_regfile.registers[10]);

        // Dump MEM[0..31] (word addresses) after program completes
        for (idx = 0; idx < 32; idx = idx + 1) begin
            $display("MEM[%0d] = %h", idx, dut.u_dmem.ram[idx*4]);
        end

        $finish;
    end
endmodule
