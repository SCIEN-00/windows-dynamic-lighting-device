/*
  Copyright (c) 2014-2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "variant.h"

/*
 * Pins descriptions for Seeed XIAO SAMD21
 */
const PinDescription g_APinDescription[] =
    {
        // 0..13 - Digital pins
        // ----------------------
        // 0/A0
        {PORTA, 2, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel0, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2},
        // 1/A1
        {PORTA, 4, PIO_ANALOG, (PIN_ATTR_DIGITAL | PIN_ATTR_ANALOG), ADC_Channel4, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_4},
        // 2/A2
        {PORTA, 10, PIO_ANALOG, (PIN_ATTR_DIGITAL | PIN_ATTR_PWM | PIN_ATTR_TIMER | PIN_ATTR_ANALOG), ADC_Channel18, PWM0_CH2, TCC0_CH2, EXTERNAL_INT_10},
        // 3/A3
        {PORTA, 11, PIO_ANALOG, (PIN_ATTR_DIGITAL | PIN_ATTR_PWM | PIN_ATTR_TIMER | PIN_ATTR_ANALOG), ADC_Channel19, PWM1_CH1, TCC1_CH1, EXTERNAL_INT_11},
        // 4/A4/SDA
        {PORTA, 8, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL | PIN_ATTR_PWM | PIN_ATTR_TIMER | PIN_ATTR_ANALOG), ADC_Channel16, PWM0_CH0, TCC0_CH0, EXTERNAL_INT_NMI},
        // 5/A5/SCL
        {PORTA, 9, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL | PIN_ATTR_PWM | PIN_ATTR_TIMER | PIN_ATTR_ANALOG), ADC_Channel17, PWM0_CH1, TCC0_CH1, EXTERNAL_INT_9},
        // 6/A6/TX
        {PORTB, 8, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL | PIN_ATTR_PWM | PIN_ATTR_TIMER | PIN_ATTR_ANALOG), ADC_Channel2, PWM4_CH0, TC4_CH0, EXTERNAL_INT_8},
        // 7/A7/RX
        {PORTB, 9, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL | PIN_ATTR_PWM | PIN_ATTR_TIMER | PIN_ATTR_ANALOG), ADC_Channel3, PWM4_CH1, TC4_CH1, EXTERNAL_INT_9},
        // 8/A8/SCK
        {PORTA, 7, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL | PIN_ATTR_PWM | PIN_ATTR_TIMER | PIN_ATTR_ANALOG), ADC_Channel7, PWM1_CH1, TCC1_CH1, EXTERNAL_INT_7},
        // 9/A9/MISO
        {PORTA, 5, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL | PIN_ATTR_PWM | PIN_ATTR_TIMER | PIN_ATTR_ANALOG), ADC_Channel5, PWM0_CH1, TCC0_CH1, EXTERNAL_INT_5},
        // 10/A10/MOSI
        {PORTA, 6, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL | PIN_ATTR_PWM | PIN_ATTR_TIMER | PIN_ATTR_ANALOG), ADC_Channel6, PWM1_CH0, TCC1_CH0, EXTERNAL_INT_6},

        // 11..12 - RX/TX LEDS (not broken out)
        // --------------------
        {PORTA, 17, PIO_DIGITAL, (PIN_ATTR_DIGITAL), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_1}, // RX LED
        {PORTA, 18, PIO_DIGITAL, (PIN_ATTR_DIGITAL), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2}, // TX LED / NeoPixel

        // 13 - Onboard LED
        {PORTA, 17, PIO_DIGITAL, (PIN_ATTR_DIGITAL), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_1},

        // 14..24 - Analog pins
        // --------------------
        {PORTA, 2, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel0, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2},    // A0
        {PORTA, 4, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel4, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_4},    // A1
        {PORTA, 10, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel18, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_10}, // A2
        {PORTA, 11, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel19, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_11}, // A3
        {PORTA, 8, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel16, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NMI}, // A4
        {PORTA, 9, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel17, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_9},   // A5
        {PORTB, 8, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel2, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_8},    // A6
        {PORTB, 9, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel3, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_9},    // A7
        {PORTA, 7, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel7, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_7},    // A8
        {PORTA, 5, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel5, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_5},    // A9
        {PORTA, 6, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel6, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_6},    // A10

        // 25..26 - USB
        // --------------------
        {PORTA, 24, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE}, // USB/DM
        {PORTA, 25, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE}, // USB/DP
};

const void *g_apTCInstances[TCC_INST_NUM + TC_INST_NUM] = {TCC0, TCC1, TCC2, TC3, TC4, TC5};

// Multi-serial objects instantiation
SERCOM sercom0(SERCOM0);
SERCOM sercom1(SERCOM1);
SERCOM sercom2(SERCOM2);
SERCOM sercom4(SERCOM4);

Uart Serial1(&sercom4, PIN_SERIAL_RX, PIN_SERIAL_TX, PAD_SERIAL_RX, PAD_SERIAL_TX);

void SERCOM4_Handler()
{
    Serial1.IrqHandler();
}
