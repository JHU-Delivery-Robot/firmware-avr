export PROJECT_ROOT
export CFGDIR
export LIBROOT
export LIBCFG
# propagate user flags
export CFLAGS

.PHONY: all
all: ir ultrasonic

.PHONY: ir ultrasonic
ir ultrasonic:
	$(MAKE) -C $@

.PHONY: clean compiledb
clean compiledb:
	$(MAKE) -C ir $@
	$(MAKE) -C ultrasonic $@
