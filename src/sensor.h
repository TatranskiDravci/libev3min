/*
    devnote:
        Drivers should be kept in a bare-minimum state to ensure
        flexibility and efficiency. Avoid providing higher level
        functionality than necessary.

        All code here is ev3 specific.

        p.v. - possible values

        Check https://docs.ev3dev.org/projects/lego-linux-drivers/en/ev3dev-stretch/sensors.html#sysfs
        for more info on sensors.
*/
#ifndef SENSOR_H
#define SENSOR_H

#include "config.h"

typedef struct Sensor
{
    char command[PATH_LEN];                             // command file path
    char value[PATH_LEN];                               // value<N> file path
    char mode[PATH_LEN];                                // mode file path
    char decimals[PATH_LEN];                            // decimals file path
    double decimal;                                     // decimals constant
    int value_len;                                      // strlen() of value
    int exists;                                         // sensor existence (p.v. 1 - exists, 0 - does not exist)
}
sensor;

sensor sensorNew(char port);                            // `sensor` constructor, initializes `sensor` type
void sensorSetMode(sensor s, char *mode);               // sets sensor mode (to fix decimals and values run sensorReset right after calling sensorSetMode)
void sensorCommand(sensor s, char *command);            // sends command to sensor
int sensorRead(sensor s, char n);                       // reads nth value on sensor (n must be char)
double sensorReadDecimal(sensor s, char n);             // reads nth value on sensor and converts it to actual decimal reading (n must be char)
void sensorReset(sensor *s);                            // resets sensor and recaches decimal and value_count


#endif
