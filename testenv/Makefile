BUILD =  main.c ../src/motor.c ../src/sensor.c

all: GNU-ARM GNU-x86_64

GNU-ARM: $(BUILD)
	arm-linux-gnueabi-gcc $^ -o ./build/test_gnu_arm

GNU-x86_64: $(BUILD)
	gcc $^ -o ./build/test_gnu_x86_64
