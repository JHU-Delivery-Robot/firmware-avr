#ifndef _DRV10983_H_
#define _DRV10983_H_


// R/W
#define SpeedCtrl1 0x00
#define SpeedCtrl2 0x01
#define DevCtrl 0x02
#define EECtrl 0x03 

// Read-only
#define Status 0x10
#define MotorSpeed1 0x11
#define MotorSpeed2 0x12 
#define MotorPeriod1 0x13 
#define MotorPeriod2 0x14 
#define MotorKt1 0x15 
#define MotorKt2 0x16 
#define MotorCurrent1 0x17 
#define MotorCurrent2 0x18 
#define IPDPosition 0x19 
#define SupplyVoltage 0x1A
#define SpeedCmd 0x1B
#define spdCmdBuffer 0x1C
#define FaultCode 0x1E

// EEPROM
#define MotorParam1 0x20 
#define MotorParam2 0x21
#define MotorParam3 0x22
#define SysOpt1 0x23
#define SysOpt2 0x24
#define SysOpt3 0x25
#define SysOpt4 0x26
#define SysOpt5 0x27
#define SysOpt6 0x28
#define SysOpt7 0x29
#define SysOpt8 0x2A
#define SysOpt9 0x2B



#endif 