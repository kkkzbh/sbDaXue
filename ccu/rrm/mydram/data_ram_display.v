`timescale 1ns / 1ps
module data_ram_display(
    //时钟与复位信号
     input clk,
    input resetn,    //后缀"n"表示低电平有效

    //输入开关，用于测试写使能和选择输入参数
    input [3:0] wen,
    input [1:0] input_sel,
    
    // SEC变为内部寄存器，不再是输入端口
    // input [1:0] sec,

    //led灯，用于指示写使能信号，以及当前在设什么参数
    output [3:0] led_wen,
    output led_addr,      //指示当前设置写地址
    output led_wdata,     //指示当前设置写数据
    output led_test_addr, //指示当前设置test地址

    //触摸屏接口，此处主要用作显示
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
//-----{LED指示}begin
    assign led_wen       = wen;
    assign led_addr      = (input_sel==2'd0);
    assign led_wdata     = (input_sel==2'd1);
    assign led_test_addr = (input_sel==2'd2);
//-----{LED指示}end
//-----{数据存储器模块}begin
    //数据存储器有两个端口，一个用于读写，另一个用于测试地址显示内存中的数据
    reg  [31:0] addr;
    reg  [31:0] wdata;
    wire [31:0] rdata;
    reg  [31:0] test_addr;
    wire [31:0] test_data;
    
    // SEC从输入端口改为内部寄存器
    reg  [1:0] sec;

    // 根据SEC选择实际的写使能信号
    reg [3:0] actual_wea;
    
    always @(*)
    begin
        case(sec)
            2'd0: begin  // 1字节模式
                case(addr[1:0])
                    2'b00: actual_wea = {3'b000, wen[0]};
                    2'b01: actual_wea = {2'b00, wen[0], 1'b0};
                    2'b10: actual_wea = {1'b0, wen[0], 2'b00};
                    2'b11: actual_wea = {wen[0], 3'b000};
                endcase
            end
            2'd1: begin  // 2字节模式
                case(addr[1])
                    1'b0: actual_wea = {2'b00, {2{wen[0]}}};
                    1'b1: actual_wea = {{2{wen[0]}}, 2'b00};
                endcase
            end
            default: begin  // 4字节模式 (SEC=2)
                actual_wea = wen;
            end
        endcase
    end

    // 添加一个寄存器来存储复位后的test_data初始值
    reg [31:0] test_data_reg;
    wire reset_active;
    assign reset_active = !resetn;

    // 添加掩码处理逻辑，确保只有选定的字节被写入，其他字节正确保留
    reg [31:0] wdata_masked;
    
    always @(*) begin
        case(sec)
            2'd0: begin  // 1字节模式
                case(addr[1:0])
                    2'b00: wdata_masked = {rdata[31:8], wdata[7:0]};
                    2'b01: wdata_masked = {rdata[31:16], wdata[7:0], rdata[7:0]};
                    2'b10: wdata_masked = {rdata[31:24], wdata[7:0], rdata[15:0]};
                    2'b11: wdata_masked = {wdata[7:0], rdata[23:0]};
                endcase
            end
            2'd1: begin  // 2字节模式
                case(addr[1])
                    1'b0: wdata_masked = {rdata[31:16], wdata[15:0]};
                    1'b1: wdata_masked = {wdata[15:0], rdata[15:0]};
                endcase
            end
            default: begin  // 4字节模式 (SEC=2)
                wdata_masked = wdata;
            end
        endcase
    end
    
    // 修改RAM接口和读写控制逻辑
    reg [31:0] ram_init_data;  // 用于初始化RAM的数据寄存器
    reg [3:0] ram_init_wea;    // 用于初始化RAM的写使能信号
    reg [7:0] ram_init_addr;   // 用于初始化RAM的地址计数器
    reg ram_init_done;         // RAM初始化完成标志
    
    // RAM初始化状态机
    localparam INIT = 1'b0, NORMAL = 1'b1;
    reg ram_state;
    
    always @(posedge clk or negedge resetn) begin
        if (!resetn) begin
            ram_init_addr <= 8'd0;
            ram_init_data <= 32'h00000000;
            ram_init_wea <= 4'b1111;  // 初始化时，全部字节都写入
            ram_init_done <= 1'b0;
            ram_state <= INIT;
        end else begin
            case (ram_state)
                INIT: begin
                    // 初始化所有RAM地址为0
                    if (ram_init_addr < 8'd128) begin // 假设RAM大小为128个位置
                        ram_init_addr <= ram_init_addr + 1'b1;
                    end else begin
                        ram_init_done <= 1'b1;
                        ram_state <= NORMAL;
                    end
                end
                NORMAL: begin
                    // 正常操作模式，保持这些寄存器的值
                    ram_init_addr <= ram_init_addr;
                    ram_init_data <= ram_init_data;
                    ram_init_wea <= 4'b0000;
                    ram_init_done <= ram_init_done;
                end
            endcase
        end
    end
    
    // 写入RAM时使用的地址、数据和写使能信号
    wire [7:0] ram_addr;
    wire [31:0] ram_wdata;
    wire [3:0] ram_wea;
    
    // 在初始化和正常模式之间选择适当的信号
    assign ram_addr = (ram_state == INIT) ? ram_init_addr : {3'b0, addr[6:2]};
    assign ram_wdata = (ram_state == INIT) ? ram_init_data : wdata_masked;
    assign ram_wea = (ram_state == INIT) ? ram_init_wea : actual_wea;

    data_ram data_ram_module(
        //双端口RAM
    .clka(clk),    // input wire clka
    .wea(ram_wea),      // 使用根据SEC调整后的写使能信号和掩码数据
    .addra(ram_addr),  // input wire [7 : 0] addra
    .dina(ram_wdata),  // 使用掩码处理后的数据
    .douta(rdata),     // output wire [31 : 0] douta
    .web(4'b0000),     // 修改：B端口设置为只读模式，写使能始终为0
    .clkb(clk),        // input wire clkb
    .addrb({3'b0,test_addr[6:2]}),  // input wire [7 : 0] addrb
    .doutb(test_data)  // output wire [31 : 0] doutb
    );

    // 添加复位逻辑，确保T_DATA在复位后显示为0
    always @(posedge clk)
    begin
        if (!resetn)
        begin
            test_data_reg <= 32'h00000000; // 复位时将test_data_reg设置为0
        end
        else
        begin
            test_data_reg <= test_data; // 正常操作时，跟踪test_data的值
        end
    end
//-----{数据寄存器模块}end

//---------------------{触摸屏显示模块}begin--------------------//
//-----{实例化显示模块}begin
//此小段内不需要修改
    reg         display_valid;
    reg  [39:0] display_name;
    reg  [31:0] display_value;
    wire [5 :0] display_number;
    wire        input_valid;
    wire [31:0] input_value;

    lcd_module lcd_module(
        .clk            (clk           ),   //10Mhz
        .resetn         (resetn        ),

        //用户可修改的接口
        .display_valid  (display_valid ),
        .display_name   (display_name  ),
        .display_value  (display_value ),
        .display_number (display_number),
        .input_valid    (input_valid   ),
        .input_value    (input_value   ),

        //lcd物理接口，不需要修改
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
//-----{实例化显示模块}end

//-----{从触摸屏获取数据}begin
//根据实验需要，修改此小段：
//建议对每一个数的输入，编写单独一个always块
    //在这里实际需要改变输入，修改此小段：
    //当input_sel为2'b00时，显示参数项为写地址，即addr
    always @(posedge clk)
    begin
        if (!resetn)
        begin
            addr <= 32'd0;
        end
        else if (input_valid && input_sel==2'd0)
        begin
            // 根据SEC值应用不同的地址掩码，只限制写地址
            case(sec)
                2'd0: addr <= input_value;                   // 1字节模式：所有地址位有效
                2'd1: addr <= {input_value[31:1], 1'b0};     // 2字节模式：低1位强制为0
                2'd2: addr <= {input_value[31:2], 2'b00};    // 4字节模式：低2位强制为0
                default: addr <= {input_value[31:2], 2'b00}; // 默认同4字节模式
            endcase
        end
    end
    
    //当input_sel为2'b01时，显示参数项为写数据，即wdata
    always @(posedge clk)
    begin
        if (!resetn)
        begin
            wdata <= 32'd0;
        end
        else if (input_valid && input_sel==2'd1)
        begin
            wdata <= input_value;
        end
    end
    
    //当input_sel为2'b10时，显示参数项为test地址，即test_addr
    //对读地址T_ADD不做字节对齐限制，始终读取4字节
    always @(posedge clk)
    begin
        if (!resetn)
        begin
            test_addr  <= 32'd0;
        end
        else if (input_valid && input_sel==2'd2)
        begin
            // 恢复原始逻辑，不限制读地址
            test_addr[31:2] <= input_value[31:2];
        end
    end
    
    //当input_sel为2'b11时，显示参数项为SEC值，即字节宽度设置
    always @(posedge clk)
    begin
        if (!resetn)
        begin
            sec <= 2'd2;  // 默认为4字节模式
        end
        else if (input_valid && input_sel==2'd3)  // 使用新的选择值2'd3
        begin
            if (input_value < 3)  // 确保SEC只能是0,1,2
                sec <= input_value[1:0];
        end
    end
//-----{从触摸屏获取数据}end

//-----{将数据显示到触摸屏}begin
//根据需要显示的内容，修改此小段：
//本实验总共需要44个显示条目，可以显示44个32位数据
//44个显示条目的编号从1开始，即为1~44。
    always @(posedge clk)
    begin
       case(display_number)
           6'd1:
           begin
               display_valid <= 1'b1;
               display_name  <= "ADDR ";
               display_value <= addr;
           end
           6'd2: 
           begin
               display_valid <= 1'b1;
               display_name  <= "WDATA";
               display_value <= wdata;
           end
           6'd3: 
           begin
               display_valid <= 1'b1;
               display_name  <= "RDATA";
               display_value <= rdata;
           end
           6'd4:
           begin
               display_valid <= 1'b1;
               display_name  <= "SEC  ";
               display_value <= {30'b0, sec};
           end
           6'd5: 
           begin
               display_valid <= 1'b1;
               display_name  <= "T_ADD";
               display_value <= test_addr;
           end
           6'd6: 
           begin
               display_valid <= 1'b1;
               display_name  <= "T_DAT";
               // 使用test_data_reg而不是直接使用test_data
               display_value <= reset_active ? 32'h00000000 : test_data_reg;
           end
           6'd7:
           begin
               display_valid <= 1'b1;
               case(sec)
                   2'd0: display_name <= "MODE1";  // 1字节模式
                   2'd1: display_name <= "MODE2";  // 2字节模式
                   2'd2: display_name <= "MODE4";  // 4字节模式
                   default: display_name <= "ERROR";
               endcase
               case(sec)
                   2'd0: display_value <= 32'h1;  // 1字节
                   2'd1: display_value <= 32'h2;  // 2字节
                   2'd2: display_value <= 32'h4;  // 4字节
                   default: display_value <= 32'h0;
               endcase
           end
           default :
           begin
               display_valid <= 1'b0;
               display_name  <= 40'd0;
               display_value <= 32'd0;
           end
       endcase
    end
//-----{将数据显示到触摸屏}end
//----------------------{触摸屏显示模块}end---------------------//
endmodule

