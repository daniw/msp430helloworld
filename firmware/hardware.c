/** \addtogroup linbox_hardware
    @{ */

/**
 * @file
 *
 * Hardware initialization functions for the calibration interface box.
 * 
 *
 * @author      Daniel Winz <daniel.winz@stud.hslu.ch>
 */

#include <mspgcc/util.h>                // delay()
#include <mspgcc/fll.h>
#include <msp430x21x2.h>
#include "hardware.h"


// - - - - - - - - - - public variables - - - - - - - - - - - - - - - - - - - -

/**
 * Table with led hardware configuration
 */

static config_led_t status_led[] = { \
    {port: (uint16_t*)&P2OUT , pin: BIT4},//0  (LED -5)
    {port: (uint16_t*)&P2OUT , pin: BIT3},//1  (LED -4)
    {port: (uint16_t*)&P2OUT , pin: BIT2},//2  (LED -3)
    {port: (uint16_t*)&P2OUT , pin: BIT1},//3  (LED -2)
    {port: (uint16_t*)&P2OUT , pin: BIT0},//4  (LED -1)
    {port: (uint16_t*)&P2OUT , pin: BIT6},//5  (LED 0)
    {port: (uint16_t*)&P3OUT , pin: BIT3},//6  (LED +1)
    {port: (uint16_t*)&P3OUT , pin: BIT4},//7  (LED +2)
    {port: (uint16_t*)&P3OUT , pin: BIT5},//8  (LED +3)
    {port: (uint16_t*)&P3OUT , pin: BIT6},//9  (LED +4)
    {port: (uint16_t*)&P3OUT , pin: BIT7},//10 (LED +5)
};
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

    //~ DCOCTL    = DCOCTL_INIT;            // Initializes clock module
    //~ BCSCTL1   = BCSCTL1_INIT;           
    //~ BCSCTL2   = BCSCTL2_INIT;           
    //~ BCSCTL3   = BCSCTL3_INIT;           
}

/**
 * Reads the actual flow input value from the ADC
 */
uint16_t read_flow_in(void){
    uint16_t flow;                      
    ADC10CTL0 |= (ENC | ADC10SC);       // start ADC conversion
    while((ADC10CTL0 & ADC10IFG) == 0){ // wait while ADC conversion is running
    }
    ADC10CTL0 &= ~ADC10IFG;             // clear interrupt flag
    flow = ADC10MEM;                    // 'flow' := ADC value
    return(flow);                       // return flow
}

/**
 * Sets the PWM ratio for the flow output
 */
void write_flow_out(uint16_t flow){
    TA0CTL &= ~MC_1;                    // stop Timer
    TA0CCR1 = flow;                     // TA0CCR1 := 'flow'
    TA0CTL |= MC_1;                     // start Timer
}

/**
 * Updates the LED status
 * 
 * Each Bit in led stands for a led. The led are numbered from the led for -20% 
 * which is depending on Bit 0 up to the led for +20% which is depending on Bit 10. 
 */
void update_led(uint16_t led){
    uint8_t i;
    for(i=0;i<11;i++){
        if((led&(1<<i))>0) {
            *status_led[i].port |= status_led[i].pin;
        }
        else {
            *status_led[i].port &= ~status_led[i].pin;
        }
    }
}

/**
 * Check if the button is pressed. 
 * returns 1 if  the button is pressed and 0 if button is not pressed. 
 */
uint8_t check_button(){
    uint8_t button;
    if((P2IN&PIN_BUTTON)==0) {
        button = 1;
    }
    else {
        button = 0;
    }
    return(button);
}

/** @} */
