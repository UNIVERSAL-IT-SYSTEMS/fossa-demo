include config.mk
include tools/kconfig/.config
include LDFLAGS.mk
include CFLAGS.mk
include PICOTCP.mk

SRC_DIR:=$(wildcard src/*)
ARCH_DIR:=$(wildcard hw/*)
SYS_SRC:=$(wildcard sys/*.c)
DRV_SRC:=$(wildcard drivers/*.c)
APP_SRC:=$(wildcard app/*.c)

APP_OBJ_FILES:=$(patsubst app/%.c,out/obj/%.o,$(APP_SRC))
SYS_OBJ_FILES:=$(patsubst sys/%.c,out/obj/%.o,$(SYS_SRC))
DRV_OBJ_FILES:=$(patsubst drivers/%.c,out/obj/%.o,$(DRV_SRC))

ifneq (,$(wildcard board/$(ARCH)/$(ARCH).s ))
	ARCH_SRC_FILE = board/$(ARCH)/$(ARCH).s
else
	ARCH_SRC_FILE = board/$(ARCH)/$(ARCH).c
endif

CP=$(CROSS_COMPILE)objcopy
SIZE=$(CROSS_COMPILE)size


all: out/image.hex

out/image.hex: out/image.elf
	@$(CP) out/image.elf -O binary out/image.bin
	@$(CP) out/image.elf -O srec --srec-len 19 out/image.s19
	@$(CP) out/image.elf -O ihex out/image.hex
	@echo
	@echo
	@echo "Image was created successfully. Run ./out/image.elf and assign an IP to the newly created TAP device."

out/image.elf: out/obj out/lib $(SYS_OBJ_FILES) $(APP_OBJ_FILES) $(DRV_OBJ_FILES) out/obj/sys_init.o
	$(CC) \
		-o $@  \
		-Wl,--start-group \
		out/lib/*.a \
		out/obj/*.o \
		-Wl,--end-group \
		-Wl,-Map,out/image.map \
		$(LDFLAGS) $(CFLAGS) $(EXTRA_CFLAGS);

out/lib:
	mkdir -p $(dir $@)
	@cp Makefile.fossa src/fossa/Makefile
	@cp Makefile.picotcp-bsd src/01-picotcp-bsd/Makefile
	@if (test -d picotcp); then \
		make -C picotcp $(PICO_OPTS) PREFIX=$(PWD)/out; \
	fi
	cp sys/bsp.h out/include
	for s in `echo src/* | sort`; do \
		make -C $$s PREFIX=$(PWD)/out; \
	done
	@for s in $(ARCH_DIR); do \
		make -C $$s PREFIX=$(PWD)/out; \
	done
	rm out/lib/bsp.a

out/obj:
	mkdir -p $(dir $@)

$(APP_OBJ_FILES): out/obj/%.o: app/%.c
	mkdir -p $(dir $@)
	$(CC) -c $^ $(CFLAGS) $(EXTRA_CFLAGS) $(PLATFORM_CFLAGS) -I out/include -o $@;
	mv $@ out/obj || true

$(SYS_OBJ_FILES): out/obj/%.o: sys/%.c
	@echo "SYSTEM MODULES"
	@mkdir -p $(dir $@)
	$(CC) -c $^ $(CFLAGS) $(EXTRA_CFLAGS) $(PLATFORM_CFLAGS) -I out/include -o $@;
	@mv $@ out/obj || true

$(DRV_OBJ_FILES): out/obj/%.o: drivers/%.c
	@echo "DEVICE DRIVERS"
	@mkdir -p $(dir $@)
	@mkdir -p out/include
	$(CC) -c $^ $(CFLAGS) $(EXTRA_CFLAGS) $(PLATFORM_CFLAGS) -I out/include -o $@;
	@mv $@ out/obj || true
	@cp drivers/*.h out/include

out/obj/sys_init.o: $(ARCH_SRC_FILE)
	@echo "ARCH SPECIFIC (STARTUP)"
	@mkdir -p out/obj
	$(CC) -c $^ -o $@ $(CFLAGS) $(EXTRA_CFLAGS);



clean:
	@cp Makefile.fossa src/fossa/Makefile
	@cp Makefile.picotcp-bsd src/01-picotcp-bsd/Makefile
	@if (test -d picotcp); then \
		make -C picotcp clean; \
	fi
	@for s in $(SRC_DIR); do \
		make -C $$s clean; \
	done
	@for s in $(ARCH_DIR); do \
		make -C $$s clean; \
	done
	@rm -rf out

