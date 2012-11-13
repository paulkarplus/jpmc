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
// 0.06		9/26/2012	PK				Added command to set deadtime, dutycycle, and freq for ePWM1. Also made a sinePWM command that turns on sine wave generation. sinefreq adjusts the frequency of the sine wave and sinemag adjusts the magnitude.
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
#include "math.h"


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
__interrupt void epwm1_timer_isr(void);

void InitEPwm(void);
void init(void);
void Adc_Config(void);

// Initialize global variables for this file
int32 current = 0;
float Freq = .1;   // frequency of timer0 interrupt in Hz
int32 adc = 0;
Uint32 Dead_Time_ns = 2000;
float PWM_Freq = 20;		// PWM Frequency in kHz
float PWM_Duty_Cycle = .3;	// PWM Duty Cycle
Uint32 PWM_Counter = 0;
char Sine_PWM = 0;
char hall_PWM = 0;
float Sine_Freq = 10; 		// Sine PWM Frequency in Hz
float Sine_Mag = .5;        // Magnitude of Sine PWM (0-1)
int32 lasthallstate = 0;
int32 hallstate = 0;
int32 hallA = 0;
int32 hallB = 0;
int32 hallC = 0;

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
	PieVectTable.EPWM1_INT = &epwm1_timer_isr;
	EDIS;    // This is needed to disable write to EALLOW protected registers

	InitEPwm();    // For this example, only initialize the ePWM Timer

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
	IER |= M_INT3;

	// Enable individual PIE Table interrupts
	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;		// Enable TINT0 in the PIE: Group 1 interrupt 7
    PieCtrlRegs.PIEIER9.bit.INTx1 = 1;		// Enable SCIRXINTA in the PIE: Group 9 interrupt 1
    PieCtrlRegs.PIEIER1.bit.INTx1 = 1;		// Enable INT 1.1 in the PIE
    PieCtrlRegs.PIEIER3.bit.INTx1 = 1;		// Enable EPWM INTn in the PIE: Group 3 interrupt 1-6

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
    // Setup GPIO-16,17,18 for Hall Effect Sensor
	EALLOW;
	GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;    // Enable pull-up for GPIO28 (SCIRXDA)
	GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO16 = 0;
	GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;    // Enable pull-up for GPIO28 (SCIRXDA)
	GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO17 = 0;
	GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;    // Enable pull-up for GPIO28 (SCIRXDA)
	GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO18 = 0;
	EDIS;
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
void InitEPwm()
{

   EALLOW;
   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;      // Stop all the TB clocks in order to synchronize clocks and configure ePWM modules
   // LOW SPEED CLOCKS prescale register settings
   SysCtrlRegs.LOSPCP.all = 0x0002;		// Sysclk / 4 (20 MHz)
   SysCtrlRegs.XCLK.bit.XCLKOUTDIV=2;
   SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 1;  // ePWM1
   SysCtrlRegs.PCLKCR1.bit.EPWM2ENCLK = 1;  // ePWM2
   SysCtrlRegs.PCLKCR1.bit.EPWM2ENCLK = 1;  // ePWM3
   SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;   // Enable TB
  //  GPIO-00 - PIN FUNCTION = --Spare--
	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;		// 0=GPIO, 1=EPWM1A, 2=Resv, 3=Resv
	GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;		// 1=OUTput,  0=INput
	GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;      // Enable pull-up on GPIO0 (EPWM1A)
	GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;		// 0=GPIO, 1=EPWM1B, 2=EMU (0), 3=COMP1OUT
	GpioCtrlRegs.GPADIR.bit.GPIO1 = 1;		// 1=OUTput,  0=INput
	GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;      // Enable pull-up on GPIO0 (EPWM1A)
	GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;		// 0=GPIO, 1=EPWM2A, 2=Resv, 3=Resv
	GpioCtrlRegs.GPADIR.bit.GPIO2 = 1;		// 1=OUTput,  0=INput
	GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1;      // Enable pull-up on GPIO0 (EPWM1A)
	GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;		// 0=GPIO, 1=EPWM2B, 2=EMU (0), 3=COMP1OUT
	GpioCtrlRegs.GPADIR.bit.GPIO3 = 1;		// 1=OUTput,  0=INput
	GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1;      // Enable pull-up on GPIO0 (EPWM1A)
	GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;		// 0=GPIO, 1=EPWM3B, 2=EMU (0), 3=COMP1OUT
	GpioCtrlRegs.GPADIR.bit.GPIO4 = 1;		// 1=OUTput,  0=INput
	GpioCtrlRegs.GPAPUD.bit.GPIO4 = 1;      // Enable pull-up on GPIO0 (EPWM1A)
	GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;		// 0=GPIO, 1=EPWM3B, 2=EMU (0), 3=COMP1OUT
	GpioCtrlRegs.GPADIR.bit.GPIO5 = 1;		// 1=OUTput,  0=INput
	GpioCtrlRegs.GPAPUD.bit.GPIO5 = 1;      // Enable pull-up on GPIO0 (EPWM1A)
  //	GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;	// uncomment if --> Set Low initially
  //	GpioDataRegs.GPASET.bit.GPIO0 = 1;		// uncomment if --> Set High initially

  //--------------------------------------------------------------------------------------
  //  GPIO-01 - PIN FUNCTION = --Spare--

  //	GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;	// uncomment if --> Set Low initially
  //	GpioDataRegs.GPASET.bit.GPIO1 = 1;		// uncomment if --> Set High initially
  //--------------------------------------------------------------------------------------
   EDIS;

   // Initally disable Free/Soft Bits
   EPwm1Regs.TBCTL.bit.FREE_SOFT = 0;
   EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;     	// Select INT on Zero event
   EPwm1Regs.ETSEL.bit.INTEN = 1;  					// Enable INT
   EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;           	// Generate INT on 1st event
   EPwm1Regs.AQCTLA.all = 0x0024;				   	// Action-qualifiers, Set on CMPA, Clear on PRD


   // Time-base registers
	EPwm1Regs.TBPRD = (Uint16)(80000/PWM_Freq);       		   // Set timer period, System clock is 80Mhz and PWM_Freq is in Khz
	EPwm1Regs.TBPHS.all = 0;				   // Time-Base Phase Register
	EPwm1Regs.TBCTR = 0;					   // Time-Base Counter Register
    EPwm1Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;  // Set Immediate load
    EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count-up mode: used for asymmetric PWM
   	EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;	   // Disable phase loading
   	EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
   	EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
   	EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    // Time-base registers
 	EPwm2Regs.TBPRD = (Uint16)(80000/PWM_Freq);       		   // Set timer period, System clock is 80Mhz and PWM_Freq is in Khz
 	EPwm2Regs.TBPHS.all = 0;				   // Time-Base Phase Register
 	EPwm2Regs.TBCTR = 0;					   // Time-Base Counter Register
	EPwm2Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;  // Set Immediate load
	EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count-up mode: used for asymmetric PWM
	EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;	   // Disable phase loading
	EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
	EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
	EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    // Time-base registers
 	EPwm3Regs.TBPRD = (Uint16)(80000/PWM_Freq);       		   // Set timer period, System clock is 80Mhz and PWM_Freq is in Khz
 	EPwm3Regs.TBPHS.all = 0;				   // Time-Base Phase Register
 	EPwm3Regs.TBCTR = 0;					   // Time-Base Counter Register
	EPwm3Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;  // Set Immediate load
	EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count-up mode: used for asymmetric PWM
	EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;	   // Disable phase loading
	EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_DISABLE;
	EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;
	EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;

	// Setup shadow register load on ZERO
	EPwm1Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;	// load on CTR=Zero
	EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;	// load on CTR=Zero

    // Set compare values
    EPwm1Regs.CMPA.half.CMPA = (Uint16)(80000/PWM_Freq*PWM_Duty_Cycle);    // Set duty 50% initially
    EPwm2Regs.CMPA.half.CMPA = (Uint16)(80000/PWM_Freq*PWM_Duty_Cycle);    // Set duty 50% initially
    EPwm3Regs.CMPA.half.CMPA = (Uint16)(80000/PWM_Freq*PWM_Duty_Cycle);    // Set duty 50% initially

    // Set actions
    EPwm1Regs.AQCTLA.bit.ZRO = AQ_SET;            // Set PWM1A on Zero
    EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;          // Clear PWM1A on event A, up count

    EPwm1Regs.AQCTLB.bit.ZRO = AQ_CLEAR;          // Set PWM1B on Zero
    EPwm1Regs.AQCTLB.bit.CBU = AQ_SET;            // Clear PWM1B on event B, up count

    EPwm2Regs.AQCTLA.bit.ZRO = AQ_SET;            // Set PWM2A on Zero
    EPwm2Regs.AQCTLA.bit.CAU = AQ_CLEAR;          // Clear PWM2A on event A, up count

    EPwm2Regs.AQCTLB.bit.ZRO = AQ_CLEAR;          // Set PWM2B on Zero
    EPwm2Regs.AQCTLB.bit.CBU = AQ_SET;            // Clear PWM2B on event B, up count

    EPwm3Regs.AQCTLA.bit.ZRO = AQ_SET;            // Set PWM3A on Zero
    EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;          // Clear PWM3A on event A, up count

    EPwm3Regs.AQCTLB.bit.ZRO = AQ_CLEAR;          // Set PWM3B on Zero
    EPwm3Regs.AQCTLB.bit.CBU = AQ_SET;            // Clear PWM3B on event B, up count

    // DeadBand configuration
   	EPwm1Regs.DBCTL.bit.IN_MODE = DBA_ALL;  		// EPwm1A is the source for both falling-edge and rising-edge delay
   	EPwm1Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;  // Both the falling-edge delay (FED) and rising-edge delay (RED) are applied to the input signals
   	EPwm1Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; 		// Active High Complementary (AHC)

   	EPwm2Regs.DBCTL.bit.IN_MODE = DBA_ALL;  		// EPwm2A is the source for both falling-edge and rising-edge delay
   	EPwm2Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;  // Both the falling-edge delay (FED) and rising-edge delay (RED) are applied to the input signals
   	EPwm2Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; 		// Active High Complementary (AHC)

   	EPwm3Regs.DBCTL.bit.IN_MODE = DBA_ALL;  		// EPwm3A is the source for both falling-edge and rising-edge delay
   	EPwm3Regs.DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;  // Both the falling-edge delay (FED) and rising-edge delay (RED) are applied to the input signals
   	EPwm3Regs.DBCTL.bit.POLSEL = DB_ACTV_HIC; 		// Active High Complementary (AHC)

   	// Set Deadband
   	EPwm1Regs.DBRED = (100);					// Set DeadBand time for rising edge of ePWM1a. 12.5 = ns/clock cycle (@80Mhz)
   	EPwm1Regs.DBFED = (100);;					// Set DeadBand time for falling edge of ePWM1a

   	EPwm2Regs.DBRED = (100);					// Set DeadBand time for rising edge of ePWM2a. 12.5 = ns/clock cycle (@80Mhz)
   	EPwm2Regs.DBFED = (100);;					// Set DeadBand time for falling edge of ePWM2a

   	EPwm3Regs.DBRED = (100);					// Set DeadBand time for rising edge of ePWM3a. 12.5 = ns/clock cycle (@80Mhz)
   	EPwm3Regs.DBFED = (100);;					// Set DeadBand time for falling edge of ePWM3a

    EDIS;

}

