`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2021/11/23 12:01:53
// Design Name: 
// Module Name: Alu
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


module Alu(
input Alu_SrcA,
    input Alu_SrcB,
    input [31 :0] ReadData1,//������1
    input [31 :0] ReadData2,//������2
    input [4:0] sa,
    input [31:0] extend,
    input [3:0] Alu_Op,//����
    output  reg zero,
    output  reg[31 :0] Alu_Result//���
    );
    reg [31:0] Alu_Src1;
    reg [31:0] Alu_Src2;
    always@(*)
    begin
        Alu_Src1 = (Alu_SrcA == 0) ? ReadData1 : sa;
        Alu_Src2 = (Alu_SrcB == 0) ? ReadData2 : extend;
        //λ�����и����Բ�����ʽ�μ�
        if(Alu_Op==4'b0001)//�޷��żӷ� 
            Alu_Result<=Alu_Src1+Alu_Src2;
        else if(Alu_Op==4'b0010)//�޷��ż���
            Alu_Result<=Alu_Src1-Alu_Src2;
        else if(Alu_Op==4'b0011)//�з��űȽ�,С����λ1
            Alu_Result<=(((Alu_Src1 < Alu_Src2) && (Alu_Src1[31] == Alu_Src2[31] )) ||( ( Alu_Src1[31] ==1 && Alu_Src2[31] == 0))) ? 1:0;
        else if(Alu_Op==4'b0100)//λ
            Alu_Result<=Alu_Src1&Alu_Src2;
        else if(Alu_Op==4'b0101)//λ
            Alu_Result<=~(Alu_Src1|Alu_Src2);
        else if(Alu_Op==4'b0110)//λ
            Alu_Result<=(Alu_Src1|Alu_Src2);
        else if(Alu_Op==4'b0111)//λ
            Alu_Result<=(Alu_Src1^Alu_Src2);
        else if(Alu_Op==4'b1000)//߼
            Alu_Result<=Alu_Src2<<Alu_Src1;
        else if(Alu_Op==4'b1001)//߼
            Alu_Result<=Alu_Src2>>Alu_Src1;
        else Alu_Result<=31'b0;    
           zero=(Alu_Result==0)?1:0;
    end
    
    
    
endmodule

