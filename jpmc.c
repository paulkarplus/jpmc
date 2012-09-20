// JPMC
// Jut Shanahan, Paul Karplus Motor Controller
// Copyright: 2012
//###########################################################################
// Description: Piccolo Control Stick with F28069 Processor
//
// Rev		Date		Edited By		Revision Notes
// 0.01		8/15/2012	Jut				Initial rev. Basic serial command functionality working. Delete, printf, and several other things implemented.
// 0.02		8/15/2012	PK				Moved dispatch_console command to the SCIA rx interrupt. Added a command line function that blinks the LED on the controlStick. Cleaned up and commented code.
// 0.03		8/16/2012	Jut				Added command to set led blink frequency
// 0.04		8/18/2012	Jut				Added command to get value at any data memory location.  Added UART color defines.
// 0.05		9/20/2012	PK				Added command to get adc value from A0 channel. ADC conversion is forced and then the adc value is stored in an interrupt
//###########################################################################
#define REV "0.04"

#include "DSP28x_Project.h"     	   // Device Headerfile and Examples Include File
#include <string.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
#include "utils/cmdline.h"
#include "console.h"
#include "utils/uartstdio.h"
#include "uartcolors.h"


#include "F2806x_Adc.h"                // ADC Registers
#include "F2806x_BootVars.h"           // Boot ROM Variables
#include "F2806x_DevEmu.h"             // Device Emulation Registers
#include "F2806x_Cla.h"                // Control Law Accelerator Registers
#include "F2806x_Comp.h"               // Comparator Registers
#include "F2806x_CpuTimers.h"          // 32-bit CPU Timers
#include "F2806x_ECan.h"               // Enhanced eCAN Registers
#include "F2806x_ECap.h"               // Enhanced Capture
#include "F2806x_EPwm.h"               // Enhanced PWM
#include "F2806x_EQep.h"               // Enhanced QEP
#include "F2806x_Gpio.h"               // General Purpose I/O Registers
#include "F2806x_I2c.h"                // I2C Registers
#include "F2806x_NmiIntrupt.h"         // NMI Interrupt Registers
#include "F2806x_PieCtrl.h"            // PIE Control Registers
#include "F2806x_PieVect.h"            // PIE Vector Table
#include "F2806x_Spi.h"                // SPI Registers
#include "F2806x_Sci.h"                // SCI Registers
#include "F2806x_SysCtrl.h"            // System Control/Power Modes
#include "F2806x_XIntrupt.h"           // External Interrupts

// Prototype statements for functions found within this file.
__interrupt void cpu_timer0_isr(void);
__interrupt void cpu_timer1_isr(void);
__interrupt void cpu_timer2_isr(void);
__interrupt void scia_rx_isr(void);					// sci receive interrupt function
__interrupt void adc_isr(void);
void init(void);
void Adc_Config(void);

// Initialize global variables for this file
float Freq = 1;   // frequency of timer0 interrupt in Hz
unsigned long adc = 0;

void main(void)
{
	init();			// Sets up the sci and GPIO registers

	// Print bootup message containing device title and revision number
	UARTprintf("\r\n");
	UARTprintf(BOLDCYAN);
	UARTprintf("JSPK Motor Controller\r\n");
	UARTprintf("Rev %s\r\n",REV);
	UARTprintf(restore);

//	UARTprintf("\033[36mJSPK Motor Controller\033[37m\r\n");
//	UARTprintf("\033[36mRev %s\033[37m\r\n",REV);
	CmdLineProcess("help");
	UARTprintf("> ");

	// Infinite loop.
   while(1){}
}

