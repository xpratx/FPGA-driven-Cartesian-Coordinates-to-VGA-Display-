`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 12.06.2025 11:01:50
// Design Name: 
// Module Name: broken_circles
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


module symbol_generator(
	input clk_25MHz,
	input reset,
	input [31:0] pix,
    output hsync,
    output vsync,
    output vga_out,
    output reg [15:0] inc_address

    );
    
    
    
    wire locked;
	reg [9:0] h_count = 0;  
    reg [9:0] v_count = 0;
    reg color;
	
	


    // VGA Timing parameters
    localparam H_ACTIVE = 640;
    localparam H_FP = 16;
    localparam H_SYNC = 96;
    localparam H_BP = 48;
    localparam H_TOTAL = H_ACTIVE + H_FP + H_SYNC + H_BP; 

    localparam V_ACTIVE = 480;
    localparam V_FP = 10;
    localparam V_SYNC = 2;
    localparam V_BP = 33;
    localparam V_TOTAL = V_ACTIVE + V_FP + V_SYNC + V_BP; 

    

    // Horizontal and vertical counters
    always @(posedge clk_25MHz or posedge reset) begin
        if (reset) begin
            h_count <= 0;
            v_count <= 0;
        end else begin
            if (h_count == H_TOTAL - 1) begin
                h_count <= 0;
                if (v_count == V_TOTAL - 1)
                    v_count <= 0;
                else
                    v_count <= v_count + 1;
            end else begin
                h_count <= h_count + 1;
            end
        end
    end

    // Generate sync signals (active low)
    assign hsync = ~((h_count >= (H_ACTIVE + H_FP)) && (h_count < (H_ACTIVE + H_FP + H_SYNC)));
    assign vsync = ~((v_count >= (V_ACTIVE + V_FP)) && (v_count < (V_ACTIVE + V_FP + V_SYNC)));


    // Display enable signal
    assign active_area = (h_count < H_ACTIVE) && (v_count < V_ACTIVE);

    
    integer i ;
    
    always @ (posedge clk_25MHz)
    begin
        if(active_area)
        begin
            if(i < 31)                              //takes in 32-bit data from pix_bram and send 1 if pix_bram contains 1 at that location
            begin
                i <= i + 1;
                inc_address <= inc_address;
                 if (pix[i])
                   begin
                         color <= 1'b1;            //this one bit data is converted to green in vga adapter by basys3
                   end
                 else
                 begin
                        color<=12'b0;               //0 is for black colour, i.e. background
                 end
            end
        
            
            else
            begin
                inc_address <= inc_address + 4;         //32 bits of data is stores in 4 consecutive locations
                i <= 0;                                //each location stores 8-bits of information, i.e. value of 8 consecutive pixels
                 if (pix[i])
                   begin
                         color <= 12'b1;
                   end
                 else
                 begin
                        color<=12'b0;
                 end
                
            end
                  
        end
   
        else
        color = 12'b0;
        
        
        if(v_count > 479)
            inc_address <= 0;
        
        
    end
    
    assign vga_out = color;

    
 endmodule
