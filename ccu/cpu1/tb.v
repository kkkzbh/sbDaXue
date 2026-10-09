`timescale 1ns / 1ps
//
// Company: 
// Engineer: 
// 
// Create Date: 2021/10/05 22:19:41
// Design Name: 
// Module Name: tb
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//


module tb;
    //inputs
    reg clk;
    reg Reset;
    reg [31:0]test_addr;
    wire [31:0]test_data;
    reg [4:0]test_addr1;
    wire [31:0]test_data1;

    // 用于遍历内存地址及循环次数的计数器
    integer loop_cnt;
    integer mem_addr_iter;
    integer reg_addr_iter;
    integer instr_cnt;

    SingleCycleCPU ins(
        .clk(clk),
        .Reset(Reset),
        .test_addr(test_addr),
        .test_data(test_data),
        .test_addr1(test_addr1),
        .test_data1(test_data1)
    );
    
    initial begin
        // 初始状态
        clk = 0;
        Reset = 0;
        test_addr1 = 5'd0;
        test_addr = 32'd0;

        // 释放复位
        #10;
        Reset = 1;
        
        // 执行指令
        // 每条指令需要一个时钟周期
        // 根据instruction memory中的指令数量，至少需要运行42个周期
        for (instr_cnt = 0; instr_cnt < 50; instr_cnt = instr_cnt + 1) begin
            #10; // 等待一个时钟周期
        end
        
        // 打印寄存器内容
        $display("===== 寄存器内容 =====");
        for (reg_addr_iter = 0; reg_addr_iter < 32; reg_addr_iter = reg_addr_iter + 1) begin
            test_addr1 = reg_addr_iter;
            #5; // 等待数据稳定
            $display("寄存器[%0d] = 0x%08h (dec %0d)", reg_addr_iter, test_data1, test_data1);
        end
        
        // 打印内存内容 - 重点关注我们存储结果的内存区域 (16-30)
        $display("===== 内存内容 =====");
        for (mem_addr_iter = 16; mem_addr_iter <= 30; mem_addr_iter = mem_addr_iter + 1) begin
            test_addr = mem_addr_iter;
            #5; // 等待数据稳定
            $display("MEM[%0d] = 0x%08h (dec %0d)", mem_addr_iter, test_data, test_data);
        end
        
        // 验证测试结果
        $display("===== 测试结果验证 =====");
        
        // R型指令测试结果验证
        test_addr = 16; #5; // ADDU结果
        $display("ADDU测试: MEM[16] = %0d (期望值: 12)", test_data);
        
        test_addr = 17; #5; // SUBU结果
        $display("SUBU测试: MEM[17] = %0d (期望值: 2)", test_data);
        
        test_addr = 18; #5; // SLT结果
        $display("SLT测试: MEM[18] = %0d (期望值: 1)", test_data);
        
        test_addr = 19; #5; // AND结果
        $display("AND测试: MEM[19] = %0d (期望值: 5)", test_data);
        
        test_addr = 20; #5; // NOR结果
        $display("NOR测试: MEM[20] = %0d (期望值: -8)", test_data);
        
        test_addr = 21; #5; // OR结果
        $display("OR测试: MEM[21] = %0d (期望值: 7)", test_data);
        
        test_addr = 22; #5; // XOR结果
        $display("XOR测试: MEM[22] = %0d (期望值: 2)", test_data);
        
        test_addr = 23; #5; // SLL结果
        $display("SLL测试: MEM[23] = %0d (期望值: 20)", test_data);
        
        test_addr = 24; #5; // SRL结果
        $display("SRL测试: MEM[24] = %0d (期望值: 3)", test_data);
        
        // I型指令测试结果验证
        test_addr = 25; #5; // ADDIU结果
        $display("ADDIU测试: MEM[25] = %0d (期望值: 100)", test_data);
        
        test_addr = 26; #5; // SLTI结果
        $display("SLTI测试: MEM[26] = %0d (期望值: 1)", test_data);
        
        test_addr = 27; #5; // LW结果
        $display("LW测试: MEM[27] = %0d (期望值: 12)", test_data);
        
        // 分支和跳转指令测试结果验证
        test_addr = 28; #5; // BEQ结果
        $display("BEQ测试: MEM[28] = %0d (期望值: 0)", test_data);
        
        test_addr = 29; #5; // BNE结果
        $display("BNE测试: MEM[29] = %0d (期望值: 0)", test_data);
        
        test_addr = 30; #5; // J结果
        $display("J测试: MEM[30] = %0d (期望值: 5)", test_data);

        // 结束仿真
        #50;
        $finish;
    end
    
    always #5 clk = ~clk;
endmodule

