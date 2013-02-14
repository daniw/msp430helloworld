/* Application for the Lin-Box
 *
 * With profiling:
 *                 MSP430F2132
 */

#include <io.h>
#include <signal.h>
#include <mspgcc/util.h>                // delay()
#include <mspgcc/eventhandler.h>
#include <stdbool.h>
#include "hardware.h"
#include "linbox.h"
//~ #include "lookup.h"

#define EVENT_scheduler         EVENT00_bits
#define EVENT_flow_update       EVENT01_bits

//~ static uint8_t i2c_state;
//~ static uint16_t i2c_ee_address;

/**
 * Table with the events that are started by the scheduler.
 */
const SCHEDULER_TABLE scheduler_table[] = {
    {modulo: 32, shift: 0, eventbits: EVENT_flow_update},
    {0} // sentinel, marks the end of the table
};

//~ /**
 //~ * Device image that is provided as part of the EEPROM image.
 //~ */
//~ i2c_slave_image_t i2c_slave_image = {
    //~ {
        //~ {5, .period=8, .tag="VE"},
        //~ {.tag="FV"},
        //~ {.tag="R0"},

    //~ }
//~ };

//~ #define LOOKUP_TABLE_LENGTH_FLOW_SENSOR 21
//~ const t_lookup_entry flow_sensor_0923_lookup[] = {      // originally used sensor
        //~ //          flow_in | flow out
        //~ //---------------------------------------------------------------------------------------------------------------
                    //~ {154    , 0},           // flow: 0 [ln/min]
                    //~ {227    , 3282},        // flow: 5 [ln/min]
                    //~ {287    , 6564},        // flow: 10 [ln/min]
                    //~ {340    , 9849},        // flow: 15 [ln/min]
                    //~ {384    , 13128},       // flow: 20 [ln/min]
                    //~ {422    , 16410},       // flow: 25 [ln/min]
                    //~ {456    , 19692},       // flow: 30 [ln/min]
                    //~ {488    , 22974},       // flow: 35 [ln/min]
                    //~ {517    , 26256},       // flow: 40 [ln/min]
                    //~ {545    , 29538},       // flow: 45 [ln/min]
                    //~ {571    , 32820},       // flow: 50 [ln/min]
                    //~ {595    , 36102},       // flow: 55 [ln/min]
                    //~ {617    , 39384},       // flow: 60 [ln/min]
                    //~ {638    , 42666},       // flow: 65 [ln/min]
                    //~ {655    , 45948},       // flow: 70 [ln/min]
                    //~ {671    , 49230},       // flow: 75 [ln/min]
                    //~ {684    , 52512},       // flow: 80 [ln/min]
                    //~ {697    , 55794},       // flow: 85 [ln/min]
                    //~ {709    , 59076},       // flow: 90 [ln/min]
                    //~ {720    , 62358},       // flow: 95 [ln/min]
                    //~ {729    , 65535},       // flow: 100 [ln/min]
//~ };                                                              ///< flow sensor 0923 table, returns necessary PWM ratio

//~ const t_lookup_entry flow_sensor_1037_lookup[] = {      // alternative sensor
        //~ //          flow_in | flow out
        //~ //---------------------------------------------------------------------------------------------------------------
                    //~ {154    , 0},           // flow: 0 [ln/min]
                    //~ {224    , 3282},        // flow: 5 [ln/min]
                    //~ {284    , 6564},        // flow: 10 [ln/min]
                    //~ {337    , 9849},        // flow: 15 [ln/min]
                    //~ {383    , 13128},       // flow: 20 [ln/min]
                    //~ {423    , 16410},       // flow: 25 [ln/min]
                    //~ {460    , 19692},       // flow: 30 [ln/min]
                    //~ {492    , 22974},       // flow: 35 [ln/min]
                    //~ {519    , 26256},       // flow: 40 [ln/min]
                    //~ {546    , 29538},       // flow: 45 [ln/min]
                    //~ {569    , 32820},       // flow: 50 [ln/min]
                    //~ {590    , 36102},       // flow: 55 [ln/min]
                    //~ {609    , 39384},       // flow: 60 [ln/min]
                    //~ {626    , 42666},       // flow: 65 [ln/min]
                    //~ {641    , 45948},       // flow: 70 [ln/min]
                    //~ {655    , 49230},       // flow: 75 [ln/min]
                    //~ {667    , 52512},       // flow: 80 [ln/min]
                    //~ {678    , 55794},       // flow: 85 [ln/min]
                    //~ {689    , 59076},       // flow: 90 [ln/min]
                    //~ {698    , 62358},       // flow: 95 [ln/min]
                    //~ {705    , 65535},       // flow: 100 [ln/min]
//~ };                                                              ///< flow sensor 1037 table, returns necessary PWM ratio

/**
 * scheduler function
 *
 * is launched by watchdor timer
 * 
 * The watchdog is programmed as intervall timer. 
 * 
 * This function is called periodicaly and it launches the scheduler.
 */
wakeup interrupt(WDT_VECTOR) intervallTimer(void) {
    scheduler_increment();
    EVENTHANDLER_LAUNCH(EVENT_scheduler);
}

/**
 * 
 */
