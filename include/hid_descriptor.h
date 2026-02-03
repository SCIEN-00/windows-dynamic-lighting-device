#pragma once

#include <stdint.h>
#include <string.h>

// USB HID LampArray Report Descriptor
// Based on USB HID spec for Lighting and Illumination (Usage Page 0x59)
const uint8_t hid_lamp_array_descriptor[] = {
    0x05, 0x59, // USAGE_PAGE (Lighting and Illumination)
    0x09, 0x01, // USAGE (LampArray)
    0xA1, 0x01, // COLLECTION (Application)

    // Report 1: Lamp Attributes (INPUT)
    0x85, 0x01, // REPORT_ID (1)
    0x19, 0x00, // USAGE_MINIMUM (Undefined)
    0x29, 0xFF, // USAGE_MAXIMUM (Undefined)
    0x15, 0x00, // LOGICAL_MINIMUM (0)
    0x25, 0xFF, // LOGICAL_MAXIMUM (255)
    0x75, 0x08, // REPORT_SIZE (8)
    0x95, 0x1F, // REPORT_COUNT (31)
    0x81, 0x02, // INPUT (Data,Var,Abs)

    // Report 2: Multiple Update (OUTPUT)
    0x85, 0x02, // REPORT_ID (2)
    0x19, 0x00, // USAGE_MINIMUM (Undefined)
    0x29, 0xFF, // USAGE_MAXIMUM (Undefined)
    0x15, 0x00, // LOGICAL_MINIMUM (0)
    0x25, 0xFF, // LOGICAL_MAXIMUM (255)
    0x75, 0x08, // REPORT_SIZE (8)
    0x95, 0x1F, // REPORT_COUNT (31)
    0x91, 0x02, // OUTPUT (Data,Var,Abs)

    // Report 3: Range Update (OUTPUT)
    0x85, 0x03, // REPORT_ID (3)
    0x19, 0x00, // USAGE_MINIMUM (Undefined)
    0x29, 0xFF, // USAGE_MAXIMUM (Undefined)
    0x15, 0x00, // LOGICAL_MINIMUM (0)
    0x25, 0xFF, // LOGICAL_MAXIMUM (255)
    0x75, 0x08, // REPORT_SIZE (8)
    0x95, 0x1F, // REPORT_COUNT (31)
    0x91, 0x02, // OUTPUT (Data,Var,Abs)

    // Report 4: Lamp Attributes Response (INPUT)
    0x85, 0x04, // REPORT_ID (4)
    0x19, 0x00, // USAGE_MINIMUM (Undefined)
    0x29, 0xFF, // USAGE_MAXIMUM (Undefined)
    0x15, 0x00, // LOGICAL_MINIMUM (0)
    0x25, 0xFF, // LOGICAL_MAXIMUM (255)
    0x75, 0x08, // REPORT_SIZE (8)
    0x95, 0x1F, // REPORT_COUNT (31)
    0x81, 0x02, // INPUT (Data,Var,Abs)

    // Report 5: Lamp Multi Update (OUTPUT)
    0x85, 0x05, // REPORT_ID (5)
    0x19, 0x00, // USAGE_MINIMUM (Undefined)
    0x29, 0xFF, // USAGE_MAXIMUM (Undefined)
    0x15, 0x00, // LOGICAL_MINIMUM (0)
    0x25, 0xFF, // LOGICAL_MAXIMUM (255)
    0x75, 0x08, // REPORT_SIZE (8)
    0x95, 0x1F, // REPORT_COUNT (31)
    0x91, 0x02, // OUTPUT (Data,Var,Abs)

    // Report 6: Lamp Range Update (OUTPUT)
    0x85, 0x06, // REPORT_ID (6)
    0x19, 0x00, // USAGE_MINIMUM (Undefined)
    0x29, 0xFF, // USAGE_MAXIMUM (Undefined)
    0x15, 0x00, // LOGICAL_MINIMUM (0)
    0x25, 0xFF, // LOGICAL_MAXIMUM (255)
    0x75, 0x08, // REPORT_SIZE (8)
    0x95, 0x1F, // REPORT_COUNT (31)
    0x91, 0x02, // OUTPUT (Data,Var,Abs)

    0xC0 // END_COLLECTION
};

const size_t hid_lamp_array_descriptor_size = sizeof(hid_lamp_array_descriptor);
