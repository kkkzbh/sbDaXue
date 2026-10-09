//**************************************************************
//
//> 文件名: adder_display.v
//> 描述 ：加法器显示模块，调用 FPGA 板上的 IO 接口和触摸屏
//> 作者 : LOONGSON
//> 日期 : 2016-04-14
//
//**************************************************************
//
module adder_display(
//时钟与复位信号
input clk,
input resetn, //后缀"n"代表低电平有效

//拨码开关，用于选择输入数和产生 cin
input input_sel, //0:输入为加数 1(add_operand1);1:为加数 2(add_operand2)
input sw_cin,

//led 灯，用于显示 cout
output led_cout,

//触摸屏相关接口，不需要更改
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

//-----{调用加法模块}begin
reg [31:0] adder_operand1;
reg [31:0] adder_operand2;
wire adder_cin;
wire [31:0] adder_result;
wire adder_cout;
adder adder_module(
  .operand1(adder_operand1),
  .operand2(adder_operand2),
  .cin(adder_cin),
  .result(adder_result),
  .cout(adder_cout)
);
assign adder_cin = sw_cin;
assign led_cout = adder_cout;
//-----{调用加法模块}end

//---------------------{调用触摸屏模块}begin--------------------//
//-----{实例化触摸屏}begin
//此小节不需要更改
reg display_valid;
reg [39:0] display_name;
reg [31:0] display_value;
wire [5:0] display_number;
wire input_valid;
wire [31:0] input_value;

lcd_module lcd_module(
  .clk(clk), //10Mhz
  .resetn(resetn),

  //调用触摸屏的接口
  .display_valid(display_valid),
  .display_name(display_name),
  .display_value(display_value),
  .display_number(display_number),
  .input_valid(input_valid),
  .input_value(input_value),

  //lcd 触摸屏相关接口，不需要更改
  .lcd_rst(lcd_rst),
  .lcd_cs(lcd_cs),
  .lcd_rs(lcd_rs),
  .lcd_wr(lcd_wr),
  .lcd_rd(lcd_rd),
  .lcd_data_io(lcd_data_io),
  .lcd_bl_ctr(lcd_bl_ctr),
  .ct_int(ct_int),
  .ct_sda(ct_sda),
  .ct_scl(ct_scl),
  .ct_rstn(ct_rstn)
);
//-----{实例化触摸屏}end

//-----{从触摸屏获取输入}begin
//根据实际需要输入的数修改此小节，
//建议对每一个数的输入，编写单独一个 always 块
//当 input_sel 为 0 时，表示输入数为加数 1，即 operand1
always @(posedge clk)
begin
  if (!resetn)
  begin
    adder_operand1 <= 32'd0;
  end
  else if (input_valid && !input_sel)
  begin
    adder_operand1 <= input_value;
  end
end

//当 input_sel 为 1 时，表示输入数为加数 2，即 operand2
always @(posedge clk)
begin
  if (!resetn)
  begin
    adder_operand2 <= 32'd0;
  end
  else if (input_valid && input_sel)
  begin
    adder_operand2 <= input_value;
  end
end
//-----{从触摸屏获取输入}end

//-----{输出到触摸屏显示}begin
//根据需要显示的数修改此小节，
//触摸屏上共有 44 块显示区域，可显示 44 组 32 位数据
//44 块显示区域从 1 开始编号，编号为 1~44，
always @(posedge clk)
begin
  case(display_number)
    6'd1 :
      begin
        display_valid <= 1'b1;
        display_name <= "ADD_1";
        display_value <= adder_operand1;
      end
    6'd2 :
      begin
        display_valid <= 1'b1;
        display_name <= "ADD_2";
        display_value <= adder_operand2;
      end
    6'd3 :
      begin
        display_valid <= 1'b1;
        display_name <= "RESUL";
        display_value <= adder_result;
      end
    default :
      begin
        display_valid <= 1'b0;
        display_name <= 40'd0;
        display_value <= 32'd0;
      end
  endcase
end
//-----{输出到触摸屏显示}end
//----------------------{调用触摸屏模块}end---------------------//
endmodule
