`timescale 1ns / 1ps
// -----------------------------------------------------------------------------
// P_board_top.v: Top-level for on-board verification with an LCD
//
// - Module definition matches the provided XDC file.
// - Instantiates the P_PipelineCPU.
// - Instantiates an lcd_module to drive an LCD screen.
// - Cycles through memory and register addresses and displays their values.
// -----------------------------------------------------------------------------
module P_board_top(
    input clk,
    input resetn,    // Low-active reset, matches XDC

    // LCD Hardware Interface (from XDC)
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

    wire [31:0] cpu_test_data_addr;
    wire [4:0]  cpu_test_reg_addr;
    wire [31:0] cpu_mem_data_out;
    wire [31:0] cpu_reg_data_out;

    // Instantiate the Pipelined CPU
    // Note: The CPU uses a high-active reset, so we invert resetn.
    P_PipelineCPU u_cpu (
        .clk(clk),
        .rst(~resetn),
        .test_data_addr(cpu_test_data_addr),
        .test_reg_addr(cpu_test_reg_addr),
        .test_data_out(cpu_mem_data_out),
        .test_reg_out(cpu_reg_data_out)
    );

    // Instantiate the LCD driver module
    // This assumes 'lcd_module' is available in the Vivado project.
    lcd_module u_lcd (
        .clk(clk),
        .resetn(resetn),
        .display_valid(display_valid),
        .display_name(display_name),
        .display_value(display_value),
        .display_number(display_number),
        .input_valid(input_valid),
        .input_value(input_value),
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

    // Logic to control what is shown on the LCD
    reg         display_valid;
    reg  [39:0] display_name;
    reg  [31:0] display_value;
    wire [5:0]  display_number; // Driven by lcd_module, indicates current row
    wire        input_valid;    // Not used in this read-only display
    wire [31:0] input_value;    // Not used

    // Function to convert a 4-bit binary to ASCII hex character
    function [7:0] bin_to_ascii_hex;
        input [3:0] val;
        begin
            if (val < 10)
                bin_to_ascii_hex = val + 8'h30; // ASCII '0'
            else
                bin_to_ascii_hex = val - 10 + 8'h41; // ASCII 'A'
        end
    endfunction

    // Wires for the two hex characters of the address
    wire [7:0] addr_char1, addr_char0;

    // Convert the 6-bit display_number to two hex characters
    assign addr_char1 = bin_to_ascii_hex(display_number[5:4]); // High nibble
    assign addr_char0 = bin_to_ascii_hex(display_number[3:0]); // Low nibble

    // Connect the display row number to the CPU's test address inputs
    assign cpu_test_data_addr = (display_number < 32) ? display_number : 0;
    assign cpu_test_reg_addr  = (display_number >= 32) ? (display_number - 32) : 0;

    // Logic to select what to display on the current LCD row
    always @(posedge clk) begin
        display_valid <= 1'b1;
        if (display_number < 32) begin // Show Data Memory contents for rows 0-31
            display_name  <= {"MEM[", addr_char1, addr_char0, "]"};
            display_value <= cpu_mem_data_out;
        end else if (display_number < 64) begin // Show Register File for rows 32-63
            display_name  <= {"REG[", addr_char1, addr_char0, "]"};
            display_value <= cpu_reg_data_out;
        end else begin // Blank for other rows
            display_valid <= 1'b0;
            display_name  <= 0;
            display_value <= 0;
        end
    end

endmodule 