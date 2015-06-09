-include ../../config.mk
-include ../../tools/kconfig/.config

PREFIX?=$(PWD)/build
CC?=gcc
AR?=ar
RANLIB?=ranlib
OBJS:=dummy.o

CFLAGS += $(EXTRA_CFLAGS)

all: $(PREFIX)/lib/bsp.a

%.o: Src/%.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(PREFIX)/lib/bsp.a: $(OBJS)
	@touch $@
	@mkdir -p $(PREFIX)/obj
	@cp $(OBJS) $(PREFIX)/obj

clean:
	rm -f *.o *.a
