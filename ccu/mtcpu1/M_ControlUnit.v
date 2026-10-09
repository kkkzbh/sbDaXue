`timescale 1ns / 1ps
//
// M_ControlUnit.v: 多周期 CPU 的核心控制器 FSM
//
module M_ControlUnit(
    input clk,
    input rst,
    input [5:0] opCode,
    input [5:0] funct,
    input zero,

    // 控制信号输出
    output reg PCWrite,
    output reg PCWriteCond,
    output reg IorD,
    output reg MemRead,
    output reg MemWrite,
    output reg MemToReg,
    output reg IRWrite,
    output reg RegWrite,
    output reg [1:0] RegDst,
    output reg [1:0] PCSource,
    output reg [1:0] ALUSrcB,
    output reg ALUSrcA,
    output reg [3:0] ALUOp
);

    // FSM 状态定义
    parameter S_FETCH       = 4'd0,  // 取指
              S_DECODE      = 4'd1,  // 译码
              S_EXEC_R      = 4'd2,  // R-Type 执行
              S_EXEC_I      = 4'd3,  // I-Type 执行
              S_MEM_ADDR    = 4'd4,  // LW/SW 地址计算
              S_BRANCH      = 4'd5,  // 分支
              S_JUMP        = 4'd6,  // 跳转
              S_MEM_READ    = 4'd7,  // LW 读内存
              S_MEM_WRITE   = 4'd8,  // SW 写内存
              S_WB_ALU      = 4'd9,  // R/I-Type 写回
              S_WB_MEM      = 4'd10; // LW 写回
    
    reg [3:0] current_state, next_state;

    // 状态寄存器 (时序逻辑)
    always @(posedge clk or posedge rst) begin
        if (rst)
            current_state <= S_FETCH;
        else
            current_state <= next_state;
    end

    // 下一状态转移逻辑 (组合逻辑)
    always @(*) begin
        case (current_state)
            S_FETCH:
                next_state = S_DECODE;
            S_DECODE:
                case (opCode)
                    6'b000000: next_state = S_EXEC_R;    // R-type
                    6'b001000: next_state = S_EXEC_I;    // addi
                    6'b001001: next_state = S_EXEC_I;    // addiu
                    6'b001010: next_state = S_EXEC_I;    // slti
                    6'b001011: next_state = S_EXEC_I;    // sltiu
                    6'b001100: next_state = S_EXEC_I;    // andi
                    6'b001101: next_state = S_EXEC_I;    // ori
                    6'b001110: next_state = S_EXEC_I;    // xori
                    6'b001111: next_state = S_EXEC_I;    // lui
                    6'b100000: next_state = S_MEM_ADDR;  // lb
                    6'b100100: next_state = S_MEM_ADDR;  // lbu
                    6'b100011: next_state = S_MEM_ADDR;  // lw
                    6'b101000: next_state = S_MEM_ADDR;  // sb
                    6'b101011: next_state = S_MEM_ADDR;  // sw
                    6'b000100: next_state = S_BRANCH;    // beq
                    6'b000101: next_state = S_BRANCH;    // bne
                    6'b000010: next_state = S_JUMP;      // j
                    6'b000011: next_state = S_JUMP;      // jal
                    default:   next_state = S_FETCH;     // unsupported
                endcase
            S_EXEC_R:       next_state = S_WB_ALU;
            S_EXEC_I:       next_state = S_WB_ALU;
            S_MEM_ADDR:
                if (opCode == 6'b100011) // lw
                    next_state = S_MEM_READ;
                else // sw
                    next_state = S_MEM_WRITE;
            S_BRANCH:       next_state = S_FETCH;
            S_JUMP:         next_state = S_FETCH;
            S_MEM_READ:     next_state = S_WB_MEM;
            S_MEM_WRITE:    next_state = S_FETCH;
            S_WB_ALU:       next_state = S_FETCH;
            S_WB_MEM:       next_state = S_FETCH;
            default:        next_state = S_FETCH;
        endcase
    end
    
    // 控制信号输出逻辑 (组合逻辑)
    always @(*) begin
        // 默认值
        PCWrite=0; PCWriteCond=0; IorD=0; MemRead=0; MemWrite=0;
        MemToReg=0; IRWrite=0; RegWrite=0;
        RegDst=2'b00; PCSource=2'b00; ALUSrcB=2'b01; ALUSrcA=0;
        ALUOp=4'b0000; // NOP

        case(current_state)
            S_FETCH: begin // PC -> I-Mem, PC=PC+4, IR=Mem[PC]
                MemRead = 1; IRWrite = 1; IorD = 0; PCWrite = 1;
                PCSource = 2'b00; ALUSrcA = 0; ALUSrcB = 2'b01; ALUOp = 4'b0001; // PC+4
            end
            S_DECODE: begin // 译码, 读寄存器, 计算分支地址
                ALUSrcA = 0; ALUSrcB = 2'b11; ALUOp = 4'b0001; // PC + sign_ext(imm)*4
            end
            S_EXEC_R: begin // R-type
                ALUSrcA = 1; ALUSrcB = 2'b00;
                case (funct)
                    6'b100000,6'b100001: ALUOp = 4'b0001; // add/addu
                    6'b100010,6'b100011: ALUOp = 4'b0010; // sub/subu
                    6'b100100: ALUOp = 4'b0100; // and
                    6'b100101: ALUOp = 4'b0101; // or
                    6'b100110: ALUOp = 4'b0110; // xor
                    6'b100111: ALUOp = 4'b0111; // nor
                    6'b101010: ALUOp = 4'b0011; // slt
                    6'b101011: ALUOp = 4'b1000; // sltu
                    6'b000000: begin ALUOp = 4'b1001; ALUSrcA = 0; ALUSrcB = 2'b11; end // sll (shamt)
                    6'b000010: begin ALUOp = 4'b1010; ALUSrcA = 0; ALUSrcB = 2'b11; end // srl
                    6'b000011: begin ALUOp = 4'b1011; ALUSrcA = 0; ALUSrcB = 2'b11; end // sra
                    6'b000100: ALUOp = 4'b1001; // sllv (A=regA, B=regB) 默认 ALUSrcA=1
                    6'b000110: ALUOp = 4'b1010; // srlv
                    6'b000111: ALUOp = 4'b1011; // srav
                    6'b001000: begin // jr
                        ALUOp = 4'b0000; // pass-through
                        PCWrite = 1; PCSource = 2'b11; // later datapath will support
                    end
                    default:   ALUOp = 4'b0000;
                endcase
            end
            S_EXEC_I: begin // I-type imm
                ALUSrcA = 1; ALUSrcB = 2'b10;
                case (opCode)
                    6'b001000,6'b001001: ALUOp = 4'b0001; // addi/addiu
                    6'b001010: ALUOp = 4'b0011;           // slti
                    6'b001011: ALUOp = 4'b1000;           // sltiu
                    6'b001100: begin ALUOp = 4'b0100; ALUSrcA = 1; end // andi (zero ext handled in datapath later)
                    6'b001101: begin ALUOp = 4'b0101; ALUSrcA = 1; end // ori
                    6'b001110: begin ALUOp = 4'b0110; ALUSrcA = 1; end // xori
                    6'b001111: begin ALUOp = 4'b1111; ALUSrcA = 0; end  // lui (use imm)
                    default:   ALUOp = 4'b0000;
                endcase
            end
            S_MEM_ADDR: begin // LW/SW: ALUOut = A + imm
                ALUSrcA = 1; ALUSrcB = 2'b10; ALUOp = 4'b0001;
            end
            S_BRANCH: begin // BEQ/BNE: if(A==B) PC=ALUOut
                ALUSrcA = 1; ALUSrcB = 2'b00; ALUOp = 4'b0010; // A-B
                PCSource = 2'b01;
                if (opCode == 6'b000100)      // BEQ
                    PCWriteCond = zero;
                else if (opCode == 6'b000101) // BNE
                    PCWriteCond = ~zero;
            end
            S_JUMP: begin // J: PC = jump_addr
                PCWrite = 1; PCSource = 2'b10;
            end
            S_MEM_READ: begin // LW: MDR = Mem[ALUOut]
                MemRead = 1; IorD = 1;
            end
            S_MEM_WRITE: begin // SW: Mem[ALUOut] = B
                MemWrite = 1; IorD = 1;
            end
            S_WB_ALU: begin // R/I-Type: Reg[rd/rt] = ALUOut
                RegWrite = 1; MemToReg = 0;
                RegDst = (opCode == 6'b000000) ? 2'b01 : 2'b00; // R-type:rd, I-type:rt
            end
            S_WB_MEM: begin // LW: Reg[rt] = MDR
                RegWrite = 1; MemToReg = 1; RegDst = 2'b00;
            end
        endcase
    end
endmodule 