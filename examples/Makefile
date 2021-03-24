export PROJECT_ROOT
export CFGDIR
export HEXDIR
export LIBROOT
export LIBCFG
# propagate user flags
export CFLAGS

.PHONY: all
all: blink

.PHONY: blink
blink:
	$(MAKE) -C $@

.PHONY: clean compiledb
clean compiledb:
	$(MAKE) -C blink $@
