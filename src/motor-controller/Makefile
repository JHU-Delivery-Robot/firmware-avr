###################################################
#            BEGIN MAKEFILE SETTINGS              #
###################################################
CFLAGS     +=
INCLUDES   +=
LDFLAGS    +=
LDLIBS     +=
LDLIBS_END +=

# Add all subdirectories here separated by the : char
vpath %.c .
# Project name (sets outputted bins)
PROJ_NAME := motor-controller
# Project deps
# add all object dependencies here without the .o extension
PROJ_OBJS := main globals handlers init motorcontrol

###################################################
#            BEGIN MAKEFILE INCLUDES              #
###################################################
include update_root.mk
include $(LIBCFG)/attiny816.mk
include $(CFGDIR)/project.mk 
