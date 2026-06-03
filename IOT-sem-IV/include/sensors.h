#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include "config.h"

int readMQ2()
{
    return analogRead(MQ2_PIN);
}

int readMQ135()
{
    return analogRead(MQ135_PIN);
}

#endif