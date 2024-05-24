#include <Arduino.h>
#include <Adafruit_TinyUSB.h>
#include <LampArrayReportDescriptor.hpp>
#include <LampArrayReports.hpp>
#include <FastLED.h>

#define LED_DATA_PIN 2
#define NUM_LEDS 60
#define COLOR_ORDER GRB
#define CHIPSET WS2812B

CRGB leds[NUM_LEDS];

static LampAttributes LedClusterAttributes[] PROGMEM =
	{
		// All positions in micrometers from upper-left corner of device 1 mm = 1000 μm.
		// Id, X, Y, Z, RED, GREENN, BLUE
		{1, 8300, 0, 0, 255, 255, 255},
		{2, 24900, 0, 0, 255, 255, 255},
		{3, 41500, 0, 0, 255, 255, 255},
		{4, 58100, 0, 0, 255, 255, 255},
		{5, 74700, 0, 0, 255, 255, 255},
		{6, 91300, 0, 0, 255, 255, 255},
		{7, 107900, 0, 0, 255, 255, 255},
		{8, 124500, 0, 0, 255, 255, 255},
		{9, 141100, 0, 0, 255, 255, 255},
		{10, 157700, 0, 0, 255, 255, 255},
		{11, 174300, 0, 0, 255, 255, 255},
		{12, 190900, 0, 0, 255, 255, 255},
		{13, 207500, 0, 0, 255, 255, 255},
		{14, 224100, 0, 0, 255, 255, 255},
		{15, 240700, 0, 0, 255, 255, 255},
		{16, 257300, 0, 0, 255, 255, 255},
		{17, 273900, 0, 0, 255, 255, 255},
		{18, 290500, 0, 0, 255, 255, 255},
		{19, 307100, 0, 0, 255, 255, 255},
		{20, 323700, 0, 0, 255, 255, 255},
		{21, 340300, 0, 0, 255, 255, 255},
		{22, 356900, 0, 0, 255, 255, 255},
		{23, 373500, 0, 0, 255, 255, 255},
		{24, 390100, 0, 0, 255, 255, 255},
		{25, 406700, 0, 0, 255, 255, 255},
		{26, 423300, 0, 0, 255, 255, 255},
		{27, 439900, 0, 0, 255, 255, 255},
		{28, 456500, 0, 0, 255, 255, 255},
		{29, 473100, 0, 0, 255, 255, 255},
		{30, 489700, 0, 0, 255, 255, 255},
		{31, 506300, 0, 0, 255, 255, 255},
		{32, 522900, 0, 0, 255, 255, 255},
		{33, 539500, 0, 0, 255, 255, 255},
		{34, 556100, 0, 0, 255, 255, 255},
		{35, 572700, 0, 0, 255, 255, 255},
		{36, 589300, 0, 0, 255, 255, 255},
		{37, 605900, 0, 0, 255, 255, 255},
		{38, 622500, 0, 0, 255, 255, 255},
		{39, 639100, 0, 0, 255, 255, 255},
		{40, 655700, 0, 0, 255, 255, 255},
		{41, 672300, 0, 0, 255, 255, 255},
		{42, 688900, 0, 0, 255, 255, 255},
		{43, 705500, 0, 0, 255, 255, 255},
		{44, 722100, 0, 0, 255, 255, 255},
		{45, 738700, 0, 0, 255, 255, 255},
		{46, 755300, 0, 0, 255, 255, 255},
		{47, 771900, 0, 0, 255, 255, 255},
		{48, 788500, 0, 0, 255, 255, 255},
		{49, 805100, 0, 0, 255, 255, 255},
		{50, 821700, 0, 0, 255, 255, 255},
		{51, 838300, 0, 0, 255, 255, 255},
		{52, 854900, 0, 0, 255, 255, 255},
		{53, 871500, 0, 0, 255, 255, 255},
		{54, 888100, 0, 0, 255, 255, 255},
		{55, 904700, 0, 0, 255, 255, 255},
		{56, 921300, 0, 0, 255, 255, 255},
		{57, 937900, 0, 0, 255, 255, 255},
		{58, 954500, 0, 0, 255, 255, 255},
		{59, 971100, 0, 0, 255, 255, 255},
		{60, 987700, 0, 0, 255, 255, 255},
};

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

		// Calculate the time it took to turn on and off the LED
		unsigned long endMicros = micros(); // End the timer
	}
}

Adafruit_USBD_HID usb_lamp_array(LampArrayReportDescriptor, sizeof(LampArrayReportDescriptor));

void sendLampArrayAttributes(uint8_t kind, uint8_t count, uint16_t boundingBoxX)
{
	uint8_t report[] = {0x01, kind, count, lowByte(boundingBoxX), highByte(boundingBoxX)};
	usb_lamp_array.sendReport(1, report, sizeof(report));
}

void sendLampArrayControl(uint8_t status[60])
{
	uint8_t report[61] = {0x02};
	memcpy(&report[1], status, 60);
	usb_lamp_array.sendReport(2, report, sizeof(report));
}

void sendLampArrayColor(uint8_t red, uint8_t green, uint8_t blue)
{
	uint8_t report[] = {0x03, red, green, blue};
	usb_lamp_array.sendReport(3, report, sizeof(report));
}

// Define your get report callback function
uint16_t get_report_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer, uint16_t reqlen)
{
	// Your implementation here
	return 0; // return the length of the report
}

// Define your set report callback function
void set_report_callback(uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize)
{
	// Your implementation here
}

void setup()
{
	// put your setup code here, to run once:
	FastLED.addLeds<CHIPSET, LED_DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
	usb_lamp_array.begin();
	usb_lamp_array.setReportCallback(get_report_callback, set_report_callback);
}

void loop()
{
}