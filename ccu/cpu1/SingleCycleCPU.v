`timescale 1ns / 1ps

module SingleCycleCPU(
        input clk,Reset,
        input [31:0]test_addr,//ȡ�洢��
        input [4:0]test_addr1,//ȡ�Ĵ���
        output [31:0] test_data,
        output [31:0]test_data1
       
        
    );
     wire [31:0] instruction;
     wire [31:0]sort;
     wire [31:0] addr;
     wire [1:0]PCSrc;
     wire zero;
     wire [31:0]Out1;
     wire [31:0]Out2;
     wire [4:0]rs;
     wire [4:0]rt;
        
    wire [5:0] opCode;
    wire [31:0] Result;
    wire [4:0] rd;
    wire Extsel, Alu_SrcA, Alu_SrcB;
    wire RD,WR;
    wire [5:0]Func;
    wire PCWre;

    wire [31:0]extendImm;
    
    wire[3:0] Alu_Op;
    wire[31:0] DataOut,DB;
    wire[15:0] Imm;
    wire[4:0] sa;
    wire DBDataSrc, RegWre,RegDst;

    
    assign sort=(opCode==6'b111111)?32'd1:32'd0;
    PC ins(
       .clk(clk),
       .Reset(Reset),
       .PCWre(PCWre),
       .PCSrc(PCSrc),
       .Imm(extendImm),
       .addr(addr),
       .instruction(instruction)
    );
   instructionMemory ins1(
       .addr({2'b0,addr[31:2]}),   
       .opCode(opCode),   
       .rs(rs), 
       .rt(rt),
       .rd(rd),
       .immediate(Imm),
       .sa(sa),
       .Func(Func),
       .instruction(instruction)
    );
    regfile ins2(
       .clk(clk),
       .RegWre(RegWre),//дʹ��
       .raddr1(rs),//������
       .raddr2(rt),
       .rdata1(Out1),
       .rdata2(Out2),
       .waddr(RegDst ? rd : rt),//д����
       .wdata(DB),//DB��ALU���߼Ĵ������ó�����
       .test_addr(test_addr1),
       .test_data(test_data1)
    );
    Alu ins3(
       .Alu_SrcA(Alu_SrcA),
       .Alu_SrcB(Alu_SrcB),
       .ReadData1(Out1),//������1
       .ReadData2(Out2),//������2
       .sa(sa),
       .extend(extendImm),
       .Alu_Op(Alu_Op),//����
       .zero(zero),
       .Alu_Result(Result)//���
    );
    SignZeroExtend ins4(
    .Imm(Imm),//l��ָ���16λ������������չ��1.����չ ��16Ϊ0��2.������չ
    .Extsel(Extsel),//״̬'0',0��չ���������λ��չ
    .extendImm(extendImm)
    );
    DataMemory ins5(
        .clk(clk),
        .wenr(RD),//��ʹ��
        .wenw(WR),//дʹ��
        .DBDataSrc(DBDataSrc),//MemtoReg���ݱ����ѡ��ˣ�Ϊ0����ALU�������������Ϊ1�������ݼĴ�����Data MEM������� 
        .DAddr(Result),//��ΪLWָ����DAddr=aluResult
        .DataIn(Out2),
        .DataOut(DataOut),
        .DB(DB),
        .test_addr(test_addr),
        .test_data(test_data)
    );
    ControlUnit ins6(
        .opCode(opCode),
        .zero(zero),
        .Func(Func),
        .PCWre(PCWre),//=1,PC�ɱ�
        .AluSrcA(Alu_SrcA),
        .AluSrcB(Alu_SrcB),    
        .DBDataSrc(DBDataSrc),//���ݱ����ѡ��ˣ�Ϊ0����ALU�������������Ϊ1�������ݼĴ�����Data MEM�������  
        .RegWre(RegWre), 
        .mRD(RD),//���ݴ洢���Ķ�ʹ��
        .mWR(WR),//���ݴ洢����дʹ��
        .ExtSel(Extsel),//��������չ
        .RegDst(RegDst),//д�Ĵ�����Ĵ����ĵ�ַ��Ϊ0��ʱ���ַ����rt��Ϊ1��ʱ���ַ����rd
        .PCSrc(PCSrc),//����PC��
        .Alu_Op(Alu_Op)
    );
    
    
    
endmodule
