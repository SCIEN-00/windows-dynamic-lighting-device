// Copyright (c) Microsoft Corporation.  All rights reserved.
// Adapted for Seeed XIAO SAMD21 with 60 LED WS2812 strip

#include <Arduino.h>
#include <stdint.h>
#include <Microsoft_HidForWindows.h>
#include <Adafruit_NeoPixel.h>

// 60 LED WS2812 strip on pin 2
#define NEOPIXEL_PIN 2
#define NUM_LAMPS 60
#define NEOPIXEL_TYPE (NEO_GRB + NEO_KHZ800)
#define LAMP_UPDATE_LATENCY 4

Adafruit_NeoPixel pixels(NUM_LAMPS, NEOPIXEL_PIN, NEOPIXEL_TYPE);

// Lamp attributes for 60 LEDs in a line (simplified positioning)
static LampAttributes lampAttributes[NUM_LAMPS] PROGMEM = {
	// 60 LEDs in a line, 10mm spacing
	{0x00, 0, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x01, 10, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x02, 20, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x03, 30, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x04, 40, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x05, 50, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x06, 60, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x07, 70, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x08, 80, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x09, 90, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x0A, 100, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x0B, 110, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x0C, 120, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x0D, 130, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x0E, 140, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x0F, 150, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x10, 160, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x11, 170, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x12, 180, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x13, 190, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x14, 200, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x15, 210, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x16, 220, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x17, 230, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x18, 240, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x19, 250, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x1A, 260, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x1B, 270, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x1C, 280, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x1D, 290, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x1E, 300, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x1F, 310, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x20, 320, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x21, 330, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x22, 340, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x23, 350, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x24, 360, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x25, 370, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x26, 380, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x27, 390, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x28, 400, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x29, 410, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x2A, 420, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x2B, 430, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x2C, 440, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x2D, 450, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x2E, 460, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x2F, 470, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x30, 480, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x31, 490, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x32, 500, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x33, 510, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x34, 520, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x35, 530, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x36, 540, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x37, 550, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x38, 560, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x39, 570, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x3A, 580, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
	{0x3B, 590, 0, 0, LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00}};

// LampArray instance - MUST be in global scope for USB initialization
Microsoft_HidLampArray lampArray(
	NUM_LAMPS,				 // lampCount
	600,					 // boundingBoxWidthInMillimeters (60 LEDs * 10mm)
	10,						 // boundingBoxHeightInMillimeters
	1,						 // boundingBoxDepthInMillimeters
	LampArrayKindPeripheral, // kind
	33,						 // minUpdateIntervalInMilliseconds (30fps)
	lampAttributes			 // attributes
);

// Autonomous mode color (blue when Windows not controlling)
uint32_t autonomousColor = pixels.Color(0, 0, 255);

void setup()
{
	// Initialize NeoPixel strip
	pixels.begin();
	pixels.clear();

	// Start in autonomous mode with blue for all LEDs
	for (uint16_t i = 0; i < NUM_LAMPS; i++)
	{
		pixels.setPixelColor(i, autonomousColor);
	}
	pixels.show();
}

void loop()
{
	// Get current lamp state from Windows
	LampArrayColor currentState[NUM_LAMPS];
	bool isAutonomousMode = lampArray.getCurrentState(currentState);

	if (isAutonomousMode)
	{
		// Autonomous: show blue on all LEDs
		for (uint16_t i = 0; i < NUM_LAMPS; i++)
		{
			pixels.setPixelColor(i, autonomousColor);
		}
	}
	else
	{
		// Windows control: apply colors to all LEDs
		for (uint16_t i = 0; i < NUM_LAMPS; i++)
		{
			uint8_t r = currentState[i].RedChannel;
			uint8_t g = currentState[i].GreenChannel;
			uint8_t b = currentState[i].BlueChannel;
			uint8_t intensity = currentState[i].IntensityChannel;

			// Apply intensity scaling
			if (intensity < 255)
			{
				r = (r * intensity) / 255;
				g = (g * intensity) / 255;
				b = (b * intensity) / 255;
			}

			pixels.setPixelColor(i, pixels.Color(r, g, b));
		}
	}

	pixels.show();
	delay(10);
}
