#include "init.h"
#include "globals.h"
#include "motorcontrol.h"
#include "DRV10983.h"


#include "stdbool.h"
#include "stdint.h"


#include <avr/io.h>
#include <avr/interrupt.h>
#include "bit_utils.h"

void update_motor_speed(uint16_t speed_cmd) {
    //read SpeedCtrl2
    i2c_init()
    i2c_start(DRV10983, 0); //start write transaction
    i2c_write(SpeedCtrl2); //write SpeedCtrl2 address
    i2c_start(DRV10983, 1); //start read transaction
    uint8_t spdctrl2_data = i2c_read_auto(); //read SpeedCtrl2 data

    //edit only SpeedCtrl MSB
    bool msb_desired = (bool) (speed_cmd >> 8); //read 8th bit (msb) from command
    if (msb_desired == 1) {
        spdctrl2_data |= (1<<7); // set msb to 1
    } else {
        spdctrl2_data &= !(1<<7); // set msb to 0
    }

    //write SpeedCtrl2
    i2c_start(DRV10983, 0); //start write transaction
    i2c_write(SpeedCtrl2); //write SpeedCtrl2 address
    i2c_write(spdctrl2_data); //write data byte

    //write SpeedCtrl1
    uint8_t spdctrl1_data = (uint8_t) speed_cmd; //get last 8 bits of speed control command
    i2c_start(DRV10983, 0); //start write transaction
    i2c_write(SpeedCtrl1); //write SpeedCtrl2 address
    i2c_write(spdctrl1_data); //write data byte

    i2c_stop();

}

void send_motor_state() {
    //just speed for now, will eventually encode dir and possibly others

}
