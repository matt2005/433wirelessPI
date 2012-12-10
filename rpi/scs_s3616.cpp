// scs_s3616.cpp
//
// To compile this: gcc -o scs_s3616 scs_s3616.cpp
// This program can be use to control SCS S3616-2 Remote Controlled Outlet
// By default you'll need a 433.92Mhz transmitter at GPIO 7 on your Raspberry PI

// Ce programme permet de controler des prises radio commandées SCS S3616-2
// Vous pouvez les acheter ici:
// http://scs-laboutique.com/Electricite/Commande+a+distance/s3162+1000w+kit+2+prises+telecommand-111
// 
// Pour l'emetteur 433.92Mhz vous pouvez l'acheter ici:
// http://snootlab.com/composants/147-emetteur-rf-434-mhz.html


// You can change the GPIO of the transmitter here.
// For more information - http://elinux.org/RPi_Low-level_peripherals
////PARAMETERS //////////////////////////////
int transmitter = 7;
/////////////////////////////////////////////

#define BCM2708_PERI_BASE        0x20000000
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>

#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)

int  mem_fd;
unsigned char *gpio_mem, *gpio_map;
char *spi0_mem, *spi0_map;
char code[79]; 	// Size of the Code String.

// I/O access
volatile unsigned *gpio;

// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

#define GPIO_SET *(gpio+7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR *(gpio+10) // clears bits which are 1 ignores bits which are 0

// function prototypes.
void setup_io();
void SendCode(char* code);