// Initial setup of all registers
void init(void)
{
	// Initialize System Control:
	// PLL, WatchDog, enable Peripheral Clocks
	InitSysCtrl();

	// Initialize Sci GPIO
	InitSciaGpio();

	// Clear all interupts and initialize PIE vector table. Disable CPU interrupts
	DINT;

	// Disable CPU interrupts and clear all CPU interrupt flags:
	IER = 0x0000;
	IFR = 0x0000;

	// Initialize the PIE control registers to their default state.
	// The default state is all PIE interrupts disabled and flags
	// are cleared.
	InitPieCtrl();

	// Initialize the PIE vector table with pointers to the shell Interrupt
	// Service Routines (ISR).
	// This will populate the entire table, even if the interrupt
	// is not used in this example.  This is useful for debug purposes.
	// The shell ISR routines are found in F2806x_DefaultIsr.c.
	// This function is found in F2806x_PieVect.c.
	InitPieVectTable();

	// Interrupts that are used in this file are re-mapped to
	// ISR functions found within this file.
	EALLOW;  // This is needed to write to EALLOW protected registers
	PieVectTable.TINT0 = &cpu_timer0_isr;
	PieVectTable.TINT1 = &cpu_timer1_isr;
	PieVectTable.TINT2 = &cpu_timer2_isr;
	PieVectTable.SCIRXINTA = &scia_rx_isr;		// SciA rx interrupt
	PieVectTable.ADCINT1 = &adc_isr;
	EDIS;    // This is needed to disable write to EALLOW protected registers



	// Step 4. Initialize the Device Peripheral.
	InitCpuTimers();   // For this file, only initialize the Cpu Timers
	InitAdc();  // For this example, init the ADC

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

	// Enable CPU int1 which is connected to CPU-Timer 0, CPU int 9 which is connected to SCIA_rx and SCIA_tx, CPU int13
	// which is connected to CPU-Timer 1, and CPU int 14, which is connected
	// to CPU-Timer 2:
	IER |= M_INT1;    // enable group 1 interrupts
	IER |= M_INT9;    // enable group 9 interrupts (scia rx and tx)
	IER |= M_INT13;   // enable group 13 interrupts
	IER |= M_INT14;   // enable group 14 interrupts

	// Enable individual PIE Table interrupts
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;		// Enable TINT0 in the PIE: Group 1 interrupt 7
    PieCtrlRegs.PIEIER9.bit.INTx1 = 1;		// Enable SCIRXINTA in the PIE: Group 9 interrupt 1
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;		// Enable INT 1.1 in the PIE

	// Enable global Interrupts and higher priority real-time debug events:
	EINT;   // Enable Global interrupt INTM
	ERTM;   // Enable Global realtime interrupt DBGM

	// Intialize UART(INT_SCIRXINTA, UARTStdioIntHandler);
	UARTStdioInitExpClk(0,115200);

	// Enable Sci tx and rx interupts within Sci control register
	SciaRegs.SCICTL2.bit.TXINTENA = 1;
	SciaRegs.SCICTL2.bit.RXBKINTENA = 1;

	// Configure ADC
	Adc_Config();

	// Setup LED on GPIO-34 for Sci blink command. LED is toggled by blink command is sent.
	EALLOW;
	GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;	// 0=GPIO,  1=COMP2OUT,  2=EMU1,  3=Resv
	GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;		// 1=OUTput,  0=INput
	GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;	// uncomment if --> Set Low initially
	//GpioDataRegs.GPBSET.bit.GPIO34 = 1;	// uncomment if --> Set High initially
	EDIS;
}

void Adc_Config(void)
{
	// Configure ADC
		EALLOW;
		AdcRegs.ADCCTL2.bit.ADCNONOVERLAP = 1;	// Enable non-overlap mode
		AdcRegs.ADCCTL1.bit.INTPULSEPOS	= 1;	// ADCINT1 trips after AdcResults latch
		AdcRegs.INTSEL1N2.bit.INT1E     = 1;	// Enabled ADCINT1
		AdcRegs.INTSEL1N2.bit.INT1CONT  = 0;	// Disable ADCINT1 Continuous mode
		AdcRegs.INTSEL1N2.bit.INT1SEL 	= 1;    // setup EOC1 to trigger ADCINT1 to fire
		AdcRegs.ADCSOC1CTL.bit.CHSEL 	= 0;    // set SOC1 channel select to ADCINA2
		AdcRegs.ADCSOC1CTL.bit.TRIGSEL 	= 0;    // set SOC1 start trigger on EPWM1A, due to round-robin SOC0 converts first then SOC1
		AdcRegs.ADCSOC1CTL.bit.ACQPS 	= 10;	// set SOC1 S/H Window to 11 ADC Clock Cycles, (10 ACQPS plus 1)
		EDIS;
/*	// Configure ADC
	EALLOW;
	AdcRegs.ADCCTL2.bit.ADCNONOVERLAP = 1;	// Enable non-overlap mode
	AdcRegs.ADCCTL1.bit.INTPULSEPOS	= 1;	// ADCINT1 trips after AdcResults latch
	AdcRegs.INTSEL1N2.bit.INT1E     = 1;	// Enabled ADCINT1
	AdcRegs.INTSEL1N2.bit.INT1CONT  = 0;	// Disable ADCINT1 Continuous mode
	AdcRegs.INTSEL1N2.bit.INT1SEL 	= 1;    // setup EOC1 to trigger ADCINT1 to fire
	AdcRegs.ADCSOC0CTL.bit.CHSEL 	= 0;    // set SOC0 channel to A0
	AdcRegs.ADCSOC0CTL.bit.TRIGSEL 	= 0;    // set SOC0 will trigger only on software
	AdcRegs.ADCSOC0CTL.bit.ACQPS 	= 10;	// set SOC0 S/H Window to 11 ADC Clock Cycles, (10 ACQPS plus 1)
	EDIS;
*/
}
// ADC interrupt function
__interrupt void  adc_isr(void)
{

  adc = AdcResult.ADCRESULT1;
  UARTprintf("ADC Value = %u\r\n",adc);

  AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;		//Clear ADCINT1 flag reinitialize for next SOC
  PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE

  return;
}
// Sci rx interrupt function.
__interrupt void scia_rx_isr(void)
{
	dispatch_console();							// Processes the received data.
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;		// Acknowledges the PIE group so that another interrupt can occur
	//SciaRegs.SCIFFRX.bit.RXFFINTCLR = 1;		// (PK) I tried commenting this out and it did not affect performance. So it must not be necessary.
	//SciaRegs.SCIFFRX.bit.RXFFOVRCLR = 1;		// (PK) I tried commenting this out and it did not affect performance. So it must not be necessary.
}
__interrupt void cpu_timer0_isr(void)
{
   CpuTimer0.InterruptCount++;
//   UARTprintf("cpu_timer0_isr %u\r\n",CpuTimer0.InterruptCount);
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
//
//===========================================================================
