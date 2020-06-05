result.elf: main.o Makefile
	arm-none-eabi-gcc main.o $(LDFLAGS) -o $@