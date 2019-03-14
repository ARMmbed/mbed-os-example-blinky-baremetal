/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#define WAIT_TIME 500 //msec

DigitalOut led1(LED1);

int main()
{
    led1 = !led1;
    wait_ms( WAIT_TIME );
}
