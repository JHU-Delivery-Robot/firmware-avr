# Tools Defs:
CC      := avr-gcc
CXX     := avr-g++
LD      := avr-gcc
READELF := avr-readelf
OBJCOPY := avr-objcopy
SIZE    := avr-size

# Compact printers
_P_CC_1     = @echo "  CC       $<";
_P_CXX_1    = @echo "  CXX      $<";
_P_AS_1     = @echo "  AS       $<";
_P_AR_1     = @echo "  AR       $@";
_P_LD_1     = @echo "  LD       $@";
_P_OBJCPY_1 = @echo "  OBJCOPY  $@";
_P_HEX_1    = @echo "  HEX      $@";
_P_BIN_1    = @echo "  BIN      $@";
_P_SIZE_1   = @echo "  SIZE     $<";

# compact print enabled by default
ifndef V
	V := 1
endif
