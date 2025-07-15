# FPGA driven Cartesian Coordinates to VGA Display 
This project aims at displaying a picture and converting it into a set of cartesian coordinates. Then it is converted to a pixel map to generate the VGA display using FPGA.
We painted a picture on MS Paint and then used simple MATLAB to generate the cartesian coordinates. You can use any black&white picture as long as it is 640x480 in resolution. (Standard VGA resolution)

## Hardware used
- Zynq Ultrascale+ ZCU 102 board (absolute overkill, not required)
- BASYS 3 board
  
 We used Zynq board just because BASYS 3 did not have enough BRAM to store our coordinate requirment. Also Zynq board does not have a VGA output so we used BASYS 3 just as an VGA Adapter.

## Flow of Work
  
                              Draw an image on Paint
                                        |
                                        |
                                       \ /
                      Genrate coordinates using MATLAB                     C-code does the movement of symbols
                                        |                                               / \
                                        |                                                |
                                       \ /                                               |
              Feed in to a .coe file onto the x and y BRAMs sperately -----> Verilog converts into a pixel map
                                   
            
