################################################################################
# micro T-Kernel 3.0 BSP  makefile
################################################################################

TEMP_SRCS_C    := $(wildcard ../app_program/*.c)
TEMP_SRCS_CPP  := $(wildcard ../app_program/*.cpp)
TEMP_OBJS_C    := $(TEMP_SRCS_C:.c=.o)
TEMP_OBJS_CPP  := $(TEMP_SRCS_CPP:.cpp=.o)
TEMP_DEPS_C    := $(TEMP_SRCS_C:.c=.d)
TEMP_DEPS_CPP  := $(TEMP_SRCS_CPP:.cpp=.d)

OBJS    += $(subst ../, ./mtkernel_3/, $(TEMP_OBJS_C)) $(subst ../, ./mtkernel_3/, $(TEMP_OBJS_CPP))
C_DEPS  += $(subst ../, ./mtkernel_3/, $(TEMP_DEPS_C)) $(subst ../, ./mtkernel_3/, $(TEMP_DEPS_CPP))

mtkernel_3/app_program/%.o: ../app_program/%.cpp
	@echo 'Building file: $<'
	$(GPP) $(CPPFLAGS) -D$(TARGET) $(INCPATH) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

mtkernel_3/app_program/%.o: ../app_program/%.c
	@echo 'Building file: $<'
	$(GCC) $(CFLAGS) -D$(TARGET) $(INCPATH) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '