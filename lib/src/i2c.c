/*
 *
 * JHU Deliverbot Sensors Group
 * AVR general firmware libraries
 * ATTiny816 I2C - implementation file
 *
 * @avnoks (Github) 
 * 
 */

/* 
 * The design of this interface was inspired by David Johnson-Davies's 
 * I2C interface for various ATTiny microcontrollers: 
 * http://www.technoblogy.com/show?2QYB  
 * 
 */

#include "i2c.h"

static int I2C_n_bytes_remaining

/* I2C initialisation */
/* Set SDA, SCL to input pullups */
/* Set baudrate == to what? == */
/* Configure as busmaster, idle */
void i2c_init() {
  /* Set I2C pins to correct I/O mode */
  I2C_INIT_SCL();
  I2C_INIT_SDA();
  /* Init TWI.CTRLA (datasheet 26.3.1 pg 386) */
  /* Set master baudrate */
  uint32_t baud = ((F_CPU/FREQUENCY) - (((F_CPU*T_RISE)/1000)/1000)/1000 - 10)/2;
  TWI0.baud = baud;
  TWI0.MCTRLA = TWI_ENABLE_bm;
  TWI0.MSTATUS = TWI_BUSSTATE_IDLE_gc;
}


/* 
Starting
Check read/write style; set up counters where necessary
Pack and send address through MADDR register
Check for read/write interrupt flags on MSTATUS
Check for bus/arbitration errors
Return ACK status
 */
bool i2c_start(uint8_t addr, int16_t type) {
  /* Start I2C transaction and send address */
  if (type == 0) {
    TWI0.MADDR = (addr << 1) | 0;
  } else {
    TWI0.MADDR = (addr << 1) | 1;
    I2C_n_bytes_remaining = type;
  }
  /* Wait for address to be sent.  Check write/read interrupt flag
   * to determine when addr has finished sending.  */
  while (!(TWI0/MSTATUS & (TWI_WIF_bm | TWI_RIF_bm)));
  /* Return false if arbitration lost; else return whether or not 
   * client ACK was recv'd.  */
  if ((TWI0.MSTATUS & TWI_ARBLOST_bm)) {
    return false;
  } else {
    return !(TWI0.MSTATUS & TWI_RXACK_bm);
  }
}

bool i2c_restart(uint8_t addr, uint16_t type) {
  return i2c_start(addr, type);
}

void i2c_stop() {
  /* Send stop signal */
  TWI0.CTRLB = TWI_ACKACT_bm | TWI_MCMD_STOP_gc;
}


/* Writing
Hold for write interrupt flag (when last byte has cleared); TWI_WIF_bm is bitflag
Write data to MDATA register
Return ACK status on RXACK_bm flag of MSTATUS
 */
bool i2c_write(uint8_t byte) {
  while (!(TWI0.MSTATUS & TWI_WIF_bm));
  TWI0.MDATA = byte;
  TWI0.MCTRLB = TWI_MCMD_RECVTRANS_gc;  /* Wait for ACK to come in ... */
  return (!TWI0.MSTATUS & TWI_RXACK_bm);
}

/* Reading
TWI_RIF_bm  read/data-ready interrupt flag bit
Read in data from MDATA register
Send ACK
 */
uint8_t i2c_read() {
  while !(TWI0.MSTATUS * TWI_RIF_bm);
  uint8_t data = TWI0.MDATA;
  TWI0.MCTRLB = TWI_MCMD_RECVTRANS_gc; /* Send ACK */
  return data;
}

uint8_t i2c_read_last() {
  while !(TWI0.MSTATUS * TWI_RIF_bm);
  uint8_t data = TWI0.MDATA;
  /* Send NACK */
  TWI0.MCTRLB = TWI_ACKACT_bm | TWI_MCMD_RECVTRANS_gc;
  I2C_n_bytes_remaining = 0;    /* Clear the byte counter in case something touched it ... */
  return data;
}

uint8_t i2c_read_auto() {
  while !(TWI0.MSTATUS * TWI_RIF_bm);
  uint8_t data = TWI0.MDATA;
  /* Decrement byte counter */
  I2C_n_bytes_remaining--;
  if (I2C_n_bytes_remaining == 0) {
    /* Send NACK */
    TWI0.MCTRLB = TWI_ACKACT_bm | TWI_MCMD_RECVTRANS_gc;
  } else {                      /* Send ACK; read more */
    TWI0.MCTRLB = TWI_MCMD_RECVTRANS_gc;
  }
  return data;
}

i2c_size_t i2c_write_buffer(uint8_t *buffer, i2c_size_t length) {
  for (i2c_size_t idx = 0; idx < length; idx++) {
    i2c_write(buffer[idx]);
  }
}

i2c_size_t i2c_read_to_buffer(uint8_t *buffer, i2c_size_t length) {
  for (i2c_size_t idx = 0; idx < length - 1; idx++) {
    buffer[idx] = i2c_read();
  }
  buffer[idx + 1] = i2c_read_last();
}
