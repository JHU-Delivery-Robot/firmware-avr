/**
 * main (entrypoint) implementation
 */
#include "init.h"
#include "pinmap.h"
#include "DRV10983.h"
#include "motorcontrol.h"

//TODO: should I include below? 
#include "stdint.h"


void loop(void) {
    //TODO: take in incoming speed setting command with I2C (need I2C content for this)
    uint8_t raw_speed = 0; // temporary
    //TODO: convert incoming speed command into compatible motor command (update function I/O accordingly)
    uint16_t speed_cmd = convert_motor_command(raw_speed);

    //TODO: update controller speed (update function I/O accordingly)
    update_motor_speed(speed_cmd);

    //TODO: get and send current motor control state parameters (update function I/O accordingly)
    send_motor_state();

    
}

int main(void) {
    AppInit();
    for(;;) loop();
}
