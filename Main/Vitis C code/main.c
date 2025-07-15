
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "sleep.h"
#include"xil_io.h"


void pbram_zero()						//clears pixel_bram and sets all the pixel value to 0

{

	for (int i1=0; i1<9600; i1++)
	{
	Xil_Out32(XPAR_PIX_CTRL_S_AXI_BASEADDR + (4*i1), 0 );		
	}
}

void pbram_allF()				//sets all pixel value to 1

{

	for (int i1=0; i1<9600; i1++)
	{
	Xil_Out32(XPAR_PIX_CTRL_S_AXI_BASEADDR + (4*i1), 0xFFFFFFFF );
	}
}


void IWillPrint( int offset, int HowManyPoints)				//takes in coords and converts it into pixel_map and send it to pixel_bram
{

    		int prev_packet_no = 0;							//if there are multiple symbols in the memory, then we pass down the offset for the symbol
    		int packet_no;									//that we want to print and how may points are there in the symbol is all passed as an argument
    		int div;
    		int inc = 0;
    		u32 sum = 0;		
    		int bit_location;
    		int X_in, Y_in;

	 	 	X_in = Xil_In32( XPAR_X_COORDS_CTRL_S_AXI_BASEADDR + 4*offset);
	        Y_in = Xil_In32(XPAR_Y_COORDS_CTRL_S_AXI_BASEADDR + 4*offset);

	        	for(int i = 1; i<HowManyPoints+1; i++)
	        	{

	        			div = X_in/32;
	        			packet_no = (Y_in*20) + div;		//packet size is 32bits because we have XilOut32 and not XilOut1
															//calculates the packet number for a particular pixel. The screen is divided into 20x480 packets


	        			if(prev_packet_no != packet_no)		//when we know that the next coord does not lie in the same packet we know that 
	        			{									//the packet is ready to be sent to the pixel_bram
	        				Xil_Out32(XPAR_PIX_CTRL_S_AXI_BASEADDR + (4*prev_packet_no), sum );
	        				sum = 0;
	        			}


						bit_location = X_in % 32;			//finds the bit location of the coord in the packet 

	        		    sum = sum | (1<<bit_location);		//shifts the bit to the desired location in the packet



	        			prev_packet_no = packet_no;



	        			 X_in = Xil_In32(XPAR_X_COORDS_CTRL_S_AXI_BASEADDR + 4*i + 4*offset);		//takes in the next coord
	        			 Y_in = Xil_In32(XPAR_Y_COORDS_CTRL_S_AXI_BASEADDR + 4*i + 4*offset);


	        	}



	        Xil_Out32(XPAR_PIX_CTRL_S_AXI_BASEADDR + (4*prev_packet_no), sum );


}


void removeSymbol(int offset, int HowManyPoints)
{

	    		int packet_no;
	    		int div;
	    		int inc = 0;
	    		int bit_location;
	    		int prev_packet_no = 0;
	    		u32 sum_remove = 0xFFFFFFFF;

	    		int X_in, Y_in;

	    		X_in = Xil_In32( XPAR_X_COORDS_CTRL_S_AXI_BASEADDR + 4*offset);
	    		Y_in = Xil_In32(XPAR_Y_COORDS_CTRL_S_AXI_BASEADDR + 4*offset);

		        	for(int i = 0; i<HowManyPoints; i++)
		        	{

		        			div = X_in/32;
		        			packet_no = (Y_in*20) + div;

		        			if(prev_packet_no != packet_no)
		        				{
		        				    Xil_Out32(XPAR_PIX_CTRL_S_AXI_BASEADDR + (4*prev_packet_no), sum_remove );
		        				    sum_remove = 0xFFFFFFFF;
		        				        			}


		        			bit_location = X_in % 32;

		        		    sum_remove = sum_remove & (0<<bit_location);



		        		     prev_packet_no = packet_no;



		        			 inc++;
		        			 X_in = Xil_In32( XPAR_X_COORDS_CTRL_S_AXI_BASEADDR + 4*offset  + 4*inc);
		        			 Y_in = Xil_In32(XPAR_Y_COORDS_CTRL_S_AXI_BASEADDR + 4*offset  + 4*inc);



		        	}



		        Xil_Out32(XPAR_PIX_CTRL_S_AXI_BASEADDR + (packet_no), 0);


}


