`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/11/23 09:48:21
// Design Name: 
// Module Name: ControlUnit
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
//////////////////////////////////////////////////////////////////////////////////


module ControlUnit(
    input [5:0] opCode,
    input zero,
    input [5:0] Func,
    output reg PCWre,//=1,PC�ɱ�
    output reg AluSrcA,
    output reg AluSrcB,    
    output reg DBDataSrc,//���ݱ����ѡ��ˣ�Ϊ0����ALU�������������Ϊ1�������ݼĴ�����Data MEM�������  
    output reg RegWre,
    
    output reg mRD,//���ݴ洢���Ķ�ʹ��
    output reg mWR,//���ݴ洢����дʹ��
    output reg ExtSel,//��������չ
    output reg RegDst,//д�Ĵ�����Ĵ����ĵ�ַ��Ϊ0��ʱ���ַ����rt��Ϊ1��ʱ���ַ����rd
    output reg [1:0]PCSrc,//����PC��
    output reg [3:0]Alu_Op
    );
   initial begin
        PCWre=1;
         mRD=0;
         mWR=0;
         DBDataSrc=0;
   end
   always@(*)
   begin
       PCWre = (opCode == 6'b111111) ? 0 : 1;   //halt
        mWR = (opCode == 6'b101011) ? 1 : 0;     //д�洢��ʹ�ܣ�sw,�Ĵ���->�洢��
        mRD = (opCode == 6'b100011) ? 1 : 0;     //��ʹ�ܣ�lw�洢��->�Ĵ���
        DBDataSrc = (opCode == 6'b100011) ? 1 : 0;
        if(opCode==6'b000000&&Func==6'b100001)//ADDU 1
        begin
             ExtSel = 0;
             RegDst = 1;
             RegWre = 1;
             AluSrcA = 0;
             AluSrcB = 0;
             PCSrc = 2'b00;
             Alu_Op = 4'b0001;
        end
        else if(opCode==6'b000000&&Func==6'b100011)//SUBU 2
        begin
            ExtSel = 0;
             RegDst = 1;
             RegWre = 1;
             AluSrcA = 0;
             AluSrcB = 0;
             PCSrc = 2'b00;
             Alu_Op = 4'b0010;
        end
        else if(opCode==6'b000000&&Func==6'b101010)//SLT 3
        begin
             ExtSel = 0;
             RegDst = 1;
             RegWre = 1;
             AluSrcA = 0;
             AluSrcB = 0;
             PCSrc = 2'b00;
             Alu_Op = 4'b0011;
        end
        else if(opCode==6'b000000&&Func==6'b100100)//AND 4
        begin
             ExtSel = 0;
             RegDst = 1;
             RegWre = 1;
             AluSrcA = 0;
             AluSrcB = 0;
             PCSrc = 2'b00;
             Alu_Op = 4'b0100;
        end
        else if(opCode==6'b000000&&Func==6'b100111)//NOR 5
        begin
             ExtSel = 0;
             RegDst = 1;
             RegWre = 1;
             AluSrcA = 0;
             AluSrcB = 0;
             PCSrc = 2'b00;
             Alu_Op = 4'b0101;
        end
        else if(opCode==6'b000000&&Func==6'b100101)//OR 6
        begin
            ExtSel = 0;
             RegDst = 1;
             RegWre = 1;
             AluSrcA = 0;
             AluSrcB = 0;
             PCSrc = 2'b00;
             Alu_Op = 4'b0110;
        end
        else if(opCode==6'b000000&&Func==6'b100110)//XOR 7
        begin
             ExtSel = 0;
             RegDst = 1;
             RegWre = 1;
             AluSrcA = 0;
             AluSrcB = 0;
             PCSrc = 2'b00;
             Alu_Op = 4'b0111;
        end
        else if(opCode==6'b000000&&Func==6'b000000)//SLL 8
        begin
             ExtSel = 0;
             RegDst = 1;
             RegWre = 1;
             AluSrcA = 1;
             AluSrcB = 0;
             PCSrc = 2'b00;
             Alu_Op = 4'b1000;
        end
        else if(opCode==6'b000000&&Func==6'b000010)//SRL 9
        begin
             ExtSel = 0;
             RegDst = 1;
             RegWre = 1;
             AluSrcA = 1;
             AluSrcB = 0;
             PCSrc = 2'b00;
             Alu_Op = 4'b1001;
        end
        else if(opCode==6'b001001)//ADDIU 10
        begin
             ExtSel = 1;
             RegDst = 0;
             RegWre = 1;
             AluSrcA = 0;
             AluSrcB = 1;
             PCSrc = 2'b00;
             Alu_Op = 4'b0001;

        end
        else if(opCode==6'b000100)//BEQ 11
        begin
             ExtSel = 1;
             RegDst = 0;
             RegWre = 0;
             AluSrcA = 0;
             AluSrcB = 0;
             PCSrc = zero ? 2'b01 : 2'b00;
             Alu_Op = 4'b0010;//�����ж��Ƿ���
        end
        else if(opCode==6'b000101)//BNE 12
        begin
             ExtSel = 1;
             RegDst = 0;
             RegWre = 0;
             AluSrcA = 0;
             AluSrcB = 0;
             PCSrc = zero ? 2'b00 : 2'b01;
             Alu_Op = 4'b0010;//�����ж��Ƿ���
        end
        else if(opCode==6'b100011)//LW���洢�� 13
        begin
             ExtSel = 1;
             RegDst = 0;
             RegWre = 1;
             AluSrcA = 0;
             AluSrcB = 1;
             PCSrc = 2'b00;
             Alu_Op = 4'b0001;
        end
        else if(opCode==6'b101011)//SWд�洢�� 14
        begin
             ExtSel = 1;
             RegDst = 0;
             RegWre = 0;
             AluSrcA = 0;
             AluSrcB = 1;
             PCSrc = 2'b00;
             Alu_Op = 4'b0001;
        end
        else if(opCode==6'b000010)//J��ֱ����ת 15
        begin
            ExtSel=0;
            RegDst=0;
            RegWre=0;
            AluSrcA=0;
            AluSrcB=0;
            PCSrc=2'b10;
            Alu_Op=0;
        end
        else if(opCode==6'b001010)//SLTI指令
        begin
             ExtSel = 1;         // 符号扩展立即数
             RegDst = 0;         // 目标寄存器是rt
             RegWre = 1;         // 需要写寄存器
             AluSrcA = 0;        // ALU操作数A是寄存器rs
             AluSrcB = 1;        // ALU操作数B是立即数
             PCSrc = 2'b00;      // PC+4
             Alu_Op = 4'b0011;   // 使用和SLT相同的ALU操作（比较操作）
        end
        else
        begin
            ExtSel=0;
            RegDst=0;
            RegWre=0;
            AluSrcA=0;
            AluSrcB=0;
            PCSrc=2'b11;
            Alu_Op=0;
        end
        

   end
endmodule