int main(int argc, char **argv)
{ 
	
	if (argc == 3)
	{
		switch(toupper(argv[1][0])){
		
		//A
		case 'A':
			switch(argv[1][1]){
		
			// A1
			case '1':
				switch(argv[2][0]){
				case '0':
				strcpy(code,"0001001001001101001101001101001101001101001101001101001101001001101101001001000");
				printf ("Outlet A1 is turned off\n");
				break;
				
				case '1':
				strcpy(code,"0001001001001101001101001101001101001101001101001101001101001001001001101101000");
				printf ("Outlet A1 is turned on\n");
				break;	  
				}
			break;
		
			// A2
			case '2':
			switch(argv[2][0]){
				case '0':
				strcpy(code,"0001001001001101001101001101001101001101001101001101001001001101101101001001000");
				printf ("Outlet A2 is turned off\n");
				break;
				
				case '1':
				strcpy(code,"0001001001001101001101001101001101001101001101001101001001001101001001101101000");
				printf ("Outlet A2 is turned on\n");
				break;	  
				}
			break;
			
			// A3
			case '3':
			switch(argv[2][0]){
				case '0':
				strcpy(code,"0001001001001101001101001101001101001101001101001001001101001101101101001001000");
				printf ("Outlet A3 is turned off\n");
				break;
				
				case '1':
				strcpy(code,"0001001001001101001101001101001101001101001101001001001101001101001001101101000");
				printf ("Outlet A3 is turned on\n");
				break;	  
				}
			break;
			
			// A4
			case '4':
			switch(argv[2][0]){
				case '0':
				strcpy(code,"0001001001001101001101001101001101001101001001001101001101001101101101001001000");
				printf ("Outlet A4 is turned off\n");
				break;
				
				case '1':
				strcpy(code,"0001001001001101001101001101001101001101001001001101001101001101001001101101000");
				printf ("Outlet A4 is turned on\n");
				break;	  
				}
			break;
			}
		break;
		
		//B
		case 'B':
		switch(argv[1][1]){
		
			// B1
			case '1':
				switch(argv[2][0]){
				case '0':
				strcpy(code,"0001001101001001001101001101001101001101001101001101001101001001101101001001000");
				printf ("Outlet B1 is turned off\n");
				break;
				
				case '1':
				strcpy(code,"0001001101001001001101001101001101001101001101001101001101001001001001101101000");
				printf ("Outlet B1 is turned on\n");
				break;	  
				}
			break;
		
			// B2
			case '2':
			switch(argv[2][0]){
				case '0':
				strcpy(code,"0001001101001001001101001101001101001101001101001101001001001101101101001001000");
				printf ("Outlet B2 is turned off\n");
				break;
				
				case '1':
				strcpy(code,"0001001101001001001101001101001101001101001101001101001001001101001001101101000");
				printf ("Outlet B2 is turned on\n");
				break;	  
				}
			break;
			
			// B3
			case '3':
			switch(argv[2][0]){
				case '0':
				strcpy(code,"0001001101001001001101001101001101001101001101001001001101001101101101001001000");
				printf ("Outlet B3 is turned off\n");
				break;
				
				case '1':
				strcpy(code,"0001001101001001001101001101001101001101001101001001001101001101001001101101000");
				printf ("Outlet B3 is turned on\n");
				break;	  
				}
			break;
			
			// B4
			case '4':
			switch(argv[2][0]){
				case '0':
				strcpy(code,"0001001101001001001101001101001101001101001001001101001101001101101101001001000");
				printf ("Outlet B4 is turned off\n");
				break;
				
				case '1':
				strcpy(code,"0001001101001001001101001101001101001101001001001101001101001101001001101101000");
				printf ("Outlet B4 is turned on\n");
				break;	  
				}
			break;
			}
		break;
		
		//C
		case 'C':
		switch(argv[1][1]){
		
			// C1
			case '1':
				switch(argv[2][0]){
				case '0':
				strcpy(code,"0001001101001101001001001101001101001101001101001101001101001001101101001001000");
				printf ("Outlet C1 is turned off\n");
				break;
				
				case '1':
				strcpy(code,"0001001101001101001001001101001101001101001101001101001101001001001001101101000");
				printf ("Outlet C1 is turned on\n");
				break;	  
				}
			break;
		
			// C2
			case '2':
			switch(argv[2][0]){
				case '0':
				strcpy(code,"0001001101001101001001001101001101001101001101001101001001001101101101001001000");
				printf ("Outlet C2 is turned off\n");
				break;
				
				case '1':
				strcpy(code,"0001001101001101001001001101001101001101001101001101001001001101001001101101000");
				printf ("Outlet C2 is turned on\n");
				break;	  
				}
			break;
			
			// C3
			case '3':
			switch(argv[2][0]){
				case '0':
				strcpy(code,"0001001101001101001001001101001101001101001101001001001101001101101101001001000");
				printf ("Outlet C3 is turned off\n");
				break;
				
				case '1':
				strcpy(code,"0001001101001101001001001101001101001101001101001001001101001101001001101101000");
				printf ("Outlet C3 is turned on\n");
				break;	  
				}
			break;
			
			// C4
			case '4':
			switch(argv[2][0]){
				case '0':
				strcpy(code,"0001001010011010010010011010011010011010010010011010011010011011011011001001000");
				printf ("Outlet C4 is turned off\n");
				break;
				
				case '1':
				strcpy(code,"0001001101001101001001001101001101001101001001001101001101001101001001101101000");
				printf ("Outlet C4 is turned on\n");
				break;	  
				}
			break;
			}
		break;
		
		//D
		case 'D':
		switch(argv[1][1]){
		
			// D1
			case '1':
				switch(argv[2][0]){
				case '0':
				strcpy(code,"0001001101001101001101001001001101001101001101001101001101001001101101001001000");
				printf ("Outlet D1 is turned off\n");
				break;
				
				case '1':
				strcpy(code,"0001001101001101001101001001001101001101001101001101001101001001001001101101000");
				printf ("Outlet D1 is turned on\n");
				break;	  
				}
			break;
		
			// D2
			case '2':
			switch(argv[2][0]){
				case '0':
				strcpy(code,"0001001101001101001101001001001101001101001101001101001001001101101101001001000");
				printf ("Outlet D2 is turned off\n");
				break;
				
				case '1':
				strcpy(code,"0001001101001101001101001001001101001101001101001101001001001101001001101101000");
				printf ("Outlet D2 is turned on\n");
				break;	  
				}
			break;
			
			// D3
			case '3':
			switch(argv[2][0]){
				case '0':
				strcpy(code,"0001001101001101001101001001001101001101001101001001001101001101101101001001000");
				printf ("Outlet D3 is turned off\n");
				break;
				
				case '1':
				strcpy(code,"0001001101001101001101001001001101001101001101001001001101001101001001101101000");
				printf ("Outlet D3 is turned on\n");
				break;	  
				}
			break;
			
			// D4
			case '4':
			switch(argv[2][0]){
				case '0':
				strcpy(code,"0001001101001101001101001001001101001101001001001101001101001101101101001001000");
				printf ("Outlet D4 is turned off\n");
				break;
				
				case '1':
				strcpy(code,"0001001101001101001101001001001101001101001001001101001101001101001001101101000");
				printf ("Outlet D4 is turned on\n");
				break;	  
				}
			break;
			}
		break;
		
		//E
		case 'E':
		switch(argv[1][1]){
		
			// E1
			case '1':
				switch(argv[2][0]){
				case '0':
				strcpy(code,"0001001101001101001101001101001001001101001101001101001101001001101101001001000");
				printf ("Outlet E1 is turned off\n");
				break;
				
				case '1':
				strcpy(code,"0001001101001101001101001101001001001101001101001101001101001001001001101101000");
				printf ("Outlet E1 is turned on\n");
				break;	  
				}
			break;
		
			// E2
			case '2':
			switch(argv[2][0]){
				case '0':
				strcpy(code,"0001001101001101001101001101001001001101001101001101001001001101101101001001000");
				printf ("Outlet E2 is turned off\n");
				break;
				
				case '1':
				strcpy(code,"0001001101001101001101001101001001001101001101001101001001001101001001101101000");
				printf ("Outlet E2 is turned on\n");
				break;	  
				}
			break;
			
			// E3
			case '3':
			switch(argv[2][0]){
				case '0':
				strcpy(code,"0001001101001101001101001101001001001101001101001001001101001101101101001001000");
				printf ("Outlet E3 is turned off\n");
				break;
				
				case '1':
				strcpy(code,"0001001101001101001101001101001001001101001101001001001101001101001001101101000");
				printf ("Outlet E3 is turned on\n");
				break;	  
				}
			break;
			
			// E4
			case '4':
			switch(argv[2][0]){
				case '0':
				strcpy(code,"0001001101001101001101001101001001001101001001001101001101001101101101001001000");
				printf ("Outlet E4 is turned off\n");
				break;
				
				case '1':
				strcpy(code,"0001001101001101001101001101001001001101001001001101001101001101001001101101000");
				printf ("Outlet E4 is turned on\n");
				break;	  
				}
			break;
			}
		break;
		
		//F
		case 'F':
		switch(argv[1][1]){
		
			// F1
			case '1':
				switch(argv[2][0]){
				case '0':
				strcpy(code,"0001001101001101001101001101001101001001001101001101001101001001101101001001000");
				printf ("Outlet F1 is turned off\n");
				break;
				
				case '1':
				strcpy(code,"0001001101001101001101001101001101001001001101001101001101001001001001101101000");
				printf ("Outlet F1 is turned on\n");
				break;	  
				}
			break;
		
			// F2
			case '2':
			switch(argv[2][0]){
				case '0':
				strcpy(code,"0001001101001101001101001101001101001001001101001101001001001101101101001001000");
				printf ("Outlet F2 is turned off\n");
				break;
				
				case '1':
				strcpy(code,"0001001101001101001101001101001101001001001101001101001001001101001001101101000");
				printf ("Outlet F2 is turned on\n");
				break;	  
				}
			break;
			
			// F3
			case '3':
			switch(argv[2][0]){
				case '0':
				strcpy(code,"0001001101001101001101001101001101001001001101001001001101001101101101001001000");
				printf ("Outlet F3 is turned off\n");
				break;
				
				case '1':
				strcpy(code,"0001001101001101001101001101001101001001001101001001001101001101001001101101000");
				printf ("Outlet F3 is turned on\n");
				break;	  
				}
			break;
			
			// F4
			case '4':
			switch(argv[2][0]){
				case '0':
				strcpy(code,"0001001101001101001101001101001101001001001001001101001101001101101101001001000");
				printf ("Outlet F4 is turned off\n");
				break;
				
				case '1':
				strcpy(code,"0001001101001101001101001101001101001001001001001101001101001101001001101101100");
				printf ("Outlet F4 is turned on\n");
				break;	  
				}
			break;
			}
		break;		
		}

		//Verify if arguments exists
		if (strlen(code) > 0)
		{
		// Set up gpio pointer for direct register access
		setup_io();

		// Switch GPIO to output mode
		INP_GPIO(transmitter); // must use INP_GPIO before we can use OUT_GPIO
		OUT_GPIO(transmitter);

        //Send Message
		SendCode(code);
		
		// Clear GPIO after sending the code
		GPIO_CLR = 1<<transmitter;
		return 0;
		}
		else
		{
			printf("You write an wrong argument\n");
			printf("Outlets are from A1 to F4\n");
			printf("Usage: scs_s3616 outlet_number on/off \n");
			printf("Exemple: scs_s3616 a1 1\n");
			return 1;
		}
	

	}
	else
	{
	printf("Not Enough Arguments\n");
	printf("Usage: scs_s3616 outlet_number on/off \n");
	printf("Exemple: scs_s3616 a1 1\n");
	return 1;
	}
	
	


} 

