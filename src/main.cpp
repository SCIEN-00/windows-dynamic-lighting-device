#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_TinyUSB.h>
#include <hid/Adafruit_USBD_HID.h>
#include "hid_descriptor.h"

// ============================================================================
// PIN & LED Configuration
// ============================================================================
#define NEOPIXEL_PIN 16
#define NUM_PIXELS 10
#define ONBOARD_LED_PIN 13

Adafruit_NeoPixel pixels(NUM_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

// ============================================================================
// HID Device State
// ============================================================================
uint32_t lamp_colors[NUM_PIXELS] = {0};
volatile uint32_t hid_get_report_count = 0;
volatile uint32_t hid_set_report_count = 0;

// USB HID Device
Adafruit_USBD_HID usb_hid;

// ============================================================================
// LED Control
// ============================================================================
void update_leds()
{
	for (int i = 0; i < NUM_PIXELS; i++)
	{
		uint32_t color = lamp_colors[i];
		pixels.setPixelColor(i, color);
	}
	pixels.show();
}

// ============================================================================
// Setup
// ============================================================================
void setup()
{
	// Initialize pins
	pinMode(ONBOARD_LED_PIN, OUTPUT);
	digitalWrite(ONBOARD_LED_PIN, LOW);

	// Initialize NeoPixels
	pixels.begin();
	pixels.fill(0x0000FF); // Blue initially
	pixels.show();

	// Initialize Serial for debugging
	Serial.begin(115200);
	delay(100);

	Serial.println("\n");
	Serial.println("=====================================");
	Serial.println("Windows Dynamic Lighting Device");
	Serial.println("Seeed XIAO SAMD21 LampArray");
	Serial.println("=====================================");
	Serial.println("Testing basic NeoPixel functionality...");
	Serial.println("");

	// Initialize USB HID
	usb_hid.setPollInterval(2);
	usb_hid.setReportDescriptor(hid_lamp_array_descriptor, hid_lamp_array_descriptor_size);
	usb_hid.begin();

	Serial.println("USB HID LampArray initialized");
}

// ============================================================================
// Main Loop
// ============================================================================
void loop()
{
	static uint32_t last_blink = 0;
	uint32_t now = millis();

	// Toggle onboard LED to show device is alive
	if (now - last_blink > 1000)
	{
		digitalWrite(ONBOARD_LED_PIN, !digitalRead(ONBOARD_LED_PIN));
		last_blink = now;
	}

	// Cycle through some test colors
	static uint32_t color_index = 0;
	static uint32_t last_color_change = 0;

	uint32_t test_colors[] = {
		0xFF0000, // Red
		0x00FF00, // Green
		0x0000FF, // Blue
		0xFFFF00, // Yellow
	};

	if (now - last_color_change > 2000)
	{
		color_index = (color_index + 1) % 4;
		for (int i = 0; i < NUM_PIXELS; i++)
		{
			lamp_colors[i] = test_colors[color_index];
		}
		last_color_change = now;
		Serial.print("Color change: ");
		Serial.println(test_colors[color_index], HEX);
	}

	// Update LEDs
	update_leds();

	delay(50);
}
