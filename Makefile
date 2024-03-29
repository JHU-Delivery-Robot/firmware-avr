include buildcfg/update_root.mk
PROJECT_ROOT  := .
REL_ROOT      := ..
include $(CFGDIR)/verify_version.mk


.DEFAULT_GOAL := all

# metatargets
.PHONY: all
all: ir ultrasonic examples

.PHONY: ir ultrasonic
ir ultrasonic: common_deps
	$(MAKE) -C src $@

.PHONY: examples
# recursive targets
examples: common_deps
	$(MAKE) -C examples

# dep targets
.PHONY: common_deps
common_deps: _check_lib_vers vendor | $(HEXDIR)

.PHONY: vendor
vendor:
	$(MAKE) -C $(LIBROOT)

# utility targets
COMPILEDB_SED := s|   "avr-gcc",|   "arm-none-eabi-gcc",\n   $\
                      "-D__AVR_ATtiny816__",\n   $\
                      "-D__AVR_DEVICE_NAME__=attiny816",\n   $\
                      "-D__AVR_DEV_LIB_NAME__=tn816",|
.PHONY: compiledb
compiledb:
	rm -f compile_commands.json
	$(MAKE) -Bnkw V=0 all > build.log
	compiledb < build.log
	@echo "Fixing compile_commands.json"; sed -i '$(COMPILEDB_SED)' compile_commands.json
ifeq ($(PLATFORM), Msys)
# windows pathfix
	@echo "Applying windows fixes to compile_commands.json";sed -i 's|/c/|/|' compile_commands.json
endif
	rm -f build.log

.PHONY: clean
clean:
	rm -rf $(HEXDIR)
	$(call_recursive)
.PHONY: libclean
libclean:
	$(MAKE) -C $(LIBROOT) clean

# special make targets
$(HEXDIR):
	@mkdir -p $@

# utilities
define call_recursive
	$(MAKE) -C examples $@
	$(MAKE) -C src $@
endef
