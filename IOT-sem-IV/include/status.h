#ifndef STATUS_H
#define STATUS_H

#include <Arduino.h>
#include "config.h"

String getStatus(int mq2, int mq135)
{
    if (mq2 > DANGER_THRESHOLD ||
        mq135 > DANGER_THRESHOLD)
    {
        return "DANGER";
    }

    if (mq2 > SAFE_THRESHOLD ||
        mq135 > SAFE_THRESHOLD)
    {
        return "WARNING";
    }

    return "SAFE";
}

#endif