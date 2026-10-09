`timescale 1ns / 1ps
//
// tb_mcpu.v: 多周期 CPU 的 Testbench
//
module tb_mcpu;
    reg clk;
    reg rst;
    reg  [31:0] test_data_addr;
    wire [31:0] test_data_out;
    reg  [4:0]  test_reg_addr;
    wire [31:0] test_reg_out;

    MultiCycleCPU dut(
        .clk(clk),
        .rst(rst),
        .test_data_addr(test_data_addr),
        .test_reg_addr(test_reg_addr),
        .test_data_out(test_data_out),
        .test_reg_out(test_reg_out)
    );

    // 时钟生成
    initial clk = 0;
    always #5 clk = ~clk;

    // 测试流程
    initial begin
        rst = 1;
        test_data_addr = 0;
        test_reg_addr = 0;
        #20;
        rst = 0;

        // 等待足够长的时间让 CPU 执行完测试程序
        // instructionMemory.v 中的程序较短，2us 足够
        #2000;
        
        $display("-------------------------------------------");
        $display("Multi-Cycle CPU Simulation Result");
        $display("-------------------------------------------");
        
        // 检查关键内存地址的值
        test_data_addr = 11; #1;
        $display("MEM[11] = %d (expected 1)", test_data_out);
        if (test_data_out !== 1) $display("Error: MEM[11] check FAILED!");

        test_data_addr = 12; #1;
        $display("MEM[12] = %d (expected 0)", test_data_out);
        if (test_data_out !== 0) $display("Error: MEM[12] check FAILED!");

        test_data_addr = 13; #1;
        $display("MEM[13] = %d (expected 0)", test_data_out);
        if (test_data_out !== 0) $display("Error: MEM[13] check FAILED!");

        test_data_addr = 14; #1;
        $display("MEM[14] = %d (expected 0)", test_data_out);
        if (test_data_out !== 0) $display("Error: MEM[14] check FAILED!");

        $display("-------------------------------------------");
        
        #100;
        $finish;
    end
endmodule 