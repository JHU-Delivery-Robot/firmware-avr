include update_root.mk

.PHONY: all
all: ir ultrasonic

.PHONY: ir ultrasonic
ir ultrasonic:
	$(MAKE) -C $@

.PHONY: clean compiledb
clean compiledb:
	$(MAKE) -C ir $@
	$(MAKE) -C ultrasonic $@
