include update_root.mk

.PHONY: all
all: blink usart

.PHONY: blink
blink:
	$(MAKE) -C $@

.PHONY: usart
usart:
	$(MAKE) -C $@

.PHONY: clean compiledb
clean compiledb:
	$(MAKE) -C blink $@
