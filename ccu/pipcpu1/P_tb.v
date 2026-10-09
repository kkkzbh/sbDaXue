`timescale 1ns / 1ps
// -----------------------------------------------------------------------------
// P_tb.v : Simple simulation test-bench for P_PipelineCPU.  It resets the core,
// runs a fixed number of cycles, then prints data memory words 0-31 which the
// supplied code.mem self-test populates with expected results.
// -----------------------------------------------------------------------------

module P_tb;
    reg  clk = 0;
    reg  rst = 1;

    // debug probe signals
    reg  [31:0] test_data_addr = 32'd0;
    reg  [4:0]  test_reg_addr  = 5'd0;
    wire [31:0] test_data_out;
    wire [31:0] test_reg_out;

    // clock generator : 10-ns period (100 MHz)
    always #5 clk = ~clk;

    // DUT
    P_PipelineCPU uut(
        .clk(clk),
        .rst(rst),
        .test_data_addr(test_data_addr),
        .test_reg_addr(test_reg_addr),
        .test_data_out(test_data_out),
        .test_reg_out(test_reg_out)
    );

    // simulation sequence
    integer idx;
    initial begin
        // hold reset for a few cycles
        #20 rst = 0;

        // run for enough cycles to finish program
        #15000; // 增加模拟时间，确保所有指令执行完成

        // probe memory/registers after execution for waveform
        $display("\n======= Memory and Register State After Execution =======");
        for (idx = 0; idx < 32; idx = idx + 1) begin
            test_data_addr = idx * 4;
            test_reg_addr  = idx[4:0];
            #20; // wait few cycles for signal to settle in waveform
            
            // 显示寄存器和对应的内存值
            $display("Reg[%0d] = 0x%08x, MEM[%0d] = 0x%08x", 
                     idx, uut.u_rf.rf[idx], idx, uut.u_dmem.ram[idx]);
        end

        // dump first 32 words of data memory with更详细的信息
        $display("\n======= Memory Dump with Expected Values =======");
        for (idx = 0; idx < 32; idx = idx + 1) begin
            $display("MEM[%0d] = 0x%08x (expected according to code.mem)", 
                     idx, uut.u_dmem.ram[idx]);
        end
        $finish;
    end
endmodule
