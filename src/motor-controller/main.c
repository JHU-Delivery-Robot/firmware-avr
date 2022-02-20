/**
 * main (entrypoint) implementation
 */
#include "init.h"
#include "pinmap.h"
#include "DRV10983.h"
#include "motorcontrol.h"

void loop(void) {
    //TODO: take in incoming speed setting command with I2C (need I2C content for this)

    //TODO: convert incoming speed command into compatible motor command (update function I/O accordingly)
    convert_motor_command();

    //TODO: update controller speed
    update_controller_speed();

    //TODO: get and send current motor control state parameters
    send_motor_state();

    
}

int main(void) {
    AppInit();
    for(;;) loop();
}
