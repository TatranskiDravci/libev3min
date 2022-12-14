BUILD =  main.c ../src/base/motor.c ../src/base/sensor.c ../src/shared.c
FLAGS ?= -O -Wall -Werror

all: GNU-ARM GNU-x86_64

GNU-ARM: $(BUILD)
	arm-linux-gnueabi-gcc -I../include $(FLAGS) $^ -o ./build/test_gnu_arm

GNU-x86_64: $(BUILD)
	gcc $(FLAGS) $^ -I../include -o ./build/test_gnu_x86_64
