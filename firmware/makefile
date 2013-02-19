# makfile configuration

NAME            = launchpad_hello
CSOURCES        = main.c hardware.c
#~ ASOURCES        = 
CPU             = msp430g2553
PLATFORM        = launchpad_g2553


BIN_NAME = $(NAME)-$(HOST)-$(PLATFORM)

ASFLAGS         = -mmcu=${CPU} -D_GNU_ASSEMBLER_ -I .
CFLAGS          = -mmcu=${CPU} -O2 -Wall -g --std=gnu99 -I .
#~ LDFLAGS         =  -lmspgcc


VPATH += $(PROJECT_ROOT) \
         #~ $(COMMON) $(COMMON)/sys $(COMMON)/host/$(HOST) $(COMMON)/platform/$(PLATFORM) \
         #~ $(COMMON)/bus/asic $(COMMON)/bus/i2c

#switch the compiler (for the internal make rules)
CC              = msp430-gcc
AS              = msp430-gcc

OBJECTS         = ${CSOURCES:.c=.o} ${ASOURCES:.S=.o}


.PHONY: all FORCE clean download download-jtag download-bsl

#all should be the first target. it's built when make is run without args
all: ${NAME}.elf ${NAME}.a43 ${NAME}.lst dependencies.d

#confgigure the next line if you want to use the serial download
download: download-jtag
#~ download: download-bsl

#additional rules for files
${NAME}.elf: ${OBJECTS}
	${CC} -mmcu=${CPU} -o $@ ${OBJECTS} $(LDFLAGS)

${NAME}.a43: ${NAME}.elf
	msp430-objcopy -O ihex $^ $@

${NAME}.lst: ${NAME}.elf
	msp430-objdump -dSt $^ >$@
	@echo "----- RAM/Flash Usage -----"
	msp430-size $^

download-jtag: all
	python '.\programmer\device_programmer.py'

download-bsl: all
	msp430-bsl $(BSLOPT) -e ${NAME}.elf

clean:
	rm -f ${NAME}.elf ${NAME}.a43 ${NAME}.lst ${OBJECTS} dependencies.d

#dummy target as dependecy if something has to be build everytime
FORCE:

#project dependencies
dependencies.d:
	$(CC) -MM ${CFLAGS} ${CSOURCES} > dependencies.d
ifdef ASOURCES
	$(CC) -MM ${ASFLAGS} ${ASOURCES} >> dependencies.d
endif

-include dependencies.d