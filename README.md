# ev3dev-clib-min
(Somewhat) minimalist C/C++ EV3 API

## Project structure
 - **`src/`** - contains API .c and .h files
    - `motor(.c, .h)` - motor control module
    - `sensor(.c, .h)` - sensor control module
    - `shared(.c, .h)` - shared macros and functions
    - `config.h` - configures path prefixes
 - **`testenv/`** - testing environment
    - **`build/`** - compiled testing programs
        - `test_gnu_arm` - compiled for ARM architecture
        - `test_gnu_x86_63` - compiled for x86_64 architecture
    - **`sys/class/lego-sensor/sensor0/`** - lego sensor emulator
    - **`sys/class/tacho-motor/motor0/`** - lego motor emulator
    - `main.c` - main testing program
    - `Makefile` - instructions for GNU-ARM and GNU-x86_64 compilation

## Using testenv
Testenv allows for debugging and testing of API functionality on x86_64 machines without the need for an ARM processor or arm-linux-gnueabi toolchain.
### Configuring `config.h`
When using ev3dev-clib-min on a lego robot, path prefixes in `config.h` should be absolute, as the `/sys/` directory is located in `/`
```c
#define PATH_LEN 23
#define SENSOR_PREFIX "/sys/class/lego-sensor/"
#define MOTOR_PREFIX  "/sys/class/tacho-motor/"
```
When using ev3dev-clib-min in testenv, however, path prefixes **must be relative** to the current directory, `./` (if the program is ran in `testenv/` director, that is)
```c
#define PATH_LEN 24
#define SENSOR_PREFIX "./sys/class/lego-sensor/"
#define MOTOR_PREFIX  "./sys/class/tacho-motor/"
```
Notice the change in `PATH_LEN`. `PATH_LEN` describes the string lenght of both `SENSOR_PREFIX` and `MOTOR_PREFIX`. Currently there is no reason for two separate `PATH_LEN`s as in ev3dev and in testenv, both have the same length.
### Building and executing
(Assuming the testing code is situated in `main.c`) To build a testing program, execute
```sh
make GNU-x86_64
```
The resulting executable binary can then be found in `build/` and will be named `test_gnu_x86_64` and can be executed using
```sh
./build/test_gnu_x86_64
```
