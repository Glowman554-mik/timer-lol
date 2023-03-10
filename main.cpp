/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <lcd.hpp>

DigitalOut led(LED1);

int main() {
    RCC->APB1ENR |= 0b00010000; // enable tim6 clock
    TIM6->PSC = 31999; // set prescaler
    TIM6->ARR = 1000; // set auto reload
    TIM6->CNT = 0; // set count
    TIM6->SR = 0; // set flag
    TIM6->CR1 = 1; // enable

    software_lcd lcd;
    lcd.set_flags(LCD_CURSOR | LCD_CURSOR_BLINK);
    lcd.clear();

    int s = 0;
    while (true) {
        while (!TIM6->SR);
        TIM6->SR = 0;
        s++;

        int seconds = s % 60;
        int minutes = (s / 60) % 60;
        int hours = (s / 60) / 60;

        char out[0xff] = { 0 };
        sprintf(out, "%2d:%2d:%2d", hours, minutes, seconds);
        lcd.cursor(0);
        lcd.puts(out);
    }
}