void printShiftedY(int offset, int HowManyPoints, int step)
{

	int prev_packet_no = 0;
	int packet_no;
	int div;
	int inc = 0;
	u32 sum = 0;
	int bit_location;
	int X_in, Y_in;

	 	X_in = Xil_In32( XPAR_X_COORDS_CTRL_S_AXI_BASEADDR + 4*offset);
	 	Y_in = Xil_In32(XPAR_Y_COORDS_CTRL_S_AXI_BASEADDR + 4*offset) - step;

    	for(int i = 1; i<HowManyPoints+1; i++)
    	{

    			div = X_in/32;
    			packet_no = (Y_in*20) + div;



    			if(prev_packet_no != packet_no)
    			{
    				Xil_Out32(XPAR_PIX_CTRL_S_AXI_BASEADDR + (4*prev_packet_no), sum );
    				sum = 0;
    			}


				bit_location = X_in % 32;

    		    sum = sum | (1<<bit_location);



    			prev_packet_no = packet_no;



    			 X_in = Xil_In32(XPAR_X_COORDS_CTRL_S_AXI_BASEADDR + 4*i + 4*offset);
    			 Y_in = Xil_In32(XPAR_Y_COORDS_CTRL_S_AXI_BASEADDR + 4*i + 4*offset) - step;


    	}



    Xil_Out32(XPAR_PIX_CTRL_S_AXI_BASEADDR + (4*prev_packet_no), sum );

}


void removeShiftedY(int offset, int HowManyPoints, int step)
{
					int packet_no;
		    		int div;
		    		int inc = 0;
		    		int bit_location;
		    		int prev_packet_no = 0;
		    		u32 sum_remove = 0xFFFFFFFF;

		    		int X_in, Y_in;

		    		X_in = Xil_In32( XPAR_X_COORDS_CTRL_S_AXI_BASEADDR + 4*offset);
		    		Y_in = Xil_In32(XPAR_Y_COORDS_CTRL_S_AXI_BASEADDR + 4*offset) -  step;

			        	for(int i = 0; i<HowManyPoints; i++)
			        	{

			        			div = X_in/32;
			        			packet_no = (Y_in*20) + div;

			        			if(prev_packet_no != packet_no)
			        				{
			        				    Xil_Out32(XPAR_PIX_CTRL_S_AXI_BASEADDR + (4*prev_packet_no), sum_remove );
			        				    sum_remove = 0xFFFFFFFF;
			        				        			}


			        			bit_location = X_in % 32;

			        		    sum_remove = sum_remove & (0<<bit_location);



			        		     prev_packet_no = packet_no;



			        			 inc++;
			        			 X_in = Xil_In32( XPAR_X_COORDS_CTRL_S_AXI_BASEADDR + 4*offset  + 4*inc);
			        			 Y_in = Xil_In32(XPAR_Y_COORDS_CTRL_S_AXI_BASEADDR + 4*offset  + 4*inc) - step;



			        	}



			        Xil_Out32(XPAR_PIX_CTRL_S_AXI_BASEADDR + (packet_no), 0);

}


void moveUp(int offset, int HowManyPoints, int shift)
{
	for(int i = 0; i<shift ; i++)
	{

		printShiftedY(offset, HowManyPoints, i);
		removeShiftedY(offset, HowManyPoints, i);

	}

//	printShiftedY(offset, HowManyPoints, shift);
}

void moveDown(int offset, int HowManyPoints, int shift)
{
	for(int i = 0; i<shift ; i++)
		{

			printShiftedY(offset, HowManyPoints, -i);
			removeShiftedY(offset, HowManyPoints, -i);

		}
}

void oscillate(int offset, int HowManyPoints, int shift)
{

	while(1)
	{
	for(int i = 0; i<shift ; i++)
			{

				printShiftedY(offset, HowManyPoints, i);
				removeShiftedY(offset, HowManyPoints, i);

			}

	for(int j = shift - 2 ; j>=0; j--)
	{
		printShiftedY(offset, HowManyPoints, j);
		removeShiftedY(offset, HowManyPoints, j);
	}
	}

//	printShiftedY(offset, HowManyPoints, shift);
}

int main()
{
    init_platform();



    IWillPrint(0, 5517);
//    IWillPrint(6628, 2939 );
//    IWillPrint(9567, 2939 );
//    IWillPrint(12506, 1427 );
//    IWillPrint(13933, 1354 );
//    sleep(1);



//    moveUp(0, 2939, 1);
//    sleep(1);
//    moveDown(0, 2939, 50);
    oscillate(0, 2939, 50);


    cleanup_platform();

    return 0;

}
