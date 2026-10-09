`timescale 1ns / 1ps  // 定义仿真时间尺度：时间单位为1纳秒，精度为1皮秒

module adder (  // 定义一个名为"adder"的模块（相当于其他编程语言中的函数或类）
    input  [31:0] operand1,  // 定义第一个32位输入操作数
    input  [31:0] operand2,  // 定义第二个32位输入操作数
    input         cin,       // 定义进位输入，1位
    output [31:0] result,    // 定义32位输出结果
    output        cout       // 定义进位输出，1位
);

// 将两个操作数和进位输入相加，结果的最高位为进位输出，其余32位为结果
assign { cout, result } = operand1 + operand2 + cin;

endmodule  // 模块定义结束