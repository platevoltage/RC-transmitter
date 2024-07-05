#include "Transmitter.h"
#include <usbhid.h>
#include <hiduniversal.h>
#include <usbhub.h>
#include <SPI.h>

#include "hidjoystickrptparser.h"

USB Usb;
USBHub Hub(&Usb);
HIDUniversal Hid(&Usb);
JoystickEvents JoyEvents;
JoystickReportParser Joy(&JoyEvents);

uint8_t receiverMacAddress[] = {0x84, 0xF7, 0x03, 0xF1, 0x1E, 0xDC};
Transmitter transmitter;

void setup() {
   
    // Initialize Serial Monitor
    Serial.begin(115200);
    // pinMode(18, INPUT_PULLUP);
    // transmitter.init(receiverMacAddress);
    delay(3000);

    Serial.println("start");
    int usbInitCode = Usb.Init();
    Serial.println(usbInitCode);
    if (usbInitCode == -1)
            Serial.println("OSC did not start.");

    delay(200);

    if (!Hid.SetReportParser(0, &Joy))
            ErrorMessage<uint8_t > (PSTR("SetReportParser"), 1);
  Serial.print("MOSI: ");
  Serial.println(MOSI);
  Serial.print("MISO: ");
  Serial.println(MISO);
  Serial.print("SCK: ");
  Serial.println(SCK);
  Serial.print("SS: ");
  Serial.println(SS);  
}



void loop() {
    Usb.Task();
}


// MAKE_PIN(P0, 0);   // General I/O pin, mapped to GPIO21
// MAKE_PIN(P1, 1);    // TX0, typically GPIO1 for UART0 TX
// MAKE_PIN(P10, 10);  // TX1, mapped to GPIO17 for UART1 TX
// MAKE_PIN(P3, 3);    // RX0, typically GPIO3 for UART0 RX
// MAKE_PIN(P21, 21);   // SDA, typically GPIO8 for I2C SDA
// MAKE_PIN(P22, 22);   // SCL, typically GPIO9 for I2C SCL
// MAKE_PIN(P19, 9);  // MISO, typically GPIO12 for SPI MISO
// MAKE_PIN(P23, 11);  // MOSI, typically GPIO13 for SPI MOSI
// MAKE_PIN(P18, 7);  // SCK, typically GPIO14 for SPI SCK
// MAKE_PIN(P5, 12);   // SS, typically GPIO15 for SPI SS
// MAKE_PIN(P17, 5);   // INT, using GPIO4 for interrupt