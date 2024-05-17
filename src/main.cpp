#include "FastLED.h"
#include "Adafruit_TinyUSB.h"
#include "LampArrayReportDescriptor.hpp"
#include "LampArrayReports.hpp"

#define LED_DATA_PIN 2
#define NUM_LEDS 60
#define COLOR_ORDER GRB
#define CHIPSET WS2812B

CRGB leds[NUM_LEDS];

enum LampPurposeKind
{
    LampPurposeControl = 1,
    LampPurposeAccent = 2,
    LampPurposeBranding = 4,
    LampPurposeStatus = 8,
    LampPurposeIllumination = 16,
    LampPurposePresentation = 32,
};

enum LampArrayKind
{
    LampArrayKindKeyboard = 1,
    LampArrayKindMouse = 2,
    LampArrayKindGameController = 3,
    LampArrayKindPeripheral = 4,
    LampArrayKindScene = 5,
    LampArrayKindNotification = 6,
    LampArrayKindChassis = 7,
    LampArrayKindWearable = 8,
    LampArrayKindFurniture = 9,
    LampArrayKindArt = 10,
};

struct __attribute__ ((__packed__)) LampArrayColor
{
    uint8_t RedChannel;
    uint8_t GreenChannel;
    uint8_t BlueChannel;
    uint8_t IntensityChannel;
};

struct __attribute__ ((__packed__)) LampAttributes
{
    uint16_t LampId;
    uint32_t PositionXInMicrometers;
    uint32_t PositionYInMicrometers;
    uint32_t PositionZInMicrometers;
    uint32_t LampPurposes;
    uint8_t RedLevelCount;
    uint8_t GreenLevelCount;
    uint8_t BlueLevelCount;
    uint8_t IsProgrammable;
};

static LampAttributes LedClusterAttributes[] PROGMEM =
	{
		// All positions in micrometers from upper-left corner of device 1 mm = 1000 μm.
		// Id, X, Y, Z, Latency, Purposes, RED, GREENN, BLUE, PROGAMMBLE
		{0, 8300, 0, 0, LampPurposeIllumination, 255, 255, 255, LAMP_IS_PROGRAMMABLE},
		{1, 24900, 0, 0, LampPurposeIllumination, 255, 255, 255, LAMP_IS_PROGRAMMABLE},
		{2, 24900 + 16600, 0, 0, LampPurposeIllumination, 255, 255, 255, LAMP_IS_PROGRAMMABLE},
};

struct LampAttributesRequestReport
{
	uint16_t lampId; // Assuming lampId is 16 bits
	uint32_t color;	 // Assuming color is 32 bits
};

void setLampColor(uint16_t lampId, uint32_t color)
{
	FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(leds, NUM_LEDS);

	if (lampId < NUM_LEDS)
	{
		leds[lampId] = color;
		FastLED.show();
	}
}

struct MyHID : public Adafruit_USBD_HID
{
	MyHID(void) : Adafruit_USBD_HID() {}

	// Override callbackGetReport
	virtual uint16_t callbackGetReport(uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer, uint16_t reqlen)
	{
		for (int i = 0; i < sizeof(LampArrayReportDescriptor); i++)
		{
			if (LampArrayReportDescriptor[i] == 0x85) // 0x85 is the prefix for report ID
			{
				uint8_t descriptor_report_id = LampArrayReportDescriptor[i + 1]; // the report ID follows 0x85
				if (report_id == descriptor_report_id && report_type == HID_REPORT_TYPE_FEATURE)
				{
					memcpy(buffer, &LampArrayReportDescriptor, sizeof(LampArrayReportDescriptor));
					return sizeof(LampArrayReportDescriptor);
				}
			}
		}
		return 0;
	}

	// Override callbackSetReport
	virtual void callbackSetReport(uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer, uint16_t bufsize)
	{
		if (report_id == LAMP_ATTRIBUTES_REQUEST_REPORT_ID && report_type == HID_REPORT_TYPE_FEATURE)
		{
			// Assuming LampAttributesRequestReport is a struct that matches the data sent by the host
			LampAttributesRequestReport *report = reinterpret_cast<LampAttributesRequestReport *>(buffer);

			// Now you can use the data in the report to update the state of your device
			// For example, if your report contains a lamp ID and a color, you might do something like this:
			setLampColor(report->lampId, report->color);
		}
	}
};

MyHID my_hid;

int default_behavior()
{
	for (int i = 0; i < NUM_LEDS; i++)
	{
		unsigned long startMicros = micros(); // Start the timer

		// Gradually turn on the LED
		for (int brightness = 0; brightness <= 255; brightness++)
		{
			leds[i] = CHSV(0, 0, brightness); // Increase brightness
			FastLED.show();
		}

		// Gradually turn off the LED
		for (int brightness = 255; brightness >= 0; brightness--)
		{
			leds[i] = CHSV(0, 0, brightness); // Decrease brightness
			FastLED.show();
		}

		unsigned long endMicros = micros(); // End the timer
	}
}

void setup()
{
	// put your setup code here, to run once:
	FastLED.addLeds<CHIPSET, LED_DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);

	my_hid.begin();
}

void loop()
{
	// put your main code here, to run repeatedly:
	// default_behavior();
}