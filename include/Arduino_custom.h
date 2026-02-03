// Custom Arduino header for Seeed XIAO with Adafruit TinyUSB support
// This wrapper allows us to use Adafruit TinyUSB without the broken Adafruit_USBD_CDC.h

#ifndef ARDUINO_H_CUSTOM
#define ARDUINO_H_CUSTOM

// Prevent the built-in Arduino.h from including Adafruit_USBD_CDC.h
#define ADAFRUIT_USBD_CDC_H

// Now include the standard Arduino.h
#include <../Arduino.h>

#endif
