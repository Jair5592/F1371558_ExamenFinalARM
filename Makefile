CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

CFLAGS = -mcpu=cortex-m3 -mthumb --specs=nosys.specs
LDSCRIPT = stm32f103c8tx_flash.ld

SRC_FILES = startup_stm32f103c8tx.s main.c .\motorDriver\motorDriver.c .\serialUart\serialUart.c .\tiempoEspera\tiempoEspera.c

OUTPUT = main.elf
OUTPUT_BIN = main.bin

FLASH_START_ADDR = 0x08000000

all: $(OUTPUT) $(OUTPUT_BIN)

$(OUTPUT): $(SRC_FILES) $(LDSCRIPT)
	$(CC) $(CFLAGS) -T $(LDSCRIPT) $(SRC_FILES) -o $@

$(OUTPUT_BIN): $(OUTPUT)
	$(OBJCOPY) -O binary $< $@

flash: $(OUTPUT_BIN)
	st-flash write $< $(FLASH_START_ADDR)

clean:
	rm -f $(OUTPUT) $(OUTPUT_BIN)

.PHONY: all flash clean