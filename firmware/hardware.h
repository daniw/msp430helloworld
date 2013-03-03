#ifndef HARDWARE_H
#define HARDWARE_H

/**
 * @file
 *
 * Hardware description for the ti launchpad
 * 
 *
 * @author      Daniel Winz <daniel.winz@stud.hslu.ch>
 */

//~ #include <io.h>
//~ #include <signal.h>
//~ #include <msp430g2553.h>
//~ #include <msp430x21x2.h>
#include <msp430.h>

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


/*
PINS:
Comment-Abbreviations:
I: Input, O: Output (PxDIR)
M: Module (PxSEL)
L: Low, H: high (PxOut)
R: Pullup/down Resistor active (PxREN)
Comment
*/


//--- Watchdog Timer ---
#define WDTCTL_INIT     (WDTPW|WDTTMSEL|WDTCNTCL)   // Init watchdog as interval timer
#define IE1_WDT_INIT    (WDTIE)                     // Enable watchdog interrupt


//--- PORT1 ---
#define P1_0            BIT0    ///< |OL|       red LED for "Hello World"
#define P1_1            BIT1    ///< |IRL|      unused
#define P1_2            BIT2    ///< |IRL|      unused
#define P1_3            BIT3    ///< |IRL|      unused
#define P1_4            BIT4    ///< |OM|       SMCLK for Measurement of int. clock
#define P1_5            BIT5    ///< |IRL|      unused
#define P1_6            BIT6    ///< |OH|       green LED for "Hello World"
#define P1_7            BIT7    ///< |IRL|      unused

#define P1OUT_INIT      (P1_6)
#define P1SEL_INIT      (0)
#define P1SEL2_INIT     (0)
#define P1DIR_INIT      (P1_0 | P1_6)
#define P1REN_INIT      (P1_1 | P1_2 | P1_3 | P1_4 | P1_5 | P1_7)

#define P1IE_INIT       (0)     ///< disable irq
#define P1IES_INIT      (0)     ///< H->L transition


//--- PORT2 ---
#define P2_0            BIT0    ///< |IRL|      unused
#define P2_1            BIT1    ///< |IRL|      unused
#define P2_2            BIT2    ///< |IRL|      unused
#define P2_3            BIT3    ///< |IRL|      unused
#define P2_4            BIT4    ///< |IRL|      unused
#define P2_5            BIT5    ///< |IRL|      unused
#define P2_6            BIT6    ///< |IRL|      unused
#define P2_7            BIT7    ///< |IRL|      unused


#define P2OUT_INIT      (0)
#define P2SEL_INIT      (0)
#define P2SEL2_INIT     (0)
#define P2DIR_INIT      (0)
#define P2REN_INIT      (P2_0 | P2_1 | P2_2 | P2_3 | P2_4 | P2_5 | P2_6 | P2_7)

#define CAPD_INIT       (0)

#define P2IE_INIT       (0)
#define P2IES_INIT      (0)


//--- PORT3 ---
#define P3_0            BIT0    ///< |IRL|      unused
#define P3_1            BIT1    ///< |IRL|      unused
#define P3_2            BIT2    ///< |IRL|      unused
#define P3_3            BIT3    ///< |IRL|      unused
#define P3_4            BIT4    ///< |IRL|      unused
#define P3_5            BIT5    ///< |IRL|      unused
#define P3_6            BIT6    ///< |IRL|      unused
#define P3_7            BIT7    ///< |IRL|      unused

//~ #define ADC_FLOW_INPUT  BIT5    ///< |IM|       ADC Channel of Flow Sensor input

#define P3OUT_INIT      (0)
#define P3SEL_INIT      (0)
#define P3DIR_INIT      (0)
#define P3REN_INIT      (P3_0 | P3_1 | P3_2 | P3_3 | P3_4 | P3_5 | P3_6 | P3_7)


//--- Interrupts ---
#define IE1_INIT        (0)
#define IE2_INIT        (0)


//~ //--- ADC ---
//~ #define ADC10CTL0_INIT  (ADC10SHT_3 | ADC10ON)
//~ #define ADC10CTL1_INIT  (INCH_5 | ADC10SSEL_3)
//~ #define ADC10AE0_INIT   (ADC_FLOW_INPUT)
//~ #define ADC10DTC0_INIT  (0)
//~ #define ADC10DTC1_INIT  (0)


//~ //--- Timer A ---
//~ #define TACTL_INIT      (TASSEL_2 | MC_1 | TACLR)
//~ #define TACCR0_INIT     (0xffff)
//~ #define TACCR1_INIT     (0x0)
//~ #define TACCTL1_INIT    (OUTMOD_7)


//~ //--- I2C ---
//~ #define I2C_ADDRESS     (0x49)                  // I2C Address
//~ #define UCB0CTL1_INIT_0 (UCSWRST)               // USCI reset
//~ #define UCB0CTL0_INIT   (UCMODE_3 | UCSYNC)     // 7-bit, single master, I2C, synchronous
                                                //~ // No need to configure UCB0CTL1, UCB0BR, nor UCB0I2CCSA for a slave
//~ #define UCB0I2COA_INIT  (I2C_ADDRESS)           // ignore genl call; own adress I2C_ADDRESS
//~ #define UCB0CTL1_INIT_1 (~UCSWRST)              // release from reset
//~ #define UCB0I2CIE_INIT  (UCSTTIE | UCSTPIE)     //enable interrupts on Start , Stop
//~ #define IE2_I2C_INIT    (UCB0RXIE | UCB0TXIE)   //enable interrupts on RX and TX


//~ //--- Clock Module ---
#define DCOCTL_INIT     (CALDCO_1MHZ)          
#define BCSCTL1_INIT    (XT2OFF|CALBC1_1MHZ)   
#define BCSCTL2_INIT    (0)                     
#define BCSCTL3_INIT    (0)                     


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -


// function prototypes
void hardware_lowlevel_init(void);              // Initialize hardware

#endif //HARDWARE_H
