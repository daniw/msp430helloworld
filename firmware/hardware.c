
/**
 * @file
 *
 * Hardware initialization functions for the ti launchpad
 * 
 *
 * @author      Daniel Winz <daniel.winz@stud.hslu.ch>
 */

//~ #include <mspgcc/util.h>                // delay()
//~ #include <mspgcc/fll.h>
//~ #include <msp430g2553.h>
//~ #include <msp430x21x2.h>
#include <msp430.h>
#include "hardware.h"


// - - - - - - - - - - public variables - - - - - - - - - - - - - - - - - - - -

// - - - - - - - - - - public functions - - - - - - - - - - - - - - - - - - - -


/**
 * Initialize watchdog, ports and modules.
 */
void hardware_lowlevel_init(void) {
    P1OUT     = P1OUT_INIT;             // Init output data of port1
    P1SEL     = P1SEL_INIT;             // Select port or module -function on port1
    P1SEL2    = P1SEL2_INIT;            // Select port or module -function on port1
    P1DIR     = P1DIR_INIT;             // Init port direction register of port1
    P1IES     = P1IES_INIT;             // init port interrupts
    P1IE      = P1IE_INIT;
    P1REN     = P1REN_INIT;             // Initialize Pulldown-Resistor

    P2OUT     = P2OUT_INIT;             // Init output data of port2
    P2SEL     = P2SEL_INIT;             // Select port or module -function on port2
    P2DIR     = P2DIR_INIT;             // Init port direction register of port2
    P2IES     = P2IES_INIT;             // init port interrupts
    P2IE      = P2IE_INIT;
    P2REN     = P2REN_INIT;             // Initialize Pulldown-Resistor
    CAPD      = CAPD_INIT;              // Init input buffers on port2 pins

    P3OUT     = P3OUT_INIT;             // Init output data of port3
    P3SEL     = P3SEL_INIT;             // Select port or module -function on port3
    P3DIR     = P3DIR_INIT;             // Init port direction register of port3
    P3REN     = P3REN_INIT;             // Initialize Pulldown-Resistor

    IE1      |= IE1_INIT;               // Initializes Interrupts
    IE2      |= IE2_INIT;               

    WDTCTL    = WDTCTL_INIT;            // Init watchdog as interval timer
    IE1      |= IE1_WDT_INIT;           

    //~ ADC10CTL0 = ADC10CTL0_INIT;         // Initalizes ADC
    //~ ADC10CTL1 = ADC10CTL1_INIT;         
    //~ ADC10AE0  = ADC10AE0_INIT;          
    //~ ADC10DTC0 = ADC10DTC0_INIT;         
    //~ ADC10DTC1 = ADC10DTC1_INIT;         

    //~ TA0CTL    = TACTL_INIT;             // Initializes Timer A
    //~ TA0CCR0   = TACCR0_INIT;            
    //~ TA0CCR1   = TACCR1_INIT;            
    //~ TA0CCTL1  = TACCTL1_INIT;           

                                        //~ // i2c setup
    //~ UCB0CTL1  = UCB0CTL1_INIT_0;        // USCI reset
    //~ UCB0CTL0  = UCB0CTL0_INIT;          // 7-bit, single master, I2C, synchronous
                                        //~ // No need to configure UCB0CTL1, UCB0BR, nor UCB0I2CCSA for a slave
    //~ UCB0I2COA = UCB0I2COA_INIT;         // ignore genl call; own adress I2C_ADDRESS
    //~ UCB0CTL1  = UCB0CTL1_INIT_1;        // release from reset
    //~ UCB0I2CIE = UCB0I2CIE_INIT;         // enable interrupts on Start , Stop
    //~ IE2      |= IE2_I2C_INIT;           // enable interrupts on RX and TX

    DCOCTL    = DCOCTL_INIT;            // Initializes clock module
    BCSCTL1   = BCSCTL1_INIT;           
    BCSCTL2   = BCSCTL2_INIT;           
    BCSCTL3   = BCSCTL3_INIT;           
}
