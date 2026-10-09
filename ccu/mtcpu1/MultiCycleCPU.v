`timescale 1ns / 1ps
//
// MultiCycleCPU.v: 多周期 CPU 顶层数据通路 (最终版)
//
module MultiCycleCPU(
    input clk,
    input rst,

    // 调试端口
    input  [31:0] test_data_addr,
    input  [4:0]  test_reg_addr,
    output [31:0] test_data_out,
    output [31:0] test_reg_out
);

    // ---------------------------- 控制信号 ----------------------------
    wire PCWrite, PCWriteCond, IorD, MemRead, MemWrite, MemToReg, IRWrite, RegWrite;
    wire [1:0] RegDst, PCSource, ALUSrcB;
    wire       ALUSrcA;
    wire [3:0] ALUOp;

    // ---------------------------- 数据通路内部连线 -------------------
    wire zero;
    wire [31:0] instruction, mem_out_data, alu_result;
    wire [31:0] reg_file_rdata1, reg_file_rdata2;

    // 中间寄存器
    reg [31:0] pc;
    reg [31:0] instruction_reg; // IR
    reg [31:0] mem_data_reg;    // MDR
    reg [31:0] reg_a, reg_b;    // A, B
    reg [31:0] alu_out_reg;     // ALUOut

    // ------------------------- 模块实例化 ----------------------------

    M_ControlUnit u_control(
        .clk(clk), .rst(rst),
        .opCode(instruction_reg[31:26]), .funct(instruction_reg[5:0]),
        .zero(zero),
        .PCWrite(PCWrite), .PCWriteCond(PCWriteCond), .IorD(IorD), 
        .MemRead(MemRead), .MemWrite(MemWrite), .MemToReg(MemToReg),
        .IRWrite(IRWrite), .RegWrite(RegWrite), .RegDst(RegDst),
        .PCSource(PCSource), .ALUSrcB(ALUSrcB), .ALUSrcA(ALUSrcA), .ALUOp(ALUOp)
    );

    // Use only lower 10 bits (word address) to match instruction memory port width
    M_InstructionMemory u_imem( .addr(pc[11:2]), .instruction(instruction) );
    
    M_DataMemory u_dmem(
        .clk(clk), .wenr(MemRead & IorD), .wenw(MemWrite),
        .DAddr(alu_out_reg), .DataIn(reg_b), .DataOut(mem_out_data),
        .test_addr(test_data_addr), .test_data(test_data_out)
    );
    
    wire [4:0] waddr_mux_out = (RegDst == 2'b10) ? 5'd31 :
                                (RegDst == 2'b01) ? instruction_reg[15:11] : instruction_reg[20:16];
    wire [31:0] wdata_mux_out = MemToReg ? mem_data_reg : alu_out_reg;
    M_regfile u_regfile(
        .clk(clk), .RegWre(RegWrite),
        .raddr1(instruction_reg[25:21]), .raddr2(instruction_reg[20:16]),
        .waddr(waddr_mux_out), .wdata(wdata_mux_out),
        .rdata1(reg_file_rdata1), .rdata2(reg_file_rdata2),
        .test_addr(test_reg_addr), .test_data(test_reg_out)
    );

    wire [31:0] alu_b_mux_out = (ALUSrcB == 2'b11) ? {27'd0, instruction_reg[10:6]} :
                              (ALUSrcB == 2'b10) ? {{16{instruction_reg[15]}}, instruction_reg[15:0]} :
                              (ALUSrcB == 2'b01) ? 32'd4 :
                              reg_b;
    M_Alu u_alu(
        .A(ALUSrcA ? reg_a : pc),
        .B( (PCSource == 2'b01) ? ({{14{instruction_reg[15]}}, instruction_reg[15:0], 2'b00}) : alu_b_mux_out ),
        .Alu_Op(ALUOp), .zero(zero), .Alu_Result(alu_result)
    );

    // ------------------------- PC 和中间寄存器更新 (时序) --------------
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            pc <= 32'h00000000;
            instruction_reg <= 32'd0;
            mem_data_reg <= 32'd0;
            reg_a <= 32'd0;
            reg_b <= 32'd0;
            alu_out_reg <= 32'd0;
        end else begin
            if (PCWrite) begin
                case(PCSource)
                    2'b10: pc <= {pc[31:28], instruction_reg[25:0], 2'b00}; // J & JAL
                    2'b11: pc <= reg_a; // JR
                    default: pc <= alu_result; // PC+4 or ALU result
                endcase
            end else if (PCWriteCond) begin // BEQ/BNE
                pc <= alu_result;
            end

            if (IRWrite)
                instruction_reg <= instruction;

            reg_a <= reg_file_rdata1;
            reg_b <= reg_file_rdata2;
            alu_out_reg <= alu_result;
            mem_data_reg <= mem_out_data;
        end
    end
endmodule 