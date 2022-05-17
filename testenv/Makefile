BUILD =  main.c ../src/motor.c ../src/sensor.c

GNU-ARM: $(BUILD)
	arm-linux-gnueabi-gcc $^ -o ./build/test_gnu_arm

GNU-x86_64: $(BUILD)
	gcc $^ -o ./build/test_gnu_x86_64
