#pragma once

PROGMEM const uint8_t LampArrayReportDescriptor[] = {
	/* USB report descriptor */
	0x05, 0x59,		  // USAGE_PAGE (Lighting and Illumination)
	0x09, 0x01,		  // USAGE (Lamp Array)
	0xa1, 0x01,		  // COLLECTION (Application)
	0x85, 0x01,		  //   REPORT_ID (1)
	0x09, 0x37,		  //   USAGE (Lamp Array Attributes)
	0xa1, 0x02,		  //   COLLECTION (Logical)
	0x09, 0x72,		  //     USAGE (Lamp Array Kind)
	0x15, 0x00,		  //     LOGICAL_MINIMUM (0)
	0x25, 0x0B,		  //     LOGICAL_MAXIMUM (11)
	0x75, 0x08,		  //     REPORT_SIZE (8)
	0x95, 0x01,		  //     REPORT_COUNT (1)
	0xb1, 0x02,		  //     FEATURE (Data,Var,Abs)
					  //
	0x09, 0x70,		  //     USAGE (Lamp Count)
	0x15, 0x01,		  //     LOGICAL_MINIMUM (1)
	0x25, 0x3c,		  //     LOGICAL_MAXIMUM (60)
	0x75, 0x08,		  //     REPORT_SIZE (8)
	0x95, 0x01,		  //     REPORT_COUNT (1)
	0xb1, 0x02,		  //     FEATURE (Data,Var,Abs)
					  //
	0x09, 0x71,		  //     USAGE (Bounding Box X Dimension)
	0x15, 0x00,		  //     LOGICAL_MINIMUM (0)
	0x26, 0x98, 0x40, //     LOGICAL_MAXIMUM (16600)
	0x75, 0x10,		  //     REPORT_SIZE (16)
	0x95, 0x01,		  //     REPORT_COUNT (1)
	0xb1, 0x02,		  //     FEATURE (Data,Var,Abs)
	0xc0,			  //   END_COLLECTION
					  //
	0x09, 0x38,		  //   USAGE (Lamp Array Control)
	0xa1, 0x02,		  //   COLLECTION (Logical)
	0x85, 0x02,		  //     REPORT_ID (2)
	0x09, 0x3b,		  //     USAGE (Lamp Array Status)
	0x15, 0x00,		  //     LOGICAL_MINIMUM (0)
	0x25, 0x01,		  //     LOGICAL_MAXIMUM (1)
	0x75, 0x01,		  //     REPORT_SIZE (1)
	0x95, 0x3c,		  //     REPORT_COUNT (60)
	0xb1, 0x02,		  //     FEATURE (Data,Var,Abs)
					  //
	0x85, 0x03,		  //     REPORT_ID (3)
	0x09, 0x3c,		  //     USAGE (Lamp Array Color)
	0x15, 0x00,		  //     LOGICAL_MINIMUM (0)
	0x25, 0xFF,		  //     LOGICAL_MAXIMUM (255)
	0x75, 0x08,		  //     REPORT_SIZE (8)
	0x95, 0x03,		  //     REPORT_COUNT (3)
	0xb1, 0x02,		  //     FEATURE (Data,Var,Abs)
	0xc0,			  //   END_COLLECTION
	0xc0			  // END_COLLECTION
};