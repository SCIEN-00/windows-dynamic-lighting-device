// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License.
// Adapted for Seeed XIAO SAMD21 with configurable WS2812 strip (GRB)

#include <Arduino.h>
#include <Microsoft_HidForWindows.h>
#include <Adafruit_NeoPixel.h>

// WS2812 strip on Seeed XIAO D2 (A2)
#define NEO_PIXEL_PIN A2
#define NEO_PIXEL_LAMP_COUNT 120
#define NEO_PIXEL_SPACING_MM 17
#define NEO_PIXEL_STRIP_LENGTH_MM (NEO_PIXEL_LAMP_COUNT * NEO_PIXEL_SPACING_MM)

// WS2812B is GRB format at 800KHz
#define NEO_PIXEL_TYPE (NEO_GRB + NEO_KHZ800)

// Apply LampArray intensity channel when available
#define USE_INTENSITY 0

// Initialize NeoPixel library
Adafruit_NeoPixel neoPixelStrip = Adafruit_NeoPixel(NEO_PIXEL_LAMP_COUNT, NEO_PIXEL_PIN, NEO_PIXEL_TYPE);

// UpdateLatency for all Lamps set to 2msec
#define NEO_PIXEL_LAMP_UPDATE_LATENCY (0x02)

// Lamp attributes for a linear LED strip
// All positions in millimeters from start of strip
// All times in milliseconds
static_assert(NEO_PIXEL_LAMP_COUNT <= 0xFF, "NEO_PIXEL_LAMP_COUNT must fit in lamp id range (0-255).");

static LampAttributes neoPixelStripLampAttributes[NEO_PIXEL_LAMP_COUNT];

struct LampAttributesInitializer
{
	LampAttributesInitializer()
	{
		for (uint16_t i = 0; i < NEO_PIXEL_LAMP_COUNT; i++)
		{
			neoPixelStripLampAttributes[i] = {
				(uint8_t)i,
				(uint16_t)(i * NEO_PIXEL_SPACING_MM),
				0,
				0,
				NEO_PIXEL_LAMP_UPDATE_LATENCY,
				LampPurposeAccent,
				0xFF,
				0xFF,
				0xFF,
				0x01,
				LAMP_IS_PROGRAMMABLE,
				0x00};
		}
	}
};

static LampAttributesInitializer lampAttributesInitializer;

// Initialize Microsoft LampArray
// Strip geometry automatically follows LED count and spacing.
// Using Scene type so Windows renders it as ambient lighting device
Microsoft_HidLampArray lampArray = Microsoft_HidLampArray(NEO_PIXEL_LAMP_COUNT, NEO_PIXEL_STRIP_LENGTH_MM, 10, 1, LampArrayKindScene, 33, neoPixelStripLampAttributes);

// Autonomous mode: rainbow spectrum animation
// Shows 25% of the spectrum across the whole strip, smoothly scrolling
#define RAINBOW_HUE_SPEED 8 // Hue units per ms (65536/8 ≈ 8.2s per full cycle)

// Forward declaration
uint32_t lampArrayColorToNeoPixelColor(LampArrayColor lampArrayColor);

void setup()
{
	// Initialize the NeoPixel library
	neoPixelStrip.begin();
	neoPixelStrip.clear();
	neoPixelStrip.show();
}

void loop()
{
	LampArrayColor currentLampArrayState[NEO_PIXEL_LAMP_COUNT];
	bool isAutonomousMode = lampArray.getCurrentState(currentLampArrayState);

	bool update = false;

	for (uint16_t i = 0; i < NEO_PIXEL_LAMP_COUNT; i++)
	{
		uint32_t newColor;

		if (isAutonomousMode)
		{
			// Autonomous-Mode: Scrolling spectrum window
			// All LEDs show only 25% of spectrum at once, window scrolls through full spectrum
			uint32_t now = millis();

			// Calculate spectrum offset (smoothly scrolls through 0-65535 hue range)
			uint16_t spectrumOffset = (uint16_t)((now * RAINBOW_HUE_SPEED) & 0xFFFF);

			// Each LED shows a portion of the 25% spectrum window
			// 25% of 65535 = 16384, divided by LED count = hue step per LED
			uint16_t huePerLed = 16384 / NEO_PIXEL_LAMP_COUNT;
			uint16_t ledHue = (uint16_t)((spectrumOffset + (i * huePerLed)) & 0xFFFF);

			newColor = neoPixelStrip.ColorHSV(ledHue, 255, 255);
		}
		else
		{
			// Windows is controlling - render provided colors
			newColor = lampArrayColorToNeoPixelColor(currentLampArrayState[i]);
		}

		if (newColor != neoPixelStrip.getPixelColor(i))
		{
			neoPixelStrip.setPixelColor(i, newColor);
			update = true;
		}
	}

	// Only call show() when something has changed (show() takes time to execute)
	if (update)
	{
		neoPixelStrip.show();
	}
}

uint32_t lampArrayColorToNeoPixelColor(LampArrayColor lampArrayColor)
{
#if USE_INTENSITY
	uint8_t r = (lampArrayColor.RedChannel * lampArrayColor.IntensityChannel) / 255;
	uint8_t g = (lampArrayColor.GreenChannel * lampArrayColor.IntensityChannel) / 255;
	uint8_t b = (lampArrayColor.BlueChannel * lampArrayColor.IntensityChannel) / 255;
	return neoPixelStrip.Color(r, g, b);
#else
	return neoPixelStrip.Color(lampArrayColor.RedChannel, lampArrayColor.GreenChannel, lampArrayColor.BlueChannel);
#endif
}
