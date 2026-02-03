// Copyright (c) Microsoft Corporation.  All rights reserved.
// Licensed under the MIT License.
// Adapted for Seeed XIAO SAMD21 with 60 LED WS2812 strip (GRB)

#include <Arduino.h>
#include <Microsoft_HidForWindows.h>
#include <Adafruit_NeoPixel.h>

// 60 LED WS2812 strip on Seeed XIAO D2 (A2)
#define NEO_PIXEL_PIN A2
#define NEO_PIXEL_LAMP_COUNT 60

// WS2812B is GRB format at 800KHz
#define NEO_PIXEL_TYPE (NEO_GRB + NEO_KHZ800)

// Temporary test mode to verify NeoPixel output independent of HID
#define FORCE_TEST 0

// Initialize NeoPixel library
Adafruit_NeoPixel neoPixelStrip = Adafruit_NeoPixel(NEO_PIXEL_LAMP_COUNT, NEO_PIXEL_PIN, NEO_PIXEL_TYPE);

// UpdateLatency for all Lamps set to 4msec
#define NEO_PIXEL_LAMP_UPDATE_LATENCY (0x04)

// Lamp attributes for 60 LEDs in a line
// All positions in millimeters from start of strip
// All times in milliseconds
static LampAttributes neoPixelStripLampAttributes[] PROGMEM =
	{
		// Id  X     Y     Z     Latency                        Purposes           RED   GRN   BLUE  GAIN  PROGAMMBLE?           KEY
		{0x00, 0, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x01, 10, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x02, 20, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x03, 30, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x04, 40, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x05, 50, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x06, 60, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x07, 70, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x08, 80, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x09, 90, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x0A, 100, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x0B, 110, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x0C, 120, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x0D, 130, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x0E, 140, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x0F, 150, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x10, 160, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x11, 170, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x12, 180, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x13, 190, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x14, 200, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x15, 210, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x16, 220, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x17, 230, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x18, 240, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x19, 250, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x1A, 260, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x1B, 270, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x1C, 280, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x1D, 290, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x1E, 300, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x1F, 310, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x20, 320, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x21, 330, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x22, 340, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x23, 350, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x24, 360, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x25, 370, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x26, 380, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x27, 390, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x28, 400, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x29, 410, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x2A, 420, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x2B, 430, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x2C, 440, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x2D, 450, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x2E, 460, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x2F, 470, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x30, 480, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x31, 490, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x32, 500, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x33, 510, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x34, 520, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x35, 530, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x36, 540, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x37, 550, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x38, 560, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x39, 570, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x3A, 580, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
		{0x3B, 590, 0, 0, NEO_PIXEL_LAMP_UPDATE_LATENCY, LampPurposeAccent, 0xFF, 0xFF, 0xFF, 0x01, LAMP_IS_PROGRAMMABLE, 0x00},
};
static_assert(((sizeof(neoPixelStripLampAttributes) / sizeof(LampAttributes)) == NEO_PIXEL_LAMP_COUNT), "neoPixelStripLampAttributes must have NEO_PIXEL_LAMP_COUNT items.");

// Initialize Microsoft LampArray
// Strip is 600mm long (60 * 10mm), 10mm tall, 1mm deep
Microsoft_HidLampArray lampArray = Microsoft_HidLampArray(NEO_PIXEL_LAMP_COUNT, 600, 10, 1, LampArrayKindPeripheral, 33, neoPixelStripLampAttributes);

// Autonomous mode color (blue when Windows not controlling)
uint32_t lampArrayAutonomousColor = neoPixelStrip.Color(0, 0, 255);

// Forward declaration
uint32_t lampArrayColorToNeoPixelColor(LampArrayColor lampArrayColor);

void setup()
{
	// Initialize the NeoPixel library
	neoPixelStrip.begin();
	neoPixelStrip.clear();

	// Always initially in Autonomous-Mode (blue)
	neoPixelStrip.fill(lampArrayAutonomousColor, 0, NEO_PIXEL_LAMP_COUNT - 1);
	neoPixelStrip.show();
}

void loop()
{
#if FORCE_TEST
	static bool isOn = false;
	static uint32_t lastToggleMs = 0;
	const uint32_t now = millis();
	if (now - lastToggleMs >= 500)
	{
		lastToggleMs = now;
		isOn = !isOn;
		const uint32_t testColor = isOn ? neoPixelStrip.Color(255, 0, 0) : neoPixelStrip.Color(0, 0, 0);
		neoPixelStrip.fill(testColor, 0, NEO_PIXEL_LAMP_COUNT);
		neoPixelStrip.show();
	}
	return;
#endif

	LampArrayColor currentLampArrayState[NEO_PIXEL_LAMP_COUNT];
	bool isAutonomousMode = lampArray.getCurrentState(currentLampArrayState);

	bool update = false;

	for (uint16_t i = 0; i < NEO_PIXEL_LAMP_COUNT; i++)
	{
		// Autonomous-Mode: Host indicates device should decide what to render
		// In this case, render blue when no application is controlling
		uint32_t newColor = isAutonomousMode ? lampArrayAutonomousColor : lampArrayColorToNeoPixelColor(currentLampArrayState[i]);
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
	// Match Microsoft example: ignore IntensityChannel for now
	return neoPixelStrip.Color(lampArrayColor.RedChannel, lampArrayColor.GreenChannel, lampArrayColor.BlueChannel);
}
