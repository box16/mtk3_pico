################################################################################
# micro T-Kernel 3.0 BSP  makefile
################################################################################

OBJS += \
./mtkernel_3/device/i2c/i2c.o 

C_DEPS += \
./mtkernel_3/device/i2c/i2c.d 

mtkernel_3/device/i2c/%.o: ../device/i2c/%.c
	@echo 'Building file: $<'
	$(GCC) $(CFLAGS) -D$(TARGET) $(INCPATH) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

ifeq ($(TARGET), _PICO_RP2040_)
-include mtkernel_3/device/i2c/sysdepend/rp2040/subdir.mk
endif