uint16_t convert_bargraph(uint16_t value, uint16_t normalized) {
    uint16_t div;
    uint16_t led;
    uint32_t value_large;
    value_large = (uint32_t)value * 1000;
    div = value_large/normalized;
    //~ i2c_slave_image.row_fv.reserved[2] = div;

    if(div >=   0  && div <  775) led = BIT0;
    if(div >=  775 && div <  825) led = BIT1;
    if(div >=  825 && div <  875) led = BIT2;
    if(div >=  875 && div <  925) led = BIT3;
    if(div >=  925 && div <  975) led = BIT4;
    if(div >=  975 && div < 1025) led = BIT5;
    if(div >= 1025 && div < 1075) led = BIT6;
    if(div >= 1075 && div < 1125) led = BIT7;
    if(div >= 1125 && div < 1175) led = BIT8;
    if(div >= 1175 && div < 1225) led = BIT9;
    if(div >= 1225)               led = BITA;
    //~ i2c_slave_image.row_fv.reserved[3] = led;
    return led;
    }

/**
 * Flow update function
 * 
 * updates the flow output
 */
void event_flow_update(void) {
    uint16_t flow;
    uint16_t led;
    static uint16_t flow_normalized;
    flow = read_flow_in();
    //~ i2c_slave_image.row_fv.flow_in = flow;
    //~ flow = lookup(flow_sensor_1037_lookup, LOOKUP_TABLE_LENGTH_FLOW_SENSOR, flow);
    //~ i2c_slave_image.row_fv.flow_out = flow;
    write_flow_out(flow);
    if(check_button()){
        flow_normalized = flow;
    }
    led = convert_bargraph(flow, flow_normalized);
    update_led(led);
    //~ i2c_slave_image.row_fv.reserved[0] = flow_normalized;
    //~ i2c_slave_image.row_fv.reserved[1] = led;
}

/**
 * Table with the event handlers
 * 
 * NOTE: must keep it in sync with the EVENT_* defines above!
 */
const EVENTHANDLER_TABLE eventhandler_table[] = {
    event_scheduler,
    event_flow_update,
    0 // sentinel, marks end of list
};

/**
 * I2C interrupt, the EEPROM read/write behavior is implemented here.  The
 * actual write back and callbacks are processed in the other interrupt handler
 * below.
 */
//~ wakeup interrupt(USCIAB0TX_VECTOR) i2c_interrupt_rxtx(void) {
    //~ uint8_t *read_pointer;
    //~ // DEBUG_P27_ON(); // wakin' up
    //~ /* Possible interrupt flags:
    //~ IFG2: UCB0RXIFG (BIT3), UCB0TXIFG (BIT2)
    //~ */
    //~ if (IFG2 & UCB0RXIFG) {
        //~ switch (i2c_state) {
            //~ case 0:         // 1st byte -> i2c_ee_address high1 byte
                //~ i2c_ee_address = (uint8_t)UCB0RXBUF << 8;
                //~ i2c_state++;
                //~ break;
            //~ case 1:         // 2nd byte -> i2c_ee_address low byte
                //~ i2c_ee_address |= (uint8_t)UCB0RXBUF;
                //~ i2c_state++;
                //~ break;
            //~ default:
                //~ //writeback = true;
                //~ if (0x0000 <= i2c_ee_address && i2c_ee_address < sizeof(i2c_slave_image)) {
                    //~ // copy row to buffer
                    //~ ((uint8_t *)&i2c_slave_image)[i2c_ee_address] = UCB0RXBUF;
                    //~ i2c_ee_address++;
                //~ }
                //~ i2c_state++;
        //~ }
    //~ }
    //~ if (IFG2 & UCB0TXIFG) {
        //~ // read from the reserved memory, wrap around address pointer
        //~ if (0x0000 <= i2c_ee_address && i2c_ee_address < sizeof(i2c_slave_image)) {
            //~ read_pointer = &((uint8_t *)&i2c_slave_image)[i2c_ee_address];
        //~ }
        //~ else {
            //~ // read 0xff in all other cases
            //~ read_pointer = "\xff";
        //~ }
        //~ UCB0TXBUF = *read_pointer;
        //~ i2c_ee_address++;
    //~ }
//~ }

//~ /**
 //~ * I2C interrupt for start and stop-conditions
 //~ * Finish writes and do callbacks. These are done at the end of a I2C
 //~ * transfer, the stop condition.
 //~ * note that RX_VECTOR is for SPI, in I2C it means status interrupts (start-stop-condition, NACK, Arbitration lost)
 //~ */
//~ wakeup interrupt(USCIAB0RX_VECTOR) i2c_interrupt_stat(void) {
    //~ //DEBUG_P27_ON(); // wakin' up
    //~ if(UCB0STAT & UCSTTIFG) {
        //~ // I2C start condition
        //~ i2c_state = 0;
        //~ UCB0STAT &= ~UCSTTIFG; // clear start-interrupt flag
    //~ }
    //~ if(UCB0STAT & UCSTPIFG) {
        //~ // I2C stop condition
        //~ //handle_writes_and_callbacks();
        //~ UCB0STAT &= ~UCSTPIFG; // clear stop-interrupt flag
    //~ }
//~ }

/**
 * Program entry. 
 *
 * Set up the hardware and launch the eventhandler.
 * 
 * Updates the key code
 */
int main(void) {
    hardware_lowlevel_init();
    eint();
    eventhandler(EVENT_flow_update); // enter eventhandler, start event for a first time
}
