/**
 * System initialization functions implementation
 */
#include "init.h"
#include "globals.h"
#include "motorcontrol.h"
#include "DRV10983.h"

//TODO: should I include all of these? 
#include "stdint.h"
#include "bit_utils.h" 
#include <avr/io.h>


void AppInit() {

    i2c_init(); //initialize I2C using i2c_init

    i2c_start(SpeedCtrl2, 8);  // start read transaction
    uint8_t spdctrl2_data = i2c_read(); // get current speedctrl2 value
    i2c_stop(); // end read transaction

    spdctrl2_data |= (1<<0); // set override bit to 1 to disable speed pin
    spdctrl2_data &= !(1<<7); // clear MSB of motor command 

    i2c_restart(SpeedCtrl2, 0); // start write transaction
    i2c_write(spdctrl2_data); 
    i2c_stop();

    //clear the rest of the motor command bits
    uint8_t spdctrl1_data = 0; // TODO: can I do this to clear all bits (back to 0)?
    i2c_start(SpeedCtrl1,0);
    i2c_write(spdctrl1_data); 
    i2c_stop();


}
