#ifndef FCY
#define FCY 10000000		// 10.000000 MHz
#endif

#include "console.h"
#include "F2806x_Cla_typedefs.h"// F2806x CLA Type definitions
#include <string.h>
#include <stdlib.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_uart.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"
#include "utils/cmdline.h"
#include "utils/uartstdio.h"
#include "F2806x_Gpio.h"               // General Purpose I/O Registers
#include "F2806x_CpuTimers.h"          // 32-bit CPU Timers


#define MAX_COMMAND_LENGTH	32
//#define DEBUG

extern float Freq;   // frequency of timer0 interrupt in Hz


void btoa(char *string, unsigned int var);      // convert 16bit variable into a string

int Cmd_LED_Freq(int argc,char *argv[])
{

	Freq = atof(argv[1]);     // convert first element in argument vector (array of strings) to a float using ascii to float function
	if(Freq >= 0)
	{
		ConfigCpuTimer(&CpuTimer0, 80, 1.0/Freq*1000000.0);
		CpuTimer0Regs.TCR.all = 0x4000; // Use write-only instruction to set TSS bit = 0 (starts timer) and TIE=1
		UARTprintf("blink frequency set to %u Hz\r\n",(long)Freq);
	}
	else
	{
		UARTprintf("invalid frequency\r\n",(long)Freq);
	}


	return 0;
}

int Cmd_blink(int argc,char *argv[])
{
	GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
	UARTprintf("Blink!!!\r\n");
	return 0;
}


int Cmd_help(int argc, char *argv[])
{
    tCmdLineEntry *pEntry;

    // Print some header text.
//    printf("\a\033[31munknown register\033[37m\r\n");          //     \a=beep
    UARTprintf("Available commands\n");
    UARTprintf("------------------\n");
    // Point at the beginning of the command table.
    pEntry = &g_sCmdTable[0];

    // Enter a loop to read each entry from the command table.  The end of the
    // table has been reached when the command name is NULL.
    while(pEntry->pcCmd)
    {
        // Print the command name and the brief description.
        UARTprintf("%s%s\n", pEntry->pcCmd, pEntry->pcHelp);

        // Advance to the next entry in the table.
        pEntry++;
    }

    // Return success.
    return(0);
}

int Cmd_Get_Reg(int argc, char *argv[])
{
	char string[16]={0};
	volatile unsigned long *ptr, x, y;

	x = (unsigned long)(strtol(argv[1], 0, 16));   // "strtol" converts the string into a long integer
	UARTprintf("address requested = 0x%x\r\n",x);
	ptr = (unsigned long *)x;
	y = *ptr;
	btoa(string,y);
	UARTprintf("%s.b = %u = 0x%x\r\n",string,(Uint32)((Uint16)y),(Uint32)((Uint16)y));
//	UARTprintf("partid = 0x%x\r\n",*(unsigned long *)(0x883));


	return 1;

}
//
//char sr(char *arg)
//{
//	char *token, strSFR[10]={0}, strval[10]={0}, *end;
//	unsigned int addr, val, *ptr, y;
//	unsigned long x;
//
//	token = strtok(arg," ");
//	strcpy(strSFR,token);
//
//	if(strSFR[0]=='0' && strSFR[1]=='x')
//	{
//		x = strtol(strSFR, &end, 0);
//		y = (unsigned int)x;
//		addr = (unsigned int)x;
//	}
//	else
//	{
//		if(!reglookup(&addr,strSFR))   // addr = address of SFR
//		{
//			printf("\a\033[31munknown register\033[37m\r\n");
//			return 0;
//		}
//	}
//
//	token = strtok(NULL," ");
//	strcpy(strval,token);
//	x = strtol(strval, &end, 0);
//	val = (unsigned int)x;
//
//	ptr = (unsigned int *)addr;
//	*ptr = val;
//
//	return 1;
//}


tCmdLineEntry g_sCmdTable[] =
{
    { "help",   Cmd_help,      " : Display list of commands" },
    { "blink",  Cmd_blink,     " : Blink the LED"},
    { "ledf",  Cmd_LED_Freq,   " : Set LED blinking frequency"},
    { "gr",    Cmd_Get_Reg,    " : Get Register"},
    { 0, 0, 0 }
};


char get_command(char *command, int maxlength);
//char gr(char *);
//char sr(char *);



char misc(char *arg)
{
//	printf("doing misc things\r\n");

	return 1;
	
}


void dispatch_console(void)
{
	static char command[MAX_COMMAND_LENGTH] = {0};		// MAX_COMMAND_LENGTH = 32
	static char lastcmd[MAX_COMMAND_LENGTH] = {0};		// MAX_COMMAND_LENGTH = 32
	static char init = 1;
	int length = strlen(command);
	//printf("length = %d\r\n",length);
	
	if(init == 0)
	{
		CmdLineProcess("help");
		UARTprintf("> ");
		init = 1;
	}
	
	if(get_command(command+length, MAX_COMMAND_LENGTH-length) == 0)
	{
//		strcpy(lastcmd,command);
//		UARTprintf("command rxed:%s\r\n",command);
		CmdLineProcess(command);
		memset(command, 0, sizeof(command));
		UARTprintf("> ");
	}
}

char get_command(char *command, int maxlength)
{
	char input=0;
	long length=0;

	if(UARTCharsAvail(UART0_BASE) == 0)
	{
		//UARTprintf("no chars available :( \r\n");
		return 1;
	}
	else
	{
		input = UARTCharGetNonBlocking(UART0_BASE);
//		UARTprintf("length=%u\r\n",length);
	}

	
	while(input != '\r' && input != '\n')
	{
		if(input == 0x7F)  // backspace
		{
			//U1TXREG = input;
			UARTCharPutNonBlocking(UART0_BASE, (unsigned char)(input));
			//UARTprintf("backspace");
			//printf("%c", input);
			command--;
			*command = 0;			// set previous input char = NULL character
			command++;
			return 1;
		}
		
		
		*command = input;
		//UARTprintf("%c", *command++);
		UARTCharPutNonBlocking(UART0_BASE, *command++);
		if(++length == maxlength - 1)
			break;
		
		if(UARTCharsAvail(UART0_BASE)==0)
			return 1;
		else
			input=UARTCharGetNonBlocking(UART0_BASE);
	
	}
	UARTprintf("\n");
	
	return 0;
}


// convert 16bit variable into a string
void btoa(char *string, unsigned int var)
{

	unsigned int x=0, i=0;

	// initialize array to all
	for(i=0; i<16; i++)
		string[i] = 48;				// Decimal 48 is equivalent to the ascii char "0"

	string[16] = 0;					// the last char in the char array must be a 0

	for(i=0; i<17; i++)
	{
		x = var << i;				// shift var to the left
		x = x & 0x8000;				// zero out bits 0 - 14, leave bit 15 intact
		if(x == 0x8000)				// is bit 15 set?
			string[i] = 49;			// Decimal 49 is equivalent to the ascii char "1"

		x = 0;
	}

}
