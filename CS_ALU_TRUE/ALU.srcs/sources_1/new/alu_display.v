`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/14 15:52:28
// Design Name: 
// Module Name: alu_display
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


module regfile_display(
    //时钟与复位信号
    input clk,
    input resetn,    //后缀"n"表示低电平有效

    //输入开关，用于控制写使能和选择输入数据
    input [6:0] sel,


    //触摸屏相关接口，不需要修改
    output lcd_rst,
    output lcd_cs,
    output lcd_rs,
    output lcd_wr,
    output lcd_rd,
    inout[15:0] lcd_data_io,
    output lcd_bl_ctr,
    inout ct_int,
    inout ct_sda,
    output ct_scl,
    output ct_rstn
);


//-----{调用alu模块}begin
    wire [31:0] alu_src1;
    wire [31:0] alu_src2;
    wire [11:0] alu_control;
    wire [31:0] alu_result;
    wire [1:0]  overflow;    // [1]:有符号溢出 [0]:无符号溢出
    
    alu alu_module(
        .alu_control(alu_control),
        .alu_src1   (alu_src1),
        .alu_src2   (alu_src2),
        .alu_result (alu_result),
        .overflow   (overflow)
    );
       
//-----{调用寄存器堆模块}end

//---------------------{调用触摸屏模块}begin--------------------//
//-----{实例化触摸屏}begin
//此小节不需要修改
    reg         display_valid;
    reg  [39:0] display_name;
    reg  [31:0] display_value;
    wire [5 :0] display_number;
    wire        input_valid;
    wire [31:0] input_value;

    lcd_module lcd_module(
        .clk            (clk           ),   //10Mhz
        .resetn         (resetn        ),

        //调用触摸屏的接口
        .display_valid  (display_valid ),
        .display_name   (display_name  ),
        .display_value  (display_value ),
        .display_number (display_number),
        .input_valid    (input_valid   ),
        .input_value    (input_value   ),

        //lcd触摸屏相关接口，不需要修改
        .lcd_rst        (lcd_rst       ),
        .lcd_cs         (lcd_cs        ),
        .lcd_rs         (lcd_rs        ),
        .lcd_wr         (lcd_wr        ),
        .lcd_rd         (lcd_rd        ),
        .lcd_data_io    (lcd_data_io   ),
        .lcd_bl_ctr     (lcd_bl_ctr    ),
        .ct_int         (ct_int        ),
        .ct_sda         (ct_sda        ),
        .ct_scl         (ct_scl        ),
        .ct_rstn        (ct_rstn       )
    ); 
//-----{实例化触摸屏}end

//-----{从触摸屏获取输入}begin
//根据实际需要输入的数修改此小节，
//建议对每一个数的输入，编写一个always块
    //根据sel的值设置ALU操作数和控制信号
    reg [31:0] reg_alu_src1;
    reg [31:0] reg_alu_src2;
    reg [11:0] reg_alu_control;
    
    assign alu_src1 = reg_alu_src1;
    assign alu_src2 = reg_alu_src2;
    assign alu_control = reg_alu_control;
    
    always @(posedge clk)
    begin
        if (!resetn)
        begin
            reg_alu_src1 <= 32'd0;
            reg_alu_src2 <= 32'd0;
            reg_alu_control <= 12'd0;
        end
        else if (input_valid)
        begin
            case(sel[1:0])
                2'b00: reg_alu_control <= input_value[11:0];
                2'b01: reg_alu_src1 <= input_value;
                2'b10: reg_alu_src2 <= input_value;
                default: ; // 不变
            endcase
        end
    end
//-----{从触摸屏获取输入}end

//-----{输出结果到触摸屏显示}begin
//根据需要显示的数修改此小节，
//触摸屏上共有44块显示区域，可显示44组32位数据
//44块显示区域从1开始编号，编号为1~44
    always @(posedge clk)
    begin
        case(display_number)
            6'd1 :
            begin
                display_valid <= 1'b1;
                display_name  <= "SRC_1";
                display_value <= alu_src1;
            end
            6'd2 :
            begin
                display_valid <= 1'b1;
                display_name  <= "SRC_2";
                display_value <= alu_src2;
            end
            6'd3 :
            begin
                display_valid <= 1'b1;
                display_name  <= "CONTR";
                display_value <={20'd0, alu_control};
            end
            6'd4 :
            begin
                display_valid <= 1'b1;
                display_name  <= "RESUL";
                display_value <= alu_result;
            end
            6'd5 :
            begin
                display_valid <= 1'b1;
                display_name  <= "SFLOW"; // 有符号溢出
                display_value <= {31'd0, overflow[1]};
            end
            6'd6 :
            begin
                display_valid <= 1'b1;
                display_name  <= "UFLOW"; // 无符号溢出
                display_value <= {31'd0, overflow[0]};
            end
            default :
            begin
                display_valid <= 1'b0;
                display_name  <= 40'd0;
                display_value <= 32'd0;
            end
        endcase
    end
//-----{输出结果到触摸屏显示}end
//----------------------{调用触摸屏模块}end---------------------//
endmodule
