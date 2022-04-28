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

#define SENSOR_PREFIX "/sys/class/lego-sensor/"

typedef struct Sensor
{
    char command[256];                                  // command file path
    char value[256];                                    // value<N> file path
    char mode[256];                                     // mode file path
    char decimals[256];                                 // decimlas file path
    char num_values[256];                               // num_values file path
    double decimal;                                     // decimals constant
    int value_len;                                      // strlen() of value
    // int value_count;                                    // number of read values for the given sensor mode - uncomment if need be
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