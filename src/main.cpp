#include "Transmitter.h"
#include <usbhid.h>
#include <hiduniversal.h>
#include <usbhub.h>
#include <SPI.h>

#include "hidjoystickrptparser.h"

uint8_t receiverMacAddress[] = {0x84, 0xF7, 0x03, 0xF1, 0x1E, 0xDC};
// struct_message messageData;
Transmitter transmitter;
USB Usb;
USBHub Hub(&Usb);
HIDUniversal Hid(&Usb);
JoystickEvents JoyEvents;
JoystickReportParser Joy(&JoyEvents);


void setup() {
   
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
    // delay(100);
    Serial.print("DRIVE - ");
    Serial.print(JoyEvents.getParsedHIDReport().drive);
    Serial.print("   STEER - ");
    Serial.print(JoyEvents.getParsedHIDReport().steering);
    esp_err_t result = transmitter.sendData(JoyEvents.getParsedHIDReport());
    if (result == ESP_OK) {
        Serial.println("   Sent with success");
    } else {
        Serial.println("   Error sending the data");
    }
}


