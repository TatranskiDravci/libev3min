BUILD =  main.c ../src/base/motor.c ../src/base/sensor.c ../src/extra/controller.c ../src/shared.c
FLAGS ?= -O 

all: GNU-ARM GNU-x86_64

GNU-ARM: $(BUILD)
	arm-linux-gnueabi-gcc $(FLAGS) $^ -o ./build/test_gnu_arm

GNU-x86_64: $(BUILD)
	gcc $(FLAGS) $^ -o ./build/test_gnu_x86_64
