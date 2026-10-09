

module single_display(
    // 时钟与复位信号
    input clk,
    input resetn,    // 低电平有效复位

    // LCD和触摸屏接口，无需修改
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

//-----{LED显示}begin
// (此部分为空)
//-----{LED显示}end

//-----{实例化CPU核}begin
    // 定义连接CPU的测试端口
    wire [31:0] test_addr; // 用于读取DataMemory的地址
    wire [31:0] test_data;  
    wire [4:0]test_addr1; // 用于读取RegFile的地址
    wire [31:0]test_data1;

    // CPU复位信号处理 (开发板为低电平复位，CPU核为高电平复位)
    wire cpu_reset = ~resetn;

    // 实例化单周期CPU
    SingleCycleCPU CPU(
        .clk   (clk       ),
        .Reset (cpu_reset ), // 使用处理后的高电平复位信号
        .test_addr(test_addr),
        .test_addr1(test_addr1),
        .test_data (test_data),
        .test_data1(test_data1)
    );
//-----{实例化CPU核}end

//---------------------{LCD显示模块}begin--------------------//
//-----{实例化LCD驱动}begin
    // 此部分为LCD驱动模块接口，无需修改
    reg         display_valid;
    reg  [39:0] display_name;
    reg  [31:0] display_value;
    wire [5 :0] display_number; // LCD模块当前希望显示的行号
    wire        input_valid;
    wire [31:0] input_value;

    lcd_module lcd_module(
        .clk            (clk           ),
        .resetn         (resetn        ),

        .display_valid  (display_valid ),
        .display_name   (display_name  ),
        .display_value  (display_value ),
        .display_number (display_number),
        .input_valid    (input_valid   ),
        .input_value    (input_value   ),

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
//-----{实例化LCD驱动}end

//-----{从CPU核获取数据}begin
    // display_number由LCD模块产生，范围1-44，用于选择要显示的内容
    // 此处设置，当LCD要显示第1-32行时，对应查看数据存储器的0-31地址
    assign test_addr = display_number - 6'd1;
    // test_addr1的连接可在此处添加
//-----{从CPU核获取数据}end

//-----{准备要在LCD上显示的数据}begin
    // 此处定义了44个显示项，可按需修改
    always @(posedge clk)
    begin
        // display_number是LCD当前要显示的行号 (1-44)
        if ( display_number > 0 && display_number < 33 ) // 显示数据存储器MEM[0]到MEM[31]
        begin
            display_valid <= 1'b1;
            // 修复: "MEM"字符串不能直接赋值，需使用ASCII码。'M'=h4D, 'E'=h45
            display_name[39:16] <= {8'h4D, 8'h45, 8'h4D}; // "MEM"
            // 将地址数值转换为ASCII码用于显示，如地址15(hF)显示为"MEM0F"
            display_name[15: 8] <= {4'b0011, test_addr[7:4]}; // 地址高4位
            display_name[7 : 0] <= {4'b0011, test_addr[3:0]}; // 地址低4位
            display_value       <= test_data;
          end
        else // 其他行不显示
        begin
           display_valid <= 1'b0;
           display_name  <= 40'd0;
           display_value <= 32'd0;
        end
    end
//-----{准备要在LCD上显示的数据}end
//----------------------{LCD显示模块}end---------------------//
endmodule
