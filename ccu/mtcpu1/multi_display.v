`timescale 1ns / 1ps
//
// multi_display.v: 用于综合和烧写的顶层
//
module multi_display(
    input clk,
    input resetn,    // 低电平有效复位

    // LCD 硬件接口
    output lcd_rst,
    output lcd_cs,
    output lcd_rs,
    output lcd_wr,
    output lcd_rd,
    inout  [15:0] lcd_data_io,
    output lcd_bl_ctr,
    inout ct_int,
    inout ct_sda,
    output ct_scl,
    output ct_rstn
);

    wire [31:0] test_addr;
    wire [31:0] test_data;
    wire [4:0]  test_addr1;
    wire [31:0] test_data1;

    // 实例化多周期 CPU
    MultiCycleCPU CPU (
        .clk   (clk),
        .rst   (~resetn),  // CPU 使用高电平复位
        .test_data_addr(test_addr),
        .test_reg_addr(test_addr1),
        .test_data_out(test_data),
        .test_reg_out(test_data1)
    );

    // 实例化 LCD 驱动模块
    lcd_module lcd_module_inst (
        .clk            (clk),
        .resetn         (resetn),
        .display_valid  (display_valid),
        .display_name   (display_name),
        .display_value  (display_value),
        .display_number (display_number),
        .input_valid    (input_valid),
        .input_value    (input_value),
        .lcd_rst        (lcd_rst),
        .lcd_cs         (lcd_cs),
        .lcd_rs         (lcd_rs),
        .lcd_wr         (lcd_wr),
        .lcd_rd         (lcd_rd),
        .lcd_data_io    (lcd_data_io),
        .lcd_bl_ctr     (lcd_bl_ctr),
        .ct_int         (ct_int),
        .ct_sda         (ct_sda),
        .ct_scl         (ct_scl),
        .ct_rstn        (ct_rstn)
    );

    // LCD 显示逻辑
    reg         display_valid;
    reg  [39:0] display_name;
    reg  [31:0] display_value;
    wire [5:0]  display_number;
    wire        input_valid;
    wire [31:0] input_value;

    assign test_addr = display_number - 6'd1;

    always @(posedge clk) begin
        if (display_number < 6'd33) begin // 显示 MEM[0]-MEM[31]
            display_valid <= 1'b1;
            display_name[39:16] <= "MEM";
            display_name[15:8]  <= {4'b0011, test_addr[7:4]};
            display_name[7:0]   <= {4'b0011, test_addr[3:0]};
            display_value       <= test_data;
        end else begin
            display_valid <= 1'b0;
            display_name  <= 40'd0;
            display_value <= 32'd0;
        end
    end

endmodule 