#ifndef HARDWARE_H
#define HARDWARE_H

/** \addtogroup linbox_hardware
    @{ */

/**
 * @file
 *
 * Hardware description for the Lin-Box.
 * 
 *
 * @author      Daniel Winz <daniel.winz@stud.hslu.ch>
 */

#include <io.h>
#include <signal.h>
#include <msp430x21x2.h>

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
/*@-fcnuse@*/   //splint: don't complain about unused HWCONF_PIN macros



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
#define P1_0            BIT0    ///< |IRL|      unused
#define P1_1            BIT1    ///< |IRL|      unused
#define PIN_FLOW_OUT    BIT2    ///< |OM|       Flow Output (PWM Module of Timer B)
#define PIN_FLOW_ERROR  BIT3    ///< |IRH|      Error of flow sensor supply voltage
#define P1_4            BIT4    ///< |IRL|      unused (Jtag, TCK)
#define P1_5            BIT5    ///< |IRL|      unused (Jtag, TMS)
#define P1_6            BIT6    ///< |IRL|      unused (Jtag, TDI)
#define P1_7            BIT7    ///< |IRL|      unused (Jtag, TDO)

#define P1OUT_INIT      (PIN_FLOW_ERROR)
#define P1SEL_INIT      (PIN_FLOW_OUT)
#define P1SEL2_INIT     (0)
#define P1DIR_INIT      (PIN_FLOW_OUT)
#define P1REN_INIT      (P1_0 | P1_1 | PIN_FLOW_ERROR | P1_4 | P1_5 | P1_6 | P1_7)

#define P1IE_INIT       (0)     ///< disable irq
#define P1IES_INIT      (0)     ///< H->L transition


//--- PORT2 ---
#define PIN_LED_M1      BIT0    ///< |OL|       LED -1
#define PIN_LED_M2      BIT1    ///< |OL|       LED -2
#define PIN_LED_M3      BIT2    ///< |OL|       LED -3
#define PIN_LED_M4      BIT3    ///< |OL|       LED -4
#define PIN_LED_M5      BIT4    ///< |OL|       LED -5
#define P2_5            BIT5    ///< |IRL|      unused
#define PIN_LED_0       BIT6    ///< |OL|       LED 0
#define PIN_BUTTON      BIT7    ///< |IRH|      Button


#define P2OUT_INIT      (PIN_BUTTON)
#define P2SEL_INIT      (0)
#define P2SEL2_INIT     (0)
#define P2DIR_INIT      (PIN_LED_M1 | PIN_LED_M2 | PIN_LED_M3 | PIN_LED_M4 | PIN_LED_M5 | PIN_LED_0)
#define P2REN_INIT      (P2_5 | PIN_BUTTON)

#define CAPD_INIT       (0)

#define P2IE_INIT       (0)
#define P2IES_INIT      (0)


//--- PORT3 ---
#define PIN_FLOW_INPUT  BIT0    ///< |IM|       flow sensor input (ADC input)
#define PIN_SDA         BIT1    ///< |IML|      I2C SDA
#define PIN_SCL         BIT2    ///< |IML|      I2C SCL
#define PIN_LED_P1      BIT3    ///< |OL|       LED +1
#define PIN_LED_P2      BIT4    ///< |OL|       LED +2
#define PIN_LED_P3      BIT5    ///< |OL|       LED +3
#define PIN_LED_P4      BIT6    ///< |OL|       LED +4
#define PIN_LED_P5      BIT7    ///< |OL|       LED +5

#define ADC_FLOW_INPUT  BIT5    ///< |IM|       ADC Channel of Flow Sensor input

#define P3OUT_INIT      (0)
#define P3SEL_INIT      (PIN_SDA | PIN_SCL)
#define P3DIR_INIT      (PIN_LED_P1 | PIN_LED_P2 | PIN_LED_P3 | PIN_LED_P4 | PIN_LED_P5)
#define P3REN_INIT      (0)


//--- Interrupts ---
#define IE1_INIT        (0)
#define IE2_INIT        (0)


//--- ADC ---
#define ADC10CTL0_INIT  (ADC10SHT_3 | ADC10ON)
#define ADC10CTL1_INIT  (INCH_5 | ADC10SSEL_3)
#define ADC10AE0_INIT   (ADC_FLOW_INPUT)
#define ADC10DTC0_INIT  (0)
#define ADC10DTC1_INIT  (0)


//--- Timer A ---
#define TACTL_INIT      (TASSEL_2 | MC_1 | TACLR)
#define TACCR0_INIT     (0xffff)
#define TACCR1_INIT     (0x0)
#define TACCTL1_INIT    (OUTMOD_7)


//--- I2C ---
#define I2C_ADDRESS     (0x49)                  // I2C Address
#define UCB0CTL1_INIT_0 (UCSWRST)               // USCI reset
#define UCB0CTL0_INIT   (UCMODE_3 | UCSYNC)     // 7-bit, single master, I2C, synchronous
                                                // No need to configure UCB0CTL1, UCB0BR, nor UCB0I2CCSA for a slave
#define UCB0I2COA_INIT  (I2C_ADDRESS)           // ignore genl call; own adress I2C_ADDRESS
#define UCB0CTL1_INIT_1 (~UCSWRST)              // release from reset
#define UCB0I2CIE_INIT  (UCSTTIE | UCSTPIE)     //enable interrupts on Start , Stop
#define IE2_I2C_INIT    (UCB0RXIE | UCB0TXIE)   //enable interrupts on RX and TX


//--- Clock Module ---
#define DCOCTL_INIT     (CALDCO_16MHZ)          
#define BCSCTL1_INIT    (XT2OFF|CALBC1_16MHZ)   
#define BCSCTL2_INIT    (0)                     
#define BCSCTL3_INIT    (0)                     


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

typedef struct config_led{
    uint16_t*   port;
    uint8_t     pin;
} config_led_t;

#ifndef _GNU_ASSEMBLER_ // C compiler runs only
// function prototypes
void hardware_lowlevel_init(void);              // Initialize hardware
uint16_t read_flow_in(void);                    // read flow value from flow sensor
void write_flow_out(uint16_t flow);             // write linearized flow value to output
void update_led(uint16_t led);                  // Updates the LEDs
uint8_t check_button();                         // Check if the Button is pressed
#endif //_GNU_ASSEMBLER_

/** @} */

#endif //HARDWARE_H
