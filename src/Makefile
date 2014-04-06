ARCH            ?= arm
CROSS_COMPILE   ?= arm-none-eabi-
QEMU := qemu-system-arm -M versatilepb -serial stdio

AS		= $(CROSS_COMPILE)as
LD		= $(CROSS_COMPILE)ld
CC		= $(CROSS_COMPILE)gcc
CPP		= $(CC) -E
OBJCOPY		= $(CROSS_COMPILE)objcopy

CPUFLGS := -mcpu=arm926ej-s
DBGFLG := -g 

TARGET := main
OBJS := timer.o start.o main.o

.PHONY := all run clear
.SUFFIXES: .o .c .S

all: $(TARGET).bin

.c.o: 
	$(CC) $(CPUFLGS) $(DBGFLG) -c -o $@ $<
.S.o: 
	$(AS) $(CPUFLGS) -o $@ $<
	
$(TARGET): linker.ld  $(OBJS)
	$(LD) -T $^ -o $@ 

$(TARGET).bin:  $(TARGET)
	$(OBJCOPY) -O binary $< $@
	@echo "DONE : building image completed"

run: $(TARGET).bin
	@echo "Starting qemu-system-arm with the built image"
	$(QEMU) -kernel $<

clean:
	@echo "removing object files"
	rm -rf *.bin *.o $(TARGET)
