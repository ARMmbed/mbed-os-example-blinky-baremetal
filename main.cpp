/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#define WAIT_TIME 500 //msec

DigitalOut led1(LED1);

int main()
{
    while (true)
    {
        led1 = !led1;
        thread_sleep_for(WAIT_TIME);
    }
}
