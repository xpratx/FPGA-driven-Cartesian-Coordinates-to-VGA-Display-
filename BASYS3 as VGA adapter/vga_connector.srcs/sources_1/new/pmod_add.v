`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 26.06.2025 11:20:15
// Design Name: 
// Module Name: pmod_add
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


module pmod_add(
    input vga_in,
    input h_sync_in,
    input v_sync_in,
    output wire [11:0]vga_out,
    output h_sync_out,
    output v_sync_out,
    output led_h,
    output led_v,
    output [11:0] led_vga
    

    );
    
    
     
     assign vga_out[0] = 0;
     assign vga_out[1] = 0;
     assign vga_out[2] = 0;
     assign vga_out[3] = 0;
     assign vga_out[4] = vga_in;
     assign vga_out[5] = vga_in;
     assign vga_out[6] = vga_in;
     assign vga_out[7] = vga_in;
     assign vga_out[8] = 0;
     assign vga_out[9] = 0;
     assign vga_out[10] = 0;
     assign vga_out[11] = 0;
     
     


    assign v_sync_out = v_sync_in;
    assign h_sync_out = h_sync_in;
    
    assign led_h = h_sync_in;
    assign led_v = v_sync_in;

    assign led_vga[0] = vga_in;
    assign led_vga[1] = vga_in;
    assign led_vga[2] = vga_in;
    assign led_vga[3] = vga_in;
    assign led_vga[4] = vga_in;
    assign led_vga[5] = vga_in;
    assign led_vga[6] = vga_in;
    assign led_vga[7] = vga_in;
    assign led_vga[8] = vga_in;
    assign led_vga[9] = vga_in;
    assign led_vga[10] = vga_in;
    assign led_vga[11] = vga_in;
   
    
endmodule
