%.hex: %.elf | $(BUILD_DIR)
	arm-none-eabi-objcopy -O ihex $< $@