// Interrupt routines uses in this example:
__interrupt void epwm1_timer_isr(void)
{
	PWM_Counter++;
	// Measure Hall State
	hallA = GpioDataRegs.GPADAT.bit.GPIO16;
	hallB = GpioDataRegs.GPADAT.bit.GPIO17;
	hallC = GpioDataRegs.GPADAT.bit.GPIO18;
	hallstate = hallA+hallB*2+hallC*4;

	// Start ADC current conversion
	AdcRegs.ADCSOCFRC1.bit.SOC1 = 1;
	float period = 80000000.0/Sine_Freq;		// Period in Pulses
	if (PWM_Counter == (Uint32)(period)) PWM_Counter = 0;
	EALLOW;
	if(Sine_PWM == 1)
	{
		float dutycycle_A = Sine_Mag*(sin(2*3.14159*PWM_Counter*100/period+2*3.14159/3)+1)/2;
		float dutycycle_B = Sine_Mag*(sin(2*3.14159*PWM_Counter*100/period)+1)/2;
		float dutycycle_C = Sine_Mag*(sin(2*3.14159*PWM_Counter*100/period+4*3.14159/3)+1)/2;
		// Set compare values
		EPwm1Regs.CMPA.half.CMPA = (Uint16)(80000.0/PWM_Freq*dutycycle_A);    // Set duty 50% initially
	    EPwm2Regs.CMPA.half.CMPA = (Uint16)(80000.0/PWM_Freq*dutycycle_B);    // Set duty 50% initially
	    EPwm3Regs.CMPA.half.CMPA = (Uint16)(80000.0/PWM_Freq*dutycycle_C);    // Set duty 50% initially
		// Set Deadband
	} else {
		if(hall_PWM == 1)
		{
			//GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;		// 0=GPIO, 1=EPWM1A, 2=Resv, 3=Resv
			//GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;		// 0=GPIO, 1=EPWM1A, 2=Resv, 3=Resv
			//GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;		// 0=GPIO, 1=EPWM1A, 2=Resv, 3=Resv
			//GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;		// 0=GPIO, 1=EPWM1A, 2=Resv, 3=Resv
			//GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;		// 0=GPIO, 1=EPWM1A, 2=Resv, 3=Resv
			//GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;		// 0=GPIO, 1=EPWM1A, 2=Resv, 3=Resv
			if (hallstate == 4) {
				EPwm2Regs.AQCSFRC.bit.CSFA = 1;
				EPwm2Regs.AQCSFRC.bit.CSFB = 1;
				EPwm1Regs.CMPA.half.CMPA = (Uint16)(80000.0/PWM_Freq*0);    // Set duty 50% initially
				//EPwm2Regs.CMPA.half.CMPA = (Uint16)(80000.0/PWM_Freq*-1);    // Set duty 50% initially
				EPwm3Regs.CMPA.half.CMPA = (Uint16)(80000.0/PWM_Freq*PWM_Duty_Cycle);    // Set duty 50% initially
			}
			if (hallstate == 6) {
				//EPwm1Regs.CMPA.half.CMPA = (Uint16)(80000.0/PWM_Freq*-1);    // Set duty 50% initially
				GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;		// 0=GPIO, 1=EPWM1A, 2=Resv, 3=Resv
				GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;		// 0=GPIO, 1=EPWM1A, 2=Resv, 3=Resv
				GpioDataRegs.GPASET.bit.GPIO0 = 0;
				GpioDataRegs.GPASET.bit.GPIO1 = 0;
				EPwm2Regs.CMPA.half.CMPA = (Uint16)(80000.0/PWM_Freq*0);    // Set duty 50% initially
				EPwm3Regs.CMPA.half.CMPA = (Uint16)(80000.0/PWM_Freq*PWM_Duty_Cycle);    // Set duty 50% initially
			}
			if (hallstate == 2) {
				EPwm1Regs.CMPA.half.CMPA = (Uint16)(80000.0/PWM_Freq*PWM_Duty_Cycle);    // Set duty 50% initially
				EPwm2Regs.CMPA.half.CMPA = (Uint16)(80000.0/PWM_Freq*0);    // Set duty 50% initially
				//EPwm3Regs.CMPA.half.CMPA = (Uint16)(80000.0/PWM_Freq*-1);    // Set duty 50% initially
				GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0;		// 0=GPIO, 1=EPWM1A, 2=Resv, 3=Resv
				GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;		// 0=GPIO, 1=EPWM1A, 2=Resv, 3=Resv
				GpioDataRegs.GPASET.bit.GPIO4 = 0;
				GpioDataRegs.GPASET.bit.GPIO5 = 0;
			}
			if (hallstate == 3) {
				EPwm1Regs.CMPA.half.CMPA = (Uint16)(80000.0/PWM_Freq*PWM_Duty_Cycle);    // Set duty 50% initially
				//EPwm2Regs.CMPA.half.CMPA = (Uint16)(80000.0/PWM_Freq*-1);    // Set duty 50% initially
				GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;		// 0=GPIO, 1=EPWM1A, 2=Resv, 3=Resv
				GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;		// 0=GPIO, 1=EPWM1A, 2=Resv, 3=Resv
				GpioDataRegs.GPASET.bit.GPIO2 = 0;
				GpioDataRegs.GPASET.bit.GPIO3 = 0;
				EPwm3Regs.CMPA.half.CMPA = (Uint16)(80000.0/PWM_Freq*0);    // Set duty 50% initially
			}
			if (hallstate == 1) {
				//EPwm1Regs.CMPA.half.CMPA = (Uint16)(80000.0/PWM_Freq*-1);    // Set duty 50% initially
				GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;		// 0=GPIO, 1=EPWM1A, 2=Resv, 3=Resv
				GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;		// 0=GPIO, 1=EPWM1A, 2=Resv, 3=Resv
				GpioDataRegs.GPASET.bit.GPIO0 = 0;
				GpioDataRegs.GPASET.bit.GPIO1 = 0;
				EPwm2Regs.CMPA.half.CMPA = (Uint16)(80000.0/PWM_Freq*PWM_Duty_Cycle);    // Set duty 50% initially
				EPwm3Regs.CMPA.half.CMPA = (Uint16)(80000.0/PWM_Freq*0);    // Set duty 50% initially
			}
			if (hallstate == 5) {
				EPwm1Regs.CMPA.half.CMPA = (Uint16)(80000.0/PWM_Freq*0);    // Set duty 50% initially
				EPwm2Regs.CMPA.half.CMPA = (Uint16)(80000.0/PWM_Freq*PWM_Duty_Cycle);    // Set duty 50% initially
				GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0;		// 0=GPIO, 1=EPWM1A, 2=Resv, 3=Resv
				GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;		// 0=GPIO, 1=EPWM1A, 2=Resv, 3=Resv
				GpioDataRegs.GPASET.bit.GPIO4 = 0;
				GpioDataRegs.GPASET.bit.GPIO5 = 0;
				//EPwm3Regs.CMPA.half.CMPA = (Uint16)(80000.0/PWM_Freq*-1);    // Set duty 50% initially
			}
		} else {
			// Set compare values
			EPwm1Regs.CMPA.half.CMPA = (Uint16)(80000.0/PWM_Freq*PWM_Duty_Cycle);    // Set duty 50% initially
			EPwm2Regs.CMPA.half.CMPA = (Uint16)(80000.0/PWM_Freq*PWM_Duty_Cycle);    // Set duty 50% initially
			EPwm3Regs.CMPA.half.CMPA = (Uint16)(80000.0/PWM_Freq*PWM_Duty_Cycle);    // Set duty 50% initially
		}
	}
	// Time-base registers
	EPwm1Regs.TBPRD = (Uint16)(80000.0/PWM_Freq);       		   // Set timer period, System clock is 80Mhz and PWM_Freq is in Khz
	EPwm2Regs.TBPRD = (Uint16)(80000.0/PWM_Freq);       		   // Set timer period, System clock is 80Mhz and PWM_Freq is in Khz
	EPwm3Regs.TBPRD = (Uint16)(80000.0/PWM_Freq);       		   // Set timer period, System clock is 80Mhz and PWM_Freq is in Khz

	//EPwm1Regs.DBRED = (Dead_Time_ns/12.5);					// Set DeadBand time for rising edge of ePWM1a. 12.5 = ns/clock cycle (@80Mhz)
	//EPwm1Regs.DBFED = (Dead_Time_ns/12.5);				// Set DeadBand time for falling edge of ePWM1a
	EDIS;


    // Clear INT flag for this timer
    EPwm1Regs.ETCLR.bit.INT = 1;



   // Acknowledge this interrupt to receive more interrupts from group 3
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

// ADC interrupt function
__interrupt void  adc_isr(void)
{

  adc = AdcResult.ADCRESULT1;
  //current = adc;
  current = (-1*adc*7388)/1000+15175;
  //UARTprintf("ADC Value = %u\r\n",adc);

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
   UARTprintf("Current Value, %d\r\n",current);
   UARTprintf("ADC Value, %d\r\n",adc);


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
