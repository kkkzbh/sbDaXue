`timescale 1ns / 1ps

module DataMemory(
    input clk,
    input wenr,           // 读使能信号
    input wenw,           // 写使能信号
    input DBDataSrc,      // 写回数据源选择信号 (0: ALU结果, 1: 存储器数据)
    input [31:0] DAddr,   // 地址输入 (来自ALU结果)
    input [31:0] DataIn,  // 待写入的数据 (来自寄存器rt)
    output reg[31:0] DataOut, // 从存储器读出的数据
    output reg[31:0] DB,      // 写回总线的数据
    input [31:0] test_addr,   // 板上测试用地址
    output reg[31:0] test_data // 板上测试用数据输出
    );
    initial begin
        DB <= 32'h0;
    end

    // 定义一个256x32位的数据存储器 (RAM)
    reg[31:0]ram[255:0];
    integer i;
    // 初始化RAM，将前32个单元清零
    initial begin
    for(i=0;i<=31;i=i+1)
        begin
        ram[i]=0;
        end
    end

    // 读操作 和 写回数据选择 (组合逻辑)
    always@(*)
    begin
        // 读操作: 当读使能(wenr)为1时，根据DAddr从ram中读取数据，否则输出高阻态
        DataOut[31:0] = wenr ? ram[DAddr] : 32'bz; // z 为高阻态

        // 写回数据选择: 根据DBDataSrc信号选择写回的数据源
        // 0: 选择ALU的计算结果 (此时DAddr端口传入的是ALU结果)
        // 1: 选择从数据存储器读出的数据 (DataOut)
        DB = (DBDataSrc == 0) ? DAddr : DataOut;
    end

    // 测试端口逻辑 (组合逻辑)
    always@(*)
    begin
        // 将测试地址test_addr对应的数据输出到test_data
        test_data[31:0] = ram[test_addr];
    end

    // 写操作 (同步时序逻辑)
    always@(posedge clk)
    begin   
        // 在时钟上升沿，当写使能(wenw)为1时，执行写操作
        if(wenw)
            begin
                ram[DAddr] = DataIn[31:0];    
            end
        //$display("mwr: %d $12 %d %d %d %d", mWR, ram[12], ram[13], ram[14], ram[15]);
    end
endmodule
