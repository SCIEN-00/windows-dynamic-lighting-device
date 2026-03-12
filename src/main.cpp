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

// Apply LampArray intensity channel from host updates.
#define USE_INTENSITY 1

// USB serial debug output for incoming Windows LampArray data
#define DEBUG_WINDOWS_LAMP_INPUT 1
#define DEBUG_LOG_INTERVAL_MS 250

#if DEBUG_WINDOWS_LAMP_INPUT
#if defined(ARDUINO_ARCH_SAMD)
#define DEBUG_SERIAL_PORT SerialUSB
#else
#define DEBUG_SERIAL_PORT Serial
#endif
#endif

// Initialize NeoPixel library
Adafruit_NeoPixel neoPixelStrip = Adafruit_NeoPixel(NEO_PIXEL_LAMP_COUNT, NEO_PIXEL_PIN, NEO_PIXEL_TYPE);

// Report realistic per-lamp update latency in milliseconds.
#define NEO_PIXEL_LAMP_UPDATE_LATENCY (0x04)

// Hint host to target up to 200 FPS effect updates.
#define LAMP_ARRAY_MIN_UPDATE_INTERVAL_MS (5)

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
				LampPurposeAccent | LampPurposeIllumination,
				0xFF,
				0xFF,
				0xFF,
				0xFF,
				LAMP_IS_PROGRAMMABLE,
				0x00};
		}
	}
};

static LampAttributesInitializer lampAttributesInitializer;

// Initialize Microsoft LampArray
// Strip geometry automatically follows LED count and spacing.
// Using Scene type so Windows renders it as ambient lighting device
Microsoft_HidLampArray lampArray = Microsoft_HidLampArray(NEO_PIXEL_LAMP_COUNT, NEO_PIXEL_STRIP_LENGTH_MM, 10, 1, LampArrayKindScene, LAMP_ARRAY_MIN_UPDATE_INTERVAL_MS, neoPixelStripLampAttributes);

// Autonomous mode: rainbow spectrum animation
// Shows 25% of the spectrum across the whole strip, smoothly scrolling
#define RAINBOW_HUE_SPEED 8 // Hue units per ms (65536/8 ≈ 8.2s per full cycle)

// Forward declaration
uint32_t lampArrayColorToNeoPixelColor(LampArrayColor lampArrayColor);

#if DEBUG_WINDOWS_LAMP_INPUT
static uint32_t lastDebugLogMs = 0;
#endif

void setup()
{
#if DEBUG_WINDOWS_LAMP_INPUT
	DEBUG_SERIAL_PORT.begin(115200);
	uint32_t serialWaitStart = millis();
	while (!DEBUG_SERIAL_PORT && (millis() - serialWaitStart < 2000))
	{
		// Wait briefly for native USB serial to connect.
	}
	DEBUG_SERIAL_PORT.println("LampArray debug: logging first LED R,G,B,I from Windows input");
#endif

	// Initialize the NeoPixel library
	neoPixelStrip.begin();
	neoPixelStrip.clear();
	neoPixelStrip.show();
}

void loop()
{
	LampArrayColor currentLampArrayState[NEO_PIXEL_LAMP_COUNT];
	bool isAutonomousMode = lampArray.getCurrentState(currentLampArrayState);

#if DEBUG_WINDOWS_LAMP_INPUT
	if (!isAutonomousMode)
	{
		uint32_t now = millis();
		if (now - lastDebugLogMs >= DEBUG_LOG_INTERVAL_MS)
		{
			lastDebugLogMs = now;
			LampArrayColor c = currentLampArrayState[0];
			DEBUG_SERIAL_PORT.print("Win LED0 R=");
			DEBUG_SERIAL_PORT.print(c.RedChannel);
			DEBUG_SERIAL_PORT.print(" G=");
			DEBUG_SERIAL_PORT.print(c.GreenChannel);
			DEBUG_SERIAL_PORT.print(" B=");
			DEBUG_SERIAL_PORT.print(c.BlueChannel);
			DEBUG_SERIAL_PORT.print(" I=");
			DEBUG_SERIAL_PORT.println(c.IntensityChannel);
		}
	}
#endif

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
