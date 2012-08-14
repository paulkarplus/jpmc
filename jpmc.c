//     C:\ti\projects\.metadata\.plugins\org.eclipse.cdt.ui\Example_2806xCpuTimer.build.log
//###########################################################################
// Description:
//! \addtogroup f2806x_example_list
//! <h1>Cpu Timer (cpu_timer)</h1>
//!
//! This example configures CPU Timer0, 1, and 2 and increments
//! a counter each time the timer asserts an interrupt.
//!
//! \b Watch \b Variables \n
//! - CpuTimer0.InterruptCount
//! - CpuTimer1.InterruptCount
//! - CpuTimer2.InterruptCount
//
//###########################################################################
// $TI Release: F2806x C/C++ Header Files and Peripheral Examples V130 $
// $Release Date: November 30, 2011 $
//###########################################################################
#define REV "0.01"
#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include <string.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
#include "utils/cmdline.h"
#include "utils/uartstdio.h"


// Prototype statements for functions found within this file.
__interrupt void cpu_timer0_isr(void);
__interrupt void cpu_timer1_isr(void);
__interrupt void cpu_timer2_isr(void);
__interrupt void scia_rx_isr(void);
void init(void);



int
Cmd_help(int argc, char *argv[])
{
    tCmdLineEntry *pEntry;

    // Print some header text.
    UARTprintf("\nAvailable commands\n");
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


tCmdLineEntry g_sCmdTable[] =
{
    { "help",   Cmd_help,      " : Display list of commands" },
    { 0, 0, 0 }
};

extern int var=10;


void main(void)
{


	init();

  UARTprintf("JSPK Motor Controller\r\n");
  UARTprintf("Rev %s\r\n",REV);


  CmdLineProcess("help me!");
  Uint32 y = 195936478;
  UARTprintf("y = 0x%x\r\n",y);


// Step 6. IDLE loop. Just sit and loop forever (optional):
   for(;;);

}

void init(void)
{
	float Freq = 60;   // frequency of timer0 interrupt in Hz


	// Step 1. Initialize System Control:
	// PLL, WatchDog, enable Peripheral Clocks
	// This example function is found in the F2806x_SysCtrl.c file.
	   InitSysCtrl();


	// Step 2. Initalize GPIO:
	// This example function is found in the F2806x_Gpio.c file and
	// illustrates how to set the GPIO to it's default state.
	// InitGpio();  // Skipped for this example

	   InitSciaGpio();


	// Step 3. Clear all interrupts and initialize PIE vector table:
	// Disable CPU interrupts
	   DINT;

	// Initialize the PIE control registers to their default state.
	// The default state is all PIE interrupts disabled and flags
	// are cleared.
	// This function is found in the F2806x_PieCtrl.c file.
	   InitPieCtrl();

	// Disable CPU interrupts and clear all CPU interrupt flags:
	   IER = 0x0000;
	   IFR = 0x0000;

	// Initialize the PIE vector table with pointers to the shell Interrupt
	// Service Routines (ISR).
	// This will populate the entire table, even if the interrupt
	// is not used in this example.  This is useful for debug purposes.
	// The shell ISR routines are found in F2806x_DefaultIsr.c.
	// This function is found in F2806x_PieVect.c.
	   InitPieVectTable();

	// Interrupts that are used in this example are re-mapped to
	// ISR functions found within this file.
	   EALLOW;  // This is needed to write to EALLOW protected registers
	   PieVectTable.TINT0 = &cpu_timer0_isr;
	   PieVectTable.TINT1 = &cpu_timer1_isr;
	   PieVectTable.TINT2 = &cpu_timer2_isr;
	   //PieVectTable.SCIRXINTA = &scia_rx_isr;
//	   PieVectTable.SCIRXINTA = &UARTStdioIntHandler;
//	   PieVectTable.SCITXINTA = &UARTStdioIntHandler;

	   EDIS;    // This is needed to disable write to EALLOW protected registers

	// Step 4. Initialize the Device Peripheral. This function can be
	//         found in F2806x_CpuTimers.c
	   InitCpuTimers();   // For this example, only initialize the Cpu Timers

	// Configure CPU-Timer 0, 1, and 2 to interrupt every second:
	// 80MHz CPU Freq, 1 second Period (in uSeconds)

	   ConfigCpuTimer(&CpuTimer0, 80, 1.0/Freq*1000000.0);
	   ConfigCpuTimer(&CpuTimer1, 80, 1000000);
	   ConfigCpuTimer(&CpuTimer2, 80, 1000000);

	// To ensure precise timing, use write-only instructions to write to the entire register. Therefore, if any
	// of the configuration bits are changed in ConfigCpuTimer and InitCpuTimers (in F2806x_CpuTimers.h), the
	// below settings must also be updated.

	   CpuTimer0Regs.TCR.all = 0x4000; // Use write-only instruction to set TSS bit = 0 (starts timer) and TIE=1
	   CpuTimer1Regs.TCR.all = 0x4000; // Use write-only instruction to set TSS bit = 0 (starts timer) and TIE=1
	   CpuTimer2Regs.TCR.all = 0x4000; // Use write-only instruction to set TSS bit = 0 (starts timer) and TIE=1


	// Step 5. User specific code, enable interrupts:


	// Enable CPU int1 which is connected to CPU-Timer 0, CPU int13
	// which is connected to CPU-Timer 1, and CPU int 14, which is connected
	// to CPU-Timer 2:
	   IER |= M_INT1;   // enable group 1 interrupts
	   IER |= M_INT9;   // enable group 9 interrupts (scia rx and tx)
	   IER |= M_INT13;   // enable group 13 interrupts
	   IER |= M_INT14;   // enable group 14 interrupts

	// Enable TINT0 in the PIE: Group 1 interrupt 7
	   PieCtrlRegs.PIEIER1.bit.INTx7 = 1;


	// Enable SCIRXINTA in the PIE: Group 9 interrupt 1
	   PieCtrlRegs.PIEIER9.bit.INTx1 = 1;
	   PieCtrlRegs.PIEIER9.bit.INTx2 = 1;


	// Enable global Interrupts and higher priority real-time debug events:
	   EINT;   // Enable Global interrupt INTM
	   ERTM;   // Enable Global realtime interrupt DBGM

	// GPIO34 will go low inside each interrupt.  Monitor this on a scope
	  EALLOW;
	  GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;        // GPIO
	  GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;         // output
	  GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;	   // led off
	  EDIS;


	  //IntRegister(INT_SCIRXINTA, UARTStdioIntHandler);
	  UARTStdioInitExpClk(0,9600);

		// Enable SCIRXINTA in the PIE: Group 9 interrupt 1, do it again in case ti fucked it up
		   PieCtrlRegs.PIEIER9.bit.INTx1 = 1;
		   PieCtrlRegs.PIEIER9.bit.INTx2 = 1;
		   SciaRegs.SCIFFTX.bit.SCIFFENA = 0;
		   SciaRegs.SCIFFRX.bit.RXFFIENA = 1;
		   SciaRegs.SCIFFTX.bit.TXFFIENA = 1;
		   SciaRegs.SCICTL2.bit.TXINTENA = 1;
		   SciaRegs.SCICTL2.bit.RXBKINTENA = 1;


}


__interrupt void scia_rx_isr(void)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
	SciaRegs.SCIFFRX.bit.RXFFINTCLR = 1;
	SciaRegs.SCIFFRX.bit.RXFFOVRCLR = 1;

	UARTprintf("uart rx interrupt %\r\n");


	GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;

}
__interrupt void cpu_timer0_isr(void)
{
   CpuTimer0.InterruptCount++;
   UARTprintf("cpu_timer0_isr %u\r\n",CpuTimer0.InterruptCount);
   GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;


//   if(SciaRegs.SCIFFRX.bit.RXFFINT)
//	   UARTprintf("SciaRegs.SCIFFRX.bit.RXFFINT = 1\r\n");
//   else
//	   UARTprintf("SciaRegs.SCIFFRX.bit.RXFFINT = 0\r\n");
//
//
//   if(PieCtrlRegs.PIEIFR9.bit.INTx1)
//	   UARTprintf("PieCtrlRegs.PIEIFR9.bit.INTx1 = 1\r\n");
//   else
//	   UARTprintf("PieCtrlRegs.PIEIFR9.bit.INTx1 = 0\r\n");


   // Acknowledge this interrupt to receive more interrupts from group 1
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

__interrupt void cpu_timer1_isr(void)
{
   CpuTimer1.InterruptCount++;
   // The CPU acknowledges the interrupt.
   EDIS;
}

__interrupt void cpu_timer2_isr(void)
{  EALLOW;
   CpuTimer2.InterruptCount++;
   // The CPU acknowledges the interrupt.
   EDIS;
}


//===========================================================================
// No mas.
//===========================================================================
