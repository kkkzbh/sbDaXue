`timescale 1ns / 1ps
// -----------------------------------------------------------------------------
// P_PipelineCPU.v : Minimal 5-stage in-order pipeline that can run the supplied
// code.mem regression program.  It purposefully supports only a subset of MIPS
// instructions sufficient for that program.
//
// This is a corrected and refactored version with a standard forwarding
// and hazard detection mechanism.
// -----------------------------------------------------------------------------

module P_PipelineCPU(
    input  clk,
    input  rst,
    // debug ports for memory/register display
    input  [31:0] test_data_addr,
    input  [4:0]  test_reg_addr,
    output [31:0] test_data_out,
    output [31:0] test_reg_out
);
    // =============================================================
    // Pipeline Registers & Forwarding Signals
    // =============================================================
    // IF/ID Stage
    reg [31:0] id_pc;
    reg [31:0] id_inst;

    // ID/EX Stage
    reg [31:0] exe_pc;
    reg [31:0] exe_inst;
    reg [31:0] exe_op1, exe_op2;
    reg [4:0]  exe_rs, exe_rt, exe_dest;
    reg        exe_reg_write, exe_mem_write, exe_mem_read;
    reg [3:0]  exe_alu_ctrl;
    reg [1:0]  exe_alu_src2_sel;

    // EX/MEM Stage
    reg [31:0] mem_pc;
    reg [31:0] mem_inst;
    reg [31:0] mem_alu_result;
    reg [31:0] mem_store_data;
    reg [4:0]  mem_dest;
    reg        mem_reg_write, mem_mem_write, mem_mem_read;

    // MEM/WB Stage
    reg [31:0] wb_inst;
    reg [31:0] wb_alu_result;
    reg [31:0] wb_mem_rdata;
    reg [4:0]  wb_dest;
    reg        wb_reg_write;

    // Final write-back data
    wire [31:0] wb_wdata;

    // Hazard Detection
    wire       load_use_hazard;
    wire       flush_ifid;

    // =============================================================
    // Stage 0 : PC register & next-PC selection
    // =============================================================
    reg [31:0] pc;
    wire [31:0] pc_next;
    wire [31:0] pc_plus4;

    P_adder u_pc_plus4(.a(pc), .b(32'd4), .y(pc_plus4));

    always @(posedge clk or posedge rst) begin
        if (rst)
            pc <= 32'd0;
        else if (!load_use_hazard) // Stall PC on load-use hazard
            pc <= pc_next;
    end

    // =============================================================
    // Stage 1 : Instruction fetch (IF)
    // =============================================================
    wire [31:0] if_inst;
    P_InstructionMemory u_imem(.clk(clk), .addr(pc), .inst(if_inst));

    // =============================================================
    // Stage 1 IF/ID pipeline register update with stall/flush support
    // =============================================================
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            id_pc   <= 32'd0;
            id_inst <= 32'd0;
        end else if (flush_ifid) begin
            id_inst <= 32'd0; // Flush (nop)
            id_pc   <= 32'd0;
        end else if (!load_use_hazard) begin
            id_pc   <= pc;
            id_inst <= if_inst;
        end // else : hold IF/ID when hazard (stall)
    end

    // =============================================================
    // Stage 2 : Instruction decode (ID)
    // =============================================================
    wire [5:0] op      = id_inst[31:26];
    wire [4:0] rs      = id_inst[25:21];
    wire [4:0] rt      = id_inst[20:16];
    wire [4:0] rd      = id_inst[15:11];
    wire [5:0] funct   = id_inst[5:0];
    wire [15:0] imm16  = id_inst[15:0];
    wire [25:0] jidx   = id_inst[25:0];

    // Register File
    wire [31:0] rs_val, rt_val;
    P_Regfile u_rf(
        .clk(clk),
        .we(wb_reg_write),
        .raddr1(rs),
        .raddr2(rt),
        .waddr(wb_dest),
        .wdata(wb_wdata),
        .test_addr(test_reg_addr),
        .test_data(test_reg_out),
        .rdata1(rs_val),
        .rdata2(rt_val)
    );

    // Control signal generation
    reg        id_reg_write, id_mem_write, id_mem_read;
    reg [3:0]  id_alu_ctrl;
    reg [1:0]  id_alu_src2_sel; // 0:rt, 1:imm_se, 2:imm_ze, 3:shamt
    reg [4:0]  id_dest_reg;
    reg        id_is_branch, id_branch_taken, id_is_jump;
    reg [31:0] id_branch_target, id_jump_target;

    wire is_var_shift = (op == 6'b000000) && (funct == 6'h04 || funct == 6'h06 || funct == 6'h07);

    always @(*) begin
        // defaults
        id_is_branch      = 1'b0; id_branch_taken   = 1'b0; id_branch_target  = 32'd0;
        id_is_jump        = 1'b0; id_jump_target    = 32'd0;
        id_reg_write      = 1'b0; id_mem_write      = 1'b0; id_mem_read       = 1'b0;
        id_alu_ctrl       = 4'hF; // Default to an invalid ALU op
        id_alu_src2_sel   = 2'd0;
        id_dest_reg       = rd;

        case (op)
            6'b000000: begin // R-type
                id_reg_write = 1'b1;
                case (funct)
                    6'h20,6'h21: id_alu_ctrl = 4'b0000; // add/addu
                    6'h22,6'h23: id_alu_ctrl = 4'b0001; // sub/subu
                    6'h2a:       id_alu_ctrl = 4'b0010; // slt
                    6'h2b:       id_alu_ctrl = 4'b0011; // sltu
                    6'h24:       id_alu_ctrl = 4'b0100; // and
                    6'h25:       id_alu_ctrl = 4'b0101; // or
                    6'h26:       id_alu_ctrl = 4'b0110; // xor
                    6'h27:       id_alu_ctrl = 4'b0111; // nor
                    6'h00:       begin id_alu_ctrl = 4'b1000; id_alu_src2_sel = 2'd3; end // sll
                    6'h02:       begin id_alu_ctrl = 4'b1001; id_alu_src2_sel = 2'd3; end // srl
                    6'h03:       begin id_alu_ctrl = 4'b1010; id_alu_src2_sel = 2'd3; end // sra
                    6'h04:       id_alu_ctrl = 4'b1000; // sllv
                    6'h06:       id_alu_ctrl = 4'b1001; // srlv
                    6'h07:       id_alu_ctrl = 4'b1010; // srav
                    default:     id_reg_write = 1'b0;
                endcase
            end
            6'b001000,6'b001001: begin id_reg_write=1; id_alu_ctrl=4'b0000; id_alu_src2_sel=1; id_dest_reg=rt; end //addi/u
            6'b001100: begin id_reg_write=1; id_alu_ctrl=4'b0100; id_alu_src2_sel=2; id_dest_reg=rt; end //andi
            6'b001101: begin id_reg_write=1; id_alu_ctrl=4'b0101; id_alu_src2_sel=2; id_dest_reg=rt; end //ori
            6'b001110: begin id_reg_write=1; id_alu_ctrl=4'b0110; id_alu_src2_sel=2; id_dest_reg=rt; end //xori
            6'b001111: begin id_reg_write=1; id_alu_ctrl=4'b1011; id_alu_src2_sel=2; id_dest_reg=rt; end //lui
            6'b100011: begin id_mem_read=1; id_reg_write=1; id_alu_ctrl=4'b0000; id_alu_src2_sel=1; id_dest_reg=rt; end //lw
            6'b101011: begin id_mem_write=1; id_alu_ctrl=4'b0000; id_alu_src2_sel=1; end //sw
            6'b000100: begin id_is_branch=1; id_branch_taken=(rs_val==rt_val); id_branch_target=id_pc+4+({{16{imm16[15]}}, imm16}<<2); end //beq
            6'b000101: begin id_is_branch=1; id_branch_taken=(rs_val!=rt_val); id_branch_target=id_pc+4+({{16{imm16[15]}}, imm16}<<2); end //bne
            6'b000010: begin id_is_jump=1; id_jump_target={id_pc[31:28], jidx, 2'b00}; end //j
            6'b000011: begin id_is_jump=1; id_reg_write=1; id_jump_target={id_pc[31:28], jidx, 2'b00}; id_dest_reg=31; end //jal
            default: ;
        endcase
    end

    // Hazard Detection: stall for one cycle if ID is trying to use a register
    // that the instruction in EX is loading into.
    assign load_use_hazard = exe_mem_read && exe_reg_write && (exe_dest == rs || exe_dest == rt);

    // Branch/Jump Logic
    assign flush_ifid = (id_is_branch & id_branch_taken) | id_is_jump;
    assign pc_next = (id_is_branch & id_branch_taken) ? id_branch_target :
                     id_is_jump                      ? id_jump_target   :
                     pc_plus4;

    // ID/EX pipeline regs
    always @(posedge clk or posedge rst) begin
        if (rst || flush_ifid) begin
            exe_pc <= 0; exe_inst <= 0; exe_op1 <= 0; exe_op2 <= 0;
            exe_alu_ctrl <= 0; exe_reg_write <= 0; exe_mem_write <= 0; exe_mem_read <= 0;
            exe_dest <= 0; exe_rs <= 0; exe_rt <= 0; exe_alu_src2_sel <= 0;
        end else if (!load_use_hazard) begin
            exe_pc <= id_pc;
            exe_inst <= id_inst;
            exe_op1 <= (is_var_shift) ? rt_val : rs_val; // For variable shifts, op1 is rt
            exe_op2 <= (is_var_shift) ? rs_val : rt_val; // For variable shifts, op2 is rs
            exe_rs <= rs;
            exe_rt <= rt;
            exe_dest <= id_dest_reg;
            exe_reg_write <= id_reg_write;
            exe_mem_write <= id_mem_write;
            exe_mem_read  <= id_mem_read;
            exe_alu_ctrl <= id_alu_ctrl;
            exe_alu_src2_sel <= id_alu_src2_sel;
        end else begin // Stall, insert NOP
             exe_pc <= 0; exe_inst <= 0; exe_op1 <= 0; exe_op2 <= 0;
             exe_alu_ctrl <= 0; exe_reg_write <= 0; exe_mem_write <= 0; exe_mem_read <= 0;
             exe_dest <= 0; exe_rs <= 0; exe_rt <= 0; exe_alu_src2_sel <= 0;
        end
    end

    // =============================================================
    // Stage 3 : Execute (EX)
    // =============================================================
    // Forwarding Unit
    wire [31:0] exe_fwd_op1, exe_fwd_op2;
    assign exe_fwd_op1 = (exe_rs != 0 && exe_rs == mem_dest && mem_reg_write) ? mem_alu_result :
                         (exe_rs != 0 && exe_rs == wb_dest  && wb_reg_write)  ? wb_wdata       :
                         exe_op1;

    assign exe_fwd_op2 = (exe_rt != 0 && exe_rt == mem_dest && mem_reg_write) ? mem_alu_result :
                         (exe_rt != 0 && exe_rt == wb_dest  && wb_reg_write)  ? wb_wdata       :
                         exe_op2;

    // ALU operand selection
    wire [31:0] alu_op1, alu_op2;
    wire [31:0] imm_sext_exe = {{16{exe_inst[15]}}, exe_inst[15:0]};
    wire [31:0] imm_zext_exe = {16'd0, exe_inst[15:0]};
    wire [31:0] shamt_exe    = {27'd0, exe_inst[10:6]};
    wire is_var_shift_exe    = (exe_inst[31:26] == 6'b000000) && (exe_inst[5:0] == 6'h04 || exe_inst[5:0] == 6'h06 || exe_inst[5:0] == 6'h07);

    assign alu_op1 = (is_var_shift_exe)           ? exe_fwd_op2 : // shift amount from rs
                     (exe_alu_src2_sel == 2'd3) ? shamt_exe :
                     exe_fwd_op1;

    assign alu_op2 = (exe_alu_src2_sel == 2'd1) ? imm_sext_exe :
                     (exe_alu_src2_sel == 2'd2) ? imm_zext_exe :
                     (is_var_shift_exe)           ? exe_fwd_op1 : // value to shift from rt
                     exe_fwd_op2;

    wire [31:0] alu_result;
    P_alu u_alu(.alu_ctrl(exe_alu_ctrl), .op1(alu_op1), .op2(alu_op2), .result(alu_result));

    // EX/MEM pipeline regs
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            mem_pc <= 0; mem_inst <= 0; mem_alu_result <= 0; mem_store_data <= 0;
            mem_reg_write <= 0; mem_mem_write <= 0; mem_mem_read <= 0; mem_dest <= 0;
        end else begin
            mem_pc <= exe_pc;
            mem_inst <= exe_inst;
            mem_alu_result <= (exe_inst[31:26] == 6'b000011) ? exe_pc + 4 : alu_result; // JAL
            mem_store_data <= exe_fwd_op2;
            mem_reg_write <= exe_reg_write;
            mem_mem_write <= exe_mem_write;
            mem_mem_read  <= exe_mem_read;
            mem_dest <= exe_dest;
        end
    end

    // =============================================================
    // Stage 4 : Memory (MEM)
    // =============================================================
    wire [31:0] mem_rdata;
    P_DataMemory u_dmem(
        .clk(clk),
        .we(mem_mem_write),
        .addr({mem_alu_result[31:2], 2'b00}),
        .wdata(mem_store_data),
        .rdata(mem_rdata),
        .test_addr(test_data_addr),
        .test_data(test_data_out)
    );

    // MEM/WB pipeline regs
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            wb_inst <= 0; wb_alu_result <= 0; wb_mem_rdata <= 0;
            wb_reg_write <= 0; wb_dest <= 0;
        end else begin
            wb_inst <= mem_inst;
            wb_alu_result <= mem_alu_result;
            wb_mem_rdata  <= mem_rdata;
            wb_reg_write <= mem_reg_write;
            wb_dest <= mem_dest;
        end
    end

    // =============================================================
    // Stage 5 : Write-back (WB)
    // =============================================================
    assign wb_wdata = (wb_inst[31:26] == 6'b100011) ? wb_mem_rdata : wb_alu_result; // LW data from memory

endmodule
