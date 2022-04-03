#ifndef _MOTORCONTROL_H_
#define _MOTORCONTROL_H_

/**
 * Prereqs:
 *   [None]
 * Side Effects:
 *   [None]
 * Converts speed commands recieved into interprettable motor commands
 * @param
 * @return Void
 */
uint16_t convert_motor_command(uint8_t speed) {}

/**
 * Prereqs:
 *   speed_cmd is 
 * Side Effects:
 *   only the last 9 bits of speed_cmd will be used
 * Updates the motor controller speed from motor command
 * @param speed_cmd
 * @return Void
 */
void update_motor_speed(uint16_t speed_cmd) {}


/**
 * Prereqs:
 *   [None]
 * Side Effects:
 *   [None]
 * Reads motor state params and sends out details to the rest of the robot
 * @param
 * @return Void
 */
void send_motor_state() {}


#endif 