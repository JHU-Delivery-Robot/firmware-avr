#include <stdint.h>
#include <stdbool.h>

/* Read, write mode flags for use with i2c_start(), i2c_restart() */
#define I2C_WRITE 0
#define I2C_READ -1

typedef uint16_t i2c_size_t;

/* **********************************************************************
 * Functions 
 */

/* Initialise I2C system.  You must call this function before calling 
 * any of the other I2C functions.  */
void i2c_init();

/*
 * Start an I2C transaction.
 * Arguments  
 *   addr : 7-bit I2C address.  Automagically sets appends read/write bit
 *     depending on the type argument.
 *   type : Indicates type of I2C transaction; signed 16-bit integer.  
 *     0  -> I2C write transaction.  Write byte with i2c_write().
 *       Transaction macro: I2C_WRITE
 *     -1 -> Read transaction of unspecified length.  All but the last 
 *       bytes are read using i2c_read().  The last byte must be read
 *       using i2c_read_last().
 *       Transaction macro: I2C_READ
 *     [1 -- 32767] -> Read transaction of definite length.  Number of 
 *       bytes to read is argument value [1 -- 32767].  
 *       Bytes must be read using i2c_read_auto().
 * Returns 
 *   true if start was sucessful; false if something went wrong.
 */
bool i2c_start(uint8_t addr, int16_t type);

/* Restart an I2C transaction.  Arguments and return-value are the same 
 * as i2c_start(). */
bool i2c_restart(uint8_t addr, uint16_t type);
/* Finish an I2C transaction. */
void i2c_stop();

/* Write a byte to I2C device in ongoing transaction.  Returns true 
 * if device ACKnowledges write; returns false if N ACKnowledge was 
 * detected. */
bool i2c_write(uint8_t byte);

/* Yes, there are three different single-byte read functions.  Enjoy. */

/* 
 * Read a byte in an I2C read transaction of unspecified length.
 * Returns byte.  
 * Do not use this function to read the last byte in a transaction.
 */
uint8_t i2c_read();

/* 
 * Read the last byte in an I2C read transaction of unspecified length.  
 * Returns byte and sends NACK to terminate read.  
 * ATTN: To close the I2C transaction itself, you still must call 
 * i2c_stop() after calling this function to transmit a stop condition.  
 *   --> This function does not send a stop condition.  It only sends a NACK.
 */
uint8_t i2c_read_last();

/* 
 * Read a byte in an I2C transmit of specified length.  
 * Automatically tracks how many bytes remain to be read in the transaction.  
 * When no more bytes remain to be read, the function transmits a NACK.  
 * ATTN: To close the I2C transaction itself, you still must call 
 * i2c_stop() to transmit a stop condition after this function reads the 
 * last byte in the transaction.
 *   --> This function does not send a stop condition.  It only sends a NACK
 *       after the last byte is read.
 */
uint8_t i2c_read_auto();


/* Fancy buffer functions */

/* Write length bytes from the contents of an array of unsigned bytes
 * to I2C device in ongoing transaction */
i2c_size_t i2c_write_buffer(uint8_t *buffer, i2c_size_t length);
/* Read length bytes from I2C device to an array of unsigned bytes 
 * in ongoing transaction.  Transaction should be opened with using 
 * I2C_READ as type argument to i2c_start()/i2c_restart(). */
i2c_size_t i2c_read_to_buffer(uint8_t *buffer, i2c_size_t length);



/* **********************************************************************
 * Usage examples
 */

/* 

uint8_t addr = 0x5A;     // Arbitrary made-up address

i2c_init();  

// Write two bytes  
i2c_start(addr, I2C_WRITE);  
i2c_write(0xA2);  // Optionally, use return-value to see if write was sucessful.
i2c_write(0xF0);  
i2c_stop();  

// Read a few bytes in a transaction whose length is not specified at the start.
i2c_start(addr, I2C_READ);
uint8_t byte1 = i2c_read();  
uint8_t byte2 = i2c_read();  
uint8_t byte_last = i2c_read_last();  
i2c_stop();  

// Read a few bytes in a transaction whose length *is* specified at the start.  
i2c_start(addr, 5);
for (uint8_t i = 0; i < 5; i++) { 
  process(i2c_read_auto());
}
i2c_stop();

// Buffer examples
uint8_t buffer[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 10};  // BUT WHAT HAPPENED TO 9?  
i2c_start(addr, I2C_WRITE);  
i2c_write_buffer(buffer, 10);  
i2c_stop();  

i2c_start(addr, I2C_READ);  
i2c_read_buffer(buffer, 10);  
i2c_stop();  
 */
