gnux86: main.c motor.c sensor.c
	gcc motor.c sensor.c main.c -o ./build/test_gnu_x86_64

gnuARM_x_gnux86: main.c motor.c sensor.c
	arm-linux-gnueabi-gcc main.c motor.c sensor.c -o ./build/main

gnuARM_x_mingw: main.c motor.c sensor.c
	# todo
