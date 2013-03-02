/* Application for the Lin-Box
 *
 * With profiling:
 *                 MSP430G2553
 */

#include <msp430.h>
//~ #include <signal.h>
//~ #include <mspgcc/util.h>                // delay()
//~ #include <mspgcc/eventhandler.h>
#include <stdbool.h>
#include "hardware.h"

#define EVENT_scheduler         EVENT00_bits
#define EVENT_hello_world       EVENT01_bits

/**
 * Table with the events that are started by the scheduler.
 */
/*const SCHEDULER_TABLE scheduler_table[] = {
    {modulo: 64, shift: 0, eventbits: EVENT_hello_world},
    {0} // sentinel, marks the end of the table
};*/

/**
 * scheduler function
 *ö8
 * is launched by watchdor timer
 * 
 * The watchdog is programmed as intervall timer. 
 * 
 * This function is called periodicaly and it launches the scheduler.
 */
/*wakeup interrupt(WDT_VECTOR) intervallTimer(void) {
    scheduler_increment();
    EVENTHANDLER_LAUNCH(EVENT_scheduler);
}*/

/**
 * Hello World
 * 
 * updates the flow output
 */
void event_hello_world(void) {
    P1OUT ^= P1_0 | P1_6;
}

/**
 * Table with the event handlers
 * 
 * NOTE: must keep it in sync with the EVENT_* defines above!
 */
/*const EVENTHANDLER_TABLE eventhandler_table[] = {
    event_scheduler,
    event_hello_world,
    0 // sentinel, marks end of list
};*/

/**
 * Program entry. 
 *
 * Set up the hardware and launch the eventhandler.
 * 
 * Updates the key code
 */
int main(void) {
    hardware_lowlevel_init();
    //~ eint();
    //~ eventhandler(EVENT_hello_world); // enter eventhandler, start event for a first time
    while(1) {
      event_hello_world();
}
}
