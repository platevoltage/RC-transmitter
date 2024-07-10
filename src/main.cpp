#include "Transmitter.h"
#include <usbhid.h>
#include <hiduniversal.h>
#include <usbhub.h>
#include <SPI.h>
#include <U8g2lib.h>
#include "hidjoystickrptparser.h"

uint8_t receiverMacAddress[] = {0x84, 0xF7, 0x03, 0xF1, 0x1E, 0xDC};
// struct_message messageData;
Transmitter transmitter;
USB Usb;
USBHub Hub(&Usb);
HIDUniversal Hid(&Usb);
JoystickEvents JoyEvents;
JoystickReportParser Joy(&JoyEvents);
U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 39, /* dc=*/ 37, /* reset=*/ 35);

void setup() {
    u8g2.begin();
    // Initialize Serial Monitor
    Serial.begin(115200);
    // pinMode(18, INPUT_PULLUP);
    delay(3000);
    transmitter.init(receiverMacAddress);

    Serial.println("start");
    int usbInitCode = Usb.Init();
    Serial.println(usbInitCode);
    if (usbInitCode == -1)
            Serial.println("OSC did not start.");

    delay(2000);

    if (!Hid.SetReportParser(0, &Joy))
            ErrorMessage<uint8_t > (PSTR("SetReportParser"), 1);
    delay(1000);
}



void loop() {
    Usb.Task();

    struct_message message = JoyEvents.getParsedHIDReport();

    transmitter.sendData(message);
    u8g2.clearBuffer();					// clear the internal memory
    u8g2.setFont(u8g2_font_helvR14_tr);	// choose a suitable font
    u8g2.drawStr(0,16,"Hello World!");	// write something to the internal memory
    u8g2.sendBuffer();					// transfer internal memory to the display
    delay(1000);  
}


