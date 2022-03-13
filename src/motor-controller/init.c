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

    //clear MSB bit and set override bit
    i2c_start(DRV10983, 0); //start write transaction
    i2c_write(SpeedCtrl2); //write address of register
    uint8_t spdctrl2_data = 0;
    spdctrl2_data |= (1<<0); // set override bit to 1 to disable speed pin
    i2c_write(spdctrl2_data); //write data byte
    i2c_stop(); //stop transaction

    //clear the rest of the motor command bits
    i2c_restart(DRV10983,0);
    i2c_write(SpeedCtrl1); //write address of register
    uint8_t spdctrl1_data = 0; 
    i2c_write(spdctrl1_data); 
    i2c_stop();


    /*
    uint8_t spdctrl2_data = 0;
    spdctrl2_data |= (1<<0); // set override bit to 1 to disable speed pin

    //spdctrl2_data &= !(1<<7); // clear MSB of motor command 

    i2c_restart(DRV10983, 0); // start write transaction
    i2c_write(spdctrl2_data); 
    i2c_stop();
    */



}