//
// Set up a memory regions to access GPIO
//
void setup_io()
{
	/* open /dev/mem */
	if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) 
	{
		printf("Can't open /dev/mem, try to execute this script as root \n");
		exit (-1);
	}

	/* mmap GPIO */
	// Allocate MAP block
	if ((gpio_mem = (unsigned char*)malloc(BLOCK_SIZE + (PAGE_SIZE-1))) == NULL) 
	{
		printf("Allocation error \n");
		exit (-1);
	}

	// Make sure pointer is on 4K boundary
	if ((unsigned long)gpio_mem % PAGE_SIZE)
	{
		gpio_mem += PAGE_SIZE - ((unsigned long)gpio_mem % PAGE_SIZE);
	}

	// Now map it
	gpio_map = (unsigned char *)mmap(
		(caddr_t)gpio_mem,
		BLOCK_SIZE,
		PROT_READ|PROT_WRITE,
		MAP_SHARED|MAP_FIXED,
		mem_fd,
		GPIO_BASE
		);

	if ((long)gpio_map < 0)
	{
		printf("mmap error %d\n", (int)gpio_map);
		exit (-1);
	}

	// Always use volatile pointer!
	gpio = (volatile unsigned *)gpio_map;
} // setup_io

//
// Function to send the output code to the RF transmitter
//
void SendCode(char* code)
{
	timespec sleeptime;
	timespec remtime;

	for (int repeater = 1 ; repeater <= 10 ; repeater++)
	{
		sleeptime.tv_sec = 0;
		sleeptime.tv_nsec = 550000; // Delay of SCS s3616 outlet
  
		for (int i = 1 ; i <= 79 ; i++)
		{
			if (code[i] == '1')
			{
				GPIO_SET = 1<<transmitter;
				//printf("1");
			}
			else
			{
				GPIO_CLR = 1<<transmitter;
				//printf("0");
			}
			nanosleep(&sleeptime,&remtime);
			
		}
		//printf("\n");
		sleeptime.tv_nsec = 1000000; //10ms This delay happens after the message was sent
		nanosleep(&sleeptime,&remtime);
	}
}


