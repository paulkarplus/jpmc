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
#include "F2806x_EPwm.h"               // Enhanced PWM
#include "F2806x_Adc.h"                // ADC Registers
#include "math.h"
#include "stdlib.h"

#define MAX_COMMAND_LENGTH	32
#define COMMAND_BUFFER_LENGTH 5
//#define DEBUG

extern float Freq;   // frequency of timer0 interrupt in Hz
extern int32 current;
extern unsigned long adc;
extern float Dead_Time_ns;
extern float PWM_Freq;		// PWM Frequency in kHz
extern float PWM_Duty_Cycle;	// PWM Duty Cycle
extern char Sine_PWM;
extern char hall_PWM;
extern float Sine_Freq; 		// Sine PWM Frequency in Hz
extern float Sine_Mag;



//char* Command_Buffer[COMMAND_BUFFER_LENGTH + 1] = {0};
//int Buffer_Pointer = 0;

void btoa(char *string, unsigned int var);      // convert 16bit variable into a string

int Cmd_Get_PWM_Regs(int argc,char *argv[])
{
	char string[16]={0};
	volatile unsigned long *ptr, x, y;
	volatile unsigned short *addr;
	volatile Uint32 *addr2;

	EPwm1Regs.TBCTL.bit.CTRMODE=0;


	addr = &(EPwm1Regs.TBCTL.all);   btoa(string,EPwm1Regs.TBCTL.all);	UARTprintf("TBCTL (0x%x) = \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.TBCTL.all,(Uint32)EPwm1Regs.TBCTL.all);
	addr = &(EPwm1Regs.TBSTS.all);	btoa(string,EPwm1Regs.TBSTS.all);	UARTprintf("TBSTS = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.TBSTS.all,(Uint32)EPwm1Regs.TBSTS.all);
	addr2 = &(EPwm1Regs.TBPHS.all);	btoa(string,EPwm1Regs.TBPHS.all);	UARTprintf("TBPHS = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr2,string,(Uint32)EPwm1Regs.TBPHS.all,(Uint32)EPwm1Regs.TBPHS.all);
	addr = &(EPwm1Regs.TBCTR);	btoa(string,EPwm1Regs.TBCTR);	UARTprintf("TBCTR = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.TBCTR,(Uint32)EPwm1Regs.TBCTR);
	addr = &(EPwm1Regs.TBPRD);	btoa(string,EPwm1Regs.TBPRD);	UARTprintf("TBPRD = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.TBPRD,(Uint32)EPwm1Regs.TBPRD);
	addr = &(EPwm1Regs.TBPRDHR);	btoa(string,EPwm1Regs.TBPRDHR);	UARTprintf("TBPRDHR = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.TBPRDHR,(Uint32)EPwm1Regs.TBPRDHR);
	addr = &(EPwm1Regs.CMPCTL.all);	btoa(string,EPwm1Regs.CMPCTL.all);	UARTprintf("CMPCTL = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.CMPCTL.all,(Uint32)EPwm1Regs.CMPCTL.all);
	addr2 = &(EPwm1Regs.CMPA.all);	btoa(string,EPwm1Regs.CMPA.all);	UARTprintf("CMPA = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr2,string,(Uint32)EPwm1Regs.CMPA.all,(Uint32)EPwm1Regs.CMPA.all);
	addr = &(EPwm1Regs.CMPB);	btoa(string,EPwm1Regs.CMPB);	UARTprintf("CMPB = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.CMPB,(Uint32)EPwm1Regs.CMPB);
	addr = &(EPwm1Regs.AQCTLA.all);	btoa(string,EPwm1Regs.AQCTLA.all);	UARTprintf("AQCTLA = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.AQCTLA.all,(Uint32)EPwm1Regs.AQCTLA.all);
	addr = &(EPwm1Regs.AQCTLB.all);	btoa(string,EPwm1Regs.AQCTLB.all);	UARTprintf("AQCTLB = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.AQCTLB.all,(Uint32)EPwm1Regs.AQCTLB.all);
	addr = &(EPwm1Regs.AQSFRC.all);	btoa(string,EPwm1Regs.AQSFRC.all);	UARTprintf("AQSFRC = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.AQSFRC.all,(Uint32)EPwm1Regs.AQSFRC.all);
	addr = &(EPwm1Regs.AQCSFRC.all);	btoa(string,EPwm1Regs.AQCSFRC.all);	UARTprintf("AQCSFRC = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.AQCSFRC.all,(Uint32)EPwm1Regs.AQCSFRC.all);
	addr = &(EPwm1Regs.DBCTL.all);	btoa(string,EPwm1Regs.DBCTL.all);	UARTprintf("DBCTL = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.DBCTL.all,(Uint32)EPwm1Regs.DBCTL.all);
	addr = &(EPwm1Regs.DBRED);	btoa(string,EPwm1Regs.DBRED);	UARTprintf("DBRED = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.DBRED,(Uint32)EPwm1Regs.DBRED);
	addr = &(EPwm1Regs.DBFED);	btoa(string,EPwm1Regs.DBFED);	UARTprintf("DBFED = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.DBFED,(Uint32)EPwm1Regs.DBFED);
	addr = &(EPwm1Regs.TZSEL.all);	btoa(string,EPwm1Regs.TZSEL.all);	UARTprintf("TZSEL = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.TZSEL.all,(Uint32)EPwm1Regs.TZSEL.all);
	addr = &(EPwm1Regs.TZDCSEL.all);	btoa(string,EPwm1Regs.TZDCSEL.all);	UARTprintf("TZDCSEL = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.TZDCSEL.all,(Uint32)EPwm1Regs.TZDCSEL.all);
	addr = &(EPwm1Regs.TZCTL.all);	btoa(string,EPwm1Regs.TZCTL.all);	UARTprintf("TZCTL = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.TZCTL.all,(Uint32)EPwm1Regs.TZCTL.all);
	addr = &(EPwm1Regs.TZEINT.all);	btoa(string,EPwm1Regs.TZEINT.all);	UARTprintf("TZEINT = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.TZEINT.all,(Uint32)EPwm1Regs.TZEINT.all);
	addr = &(EPwm1Regs.TZFLG.all);	btoa(string,EPwm1Regs.TZFLG.all);	UARTprintf("TZFLG = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.TZFLG.all,(Uint32)EPwm1Regs.TZFLG.all);
	addr = &(EPwm1Regs.TZCLR.all);	btoa(string,EPwm1Regs.TZCLR.all);	UARTprintf("TZCLR = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.TZCLR.all,(Uint32)EPwm1Regs.TZCLR.all);
	addr = &(EPwm1Regs.TZFRC.all);	btoa(string,EPwm1Regs.TZFRC.all);	UARTprintf("TZFRC = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.TZFRC.all,(Uint32)EPwm1Regs.TZFRC.all);
	addr = &(EPwm1Regs.ETSEL.all);	btoa(string,EPwm1Regs.ETSEL.all);	UARTprintf("ETSEL = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.ETSEL.all,(Uint32)EPwm1Regs.ETSEL.all);
	addr = &(EPwm1Regs.ETPS.all);	btoa(string,EPwm1Regs.ETPS.all);	UARTprintf("ETPS = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.ETPS.all,(Uint32)EPwm1Regs.ETPS.all);
	addr = &(EPwm1Regs.ETFLG.all);	btoa(string,EPwm1Regs.ETFLG.all);	UARTprintf("ETFLG = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.ETFLG.all,(Uint32)EPwm1Regs.ETFLG.all);
	addr = &(EPwm1Regs.ETCLR.all);	btoa(string,EPwm1Regs.ETCLR.all);	UARTprintf("ETCLR = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.ETCLR.all,(Uint32)EPwm1Regs.ETCLR.all);
	addr = &(EPwm1Regs.ETFRC.all);	btoa(string,EPwm1Regs.ETFRC.all);	UARTprintf("ETFRC = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.ETFRC.all,(Uint32)EPwm1Regs.ETFRC.all);
	addr = &(EPwm1Regs.PCCTL.all);	btoa(string,EPwm1Regs.PCCTL.all);	UARTprintf("PCCTL = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.PCCTL.all,(Uint32)EPwm1Regs.PCCTL.all);
	addr = &(EPwm1Regs.HRCNFG.all);	btoa(string,EPwm1Regs.HRCNFG.all);	UARTprintf("HRCNFG = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.HRCNFG.all,(Uint32)EPwm1Regs.HRCNFG.all);
	//addr = &(EPwm1Regs.HRPWR.all);	btoa(string,EPwm1Regs.HRPWR);	UARTprintf("HRPWR = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.HRPWR,(Uint32)EPwm1Regs.HRPWR);
	//addr = &(EPwm1Regs.HRMSTEP.all);	btoa(string,EPwm1Regs.HRMSTEP);	UARTprintf("HRMSTEP = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.HRMSTEP,(Uint32)EPwm1Regs.HRMSTEP);
	addr = &(EPwm1Regs.HRPCTL.all);	btoa(string,EPwm1Regs.HRPCTL.all);	UARTprintf("HRPCTL = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.HRPCTL.all,(Uint32)EPwm1Regs.HRPCTL.all);
	addr2 = &(EPwm1Regs.TBPRDM.all);	btoa(string,EPwm1Regs.TBPRDM.all);	UARTprintf("TBPRDM = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr2,string,(Uint32)EPwm1Regs.TBPRDM.all,(Uint32)EPwm1Regs.TBPRDM.all);
	addr2 = &(EPwm1Regs.CMPAM.all);	btoa(string,EPwm1Regs.CMPAM.all);	UARTprintf("CMPAM = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr2,string,(Uint32)EPwm1Regs.CMPAM.all,(Uint32)EPwm1Regs.CMPAM.all);
	addr = &(EPwm1Regs.DCTRIPSEL.all);	btoa(string,EPwm1Regs.DCTRIPSEL.all);	UARTprintf("DCTRIPSEL = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.DCTRIPSEL.all,(Uint32)EPwm1Regs.DCTRIPSEL.all);
	addr = &(EPwm1Regs.DCACTL.all);	btoa(string,EPwm1Regs.DCACTL.all);	UARTprintf("DCACTL = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.DCACTL.all,(Uint32)EPwm1Regs.DCACTL.all);
	addr = &(EPwm1Regs.DCBCTL.all);	btoa(string,EPwm1Regs.DCBCTL.all);	UARTprintf("DCBCTL = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.DCBCTL.all,(Uint32)EPwm1Regs.DCBCTL.all);
	addr = &(EPwm1Regs.DCFCTL.all);	btoa(string,EPwm1Regs.DCFCTL.all);	UARTprintf("DCFCTL = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.DCFCTL.all,(Uint32)EPwm1Regs.DCFCTL.all);
	addr = &(EPwm1Regs.DCCAPCTL.all);	btoa(string,EPwm1Regs.DCCAPCTL.all);	UARTprintf("DCCAPCTL = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.DCCAPCTL.all,(Uint32)EPwm1Regs.DCCAPCTL.all);
	addr = &(EPwm1Regs.DCFOFFSET);	btoa(string,EPwm1Regs.DCFOFFSET);	UARTprintf("DCFOFFSET = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.DCFOFFSET,(Uint32)EPwm1Regs.DCFOFFSET);
	addr = &(EPwm1Regs.DCFOFFSETCNT);	btoa(string,EPwm1Regs.DCFOFFSETCNT);	UARTprintf("DCFOFFSETCNT = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.DCFOFFSETCNT,(Uint32)EPwm1Regs.DCFOFFSETCNT);
	addr = &(EPwm1Regs.DCFWINDOW);	btoa(string,EPwm1Regs.DCFWINDOW);	UARTprintf("DCFWINDOW = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.DCFWINDOW,(Uint32)EPwm1Regs.DCFWINDOW);
	addr = &(EPwm1Regs.DCFWINDOWCNT);	btoa(string,EPwm1Regs.DCFWINDOWCNT);	UARTprintf("DCFWINDOWCNT = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.DCFWINDOWCNT,(Uint32)EPwm1Regs.DCFWINDOWCNT);
	addr = &(EPwm1Regs.DCCAP);	btoa(string,EPwm1Regs.DCCAP);	UARTprintf("DCCAP = (0x%x) \t%s.b = %u = 0x%x\r\n",(Uint32)addr,string,(Uint32)EPwm1Regs.DCCAP,(Uint32)EPwm1Regs.DCCAP);



	return 1;
}

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
    while(pEntry->pcCmd != 0)
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

int Cmd_trigger_adc(int argc,char *argv[])
{
	UARTprintf("ADC Triggered!\r\n");
	UARTprintf("ADC Value = %u\r\n",current);
	return 0;
}

int Cmd_sine(int argC,char *argv[])
{
	double angle = atof(argv[1]);
	UARTprintf("angle is : %u\r\n",(unsigned long)(angle*1000));
	double sine_angle = sin(angle);
	UARTprintf("sine of %u is : %u\r\n",(unsigned long)(angle*1000), (unsigned long)(sine_angle*1000));
}
int Cmd_deadtime(int argc,char *argv[])
{
	Dead_Time_ns = atof(argv[1]);
	if (Dead_Time_ns > 300) Dead_Time_ns = 300;
	if (Dead_Time_ns < 50) Dead_Time_ns = 50;
	UARTprintf("Deadtime set!\r\n");
	return 0;
}
int Cmd_dutycycle(int argc,char *argv[])
{
	PWM_Duty_Cycle = atof(argv[1])/100;
	if (PWM_Duty_Cycle > 1) PWM_Duty_Cycle = 1;
	if (PWM_Duty_Cycle < 0) PWM_Duty_Cycle = 0;
	UARTprintf("Duty Cycle set!\r\n");
	return 0;
}
int Cmd_pwmfreq(int argc,char *argv[])
{
	PWM_Freq = atof(argv[1]);
	if (PWM_Freq > 100) PWM_Freq = 100;
	if (PWM_Freq < 1) PWM_Freq = 1;
	UARTprintf("PWM frequency set!\r\n");
	return 0;
}
int Cmd_sinepwm(int argc,char *argv[])
{
	if (Sine_PWM == 0)
	{
		Sine_PWM = 1;
		UARTprintf("Sine PWM On!\r\n");
	} else {
		if (Sine_PWM == 1)
			{
				Sine_PWM = 0;
				UARTprintf("Sine PWM Off!\r\n");
			}
	}

	return 0;
}
int Cmd_sinefreq(int argc,char *argv[])
{
	Sine_Freq = atof(argv[1]);
	if (Sine_Freq > 10000) Sine_Freq = 10000;   // Frequency in Hz
	if (Sine_Freq < 0) Sine_Freq = 0;
	UARTprintf("Sine frequency set!\r\n");
	return 0;
}
int Cmd_sinemag(int argc,char *argv[])
{
	Sine_Mag = atof(argv[1]);
	if (Sine_Mag > 1) Sine_Mag = 1;   // Magnitude of PWM Sine Wave from 0-1
	if (Sine_Mag < 0) Sine_Mag = 0;
	UARTprintf("Sine magnitude set!\r\n");
	return 0;
}
int Cmd_hallpwm(int argc,char *argv[])
{
	if (hall_PWM == 0)
	{
		hall_PWM = 1;
		UARTprintf("hall PWM On!\r\n");
	} else {
		if (hall_PWM == 1)
			{
				hall_PWM = 0;
				UARTprintf("hall PWM Off!\r\n");
			}
	}

	return 0;
}
tCmdLineEntry g_sCmdTable[] =
{
	{"help",	Cmd_help,			" : Display list of commands"},
    {"blink",	Cmd_blink,			" : Blink the LED"},
    {"ledf",	Cmd_LED_Freq,		" : Set LED blinking frequency"},
    {"gr",		Cmd_Get_Reg,		" : Get Register"},
    {"gp",		Cmd_Get_PWM_Regs,	" : Print PWM Registers"},
    {"adc",		Cmd_trigger_adc,	" : Trigger SOC for ADC A0"},
    {"sine",	Cmd_sine,			" : Take the sine of a float"},
    {"dt",      Cmd_deadtime,       " : Set the deadtime in ns"},
    {"dc",      Cmd_dutycycle,      " : Set the PWM duty cycle"},
    {"pwmfreq", Cmd_pwmfreq,        " : Set the PWM frequency"},
    {"sinepwm", Cmd_sinepwm,        " : Set the PWM to output a sine function"},
    {"sinefreq",Cmd_sinefreq,       " : Set the frequency of the PWM sine function"},
    {"sinemag", Cmd_sinemag,        " : Set the magnitude of the PWM sine function (0-1)"},
    {"hallpwm", Cmd_hallpwm,        " : Set the PWM to sync with hall signals"},
    {0,0,0}
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
		CmdLineProcess(command);
		// Failed Buffering Routine PK 9.26.2012. Problem was that it would just copy the pointer location over and over again
		/*if (Buffer_Pointer > COMMAND_BUFFER_LENGTH) {
			unsigned int i;
			for (i = 0; i < COMMAND_BUFFER_LENGTH; i++)
			{
				Command_Buffer[i] = Command_Buffer[i+1];
			}
			Buffer_Pointer = COMMAND_BUFFER_LENGTH;
		}
		char *last_command = command;
		Command_Buffer[Buffer_Pointer] = command;
		Buffer_Pointer++;
		*/
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
