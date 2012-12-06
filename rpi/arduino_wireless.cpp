// g++ -o transmit transmit.cpp
// Rpi to Arduino Wireless Trasmitter by Sarrailh Remi.
// Based on the example GPIO in C program by Dom and Gert.
// Based on the RC Mains socket control program by Goeff Johnson

// Access from ARM Running Linux

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

#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)

int  mem_fd;
unsigned char *gpio_mem, *gpio_map;
char *spi0_mem, *spi0_map;

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
void SendCode(char* szCode, int number);

int main(int argc, char **argv)
{ 
	int g,rep;
	int send_numbers;

		// Set up gpi pointer for direct register access
		setup_io();

		// Switch GPIO 7 to output mode
		INP_GPIO(7); // must use INP_GPIO before we can use OUT_GPIO
		OUT_GPIO(7);

		char szOn[500] = {0};

        //Send Message put in arguments ex: switch "11110010101010"

		strcpy(szOn, "11111111");
		send_numbers = atol (argv[1]);
		send_numbers = send_numbers * 10 + 15;
		SendCode(szOn,send_numbers);
                //I noticed the Rpi tends to continue to send 111111 after the end of the code so I clear the GPIO before the ends
		GPIO_CLR = 1<<7;
	return 0;
} // main

//
// Set up a memory regions to access GPIO
//
void setup_io()
{
	/* open /dev/mem */
	if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) 
	{
		printf("Can't open /dev/mem \n");
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

// Function to send the output code to the RF transmitter connected to GPIO 7.
void SendCode(char* szCode, int number)
{
	timespec sleeptime;
	timespec remtime;

	for (int iSend = 1 ; iSend <= number; iSend++)
	{
		sleeptime.tv_sec = 0;
	 	sleeptime.tv_nsec = 1000000; // 1ms : Value on the Arduino Code you can change it to try.
	                        
		for (int i = 0 ; i < strlen(szCode) ; i++)
		{
			if (szCode[i] == '1')
			{
				GPIO_SET = 1<<7;
			}
			else
			{
				GPIO_CLR = 1<<7;
			}
			nanosleep(&sleeptime,&remtime);
		}
		
		//sleeptime.tv_nsec = 10000000; //10ms This delay happens after the message was sent
		//nanosleep(&sleeptime,&remtime);
	}
}
