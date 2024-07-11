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

// bool up;
// bool down;
// bool left;
// bool right;

// bool A;
// bool B;
// bool X;
// bool Y;

void setup() {
    u8g2.begin();
    // Initialize Serial Monitor
    Serial.begin(115200);
    // pinMode(18, INPUT_PULLUP);
    // delay(3000);
    transmitter.init(receiverMacAddress);

    Serial.println("start");
    int usbInitCode = Usb.Init();
    Serial.println(usbInitCode);
    if (usbInitCode == -1)
            Serial.println("OSC did not start.");

    // delay(2000);

    if (!Hid.SetReportParser(0, &Joy))
            ErrorMessage<uint8_t > (PSTR("SetReportParser"), 1);
    // delay(1000);
}



void loop() {
    Usb.Task();

    struct_message message = JoyEvents.getParsedHIDReport();

    transmitter.sendData(message);
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_helvB12_tr);
    String steer = "Steer: ";
    steer.concat(message.steering);
    u8g2.drawStr(0,14, steer.c_str());
    String drive = "Drive: ";
    drive.concat(message.drive);
    u8g2.drawStr(0,28, drive.c_str());

    // String usbStatus = "";
    // usbStatus.concat(Usb.getUsbTaskState());
    // u8g2.drawStr(0,42, usbStatus.c_str());
    String upStatus = "";
    upStatus.concat(JoyEvents.up);
    u8g2.drawStr(10,42, upStatus.c_str());
    String leftStatus = "";
    leftStatus.concat(JoyEvents.left);
    u8g2.drawStr(0,52, leftStatus.c_str());
    String rightStatus = "";
    rightStatus.concat(JoyEvents.right);
    u8g2.drawStr(20,52, rightStatus.c_str());
    String downStatus = "";
    downStatus.concat(JoyEvents.down);
    u8g2.drawStr(10,60, downStatus.c_str());

    String YStatus = "";
    YStatus.concat(JoyEvents.Y);
    u8g2.drawStr(50,42, YStatus.c_str());
    String XStatus = "";
    XStatus.concat(JoyEvents.X);
    u8g2.drawStr(40,52, XStatus.c_str());
    String BStatus = "";
    BStatus.concat(JoyEvents.B);
    u8g2.drawStr(60,52, BStatus.c_str());
    String AStatus = "";
    AStatus.concat(JoyEvents.A);
    u8g2.drawStr(50,60, AStatus.c_str());

    String reverseStatus = "";
    reverseStatus.concat(JoyEvents.reverse);
    u8g2.drawStr(80,52, reverseStatus.c_str());

    String startStatus = "";
    startStatus.concat(JoyEvents.start);
    u8g2.drawStr(92,52, startStatus.c_str());

    if (Usb.getUsbTaskState() != 144) {

      
        u8g2.setDrawColor(0);
        u8g2.drawBox(0,0,128,64);
        u8g2.setDrawColor(1);

        
        // u8g2.drawBox(0,18,124,30);
        // u8g2.drawFrame(0,18,124,30);
        // u8g2.setDrawColor(0);
        // u8g2.drawBox(4,22,124,32);
        // u8g2.setDrawColor(1);
        // u8g2.drawFrame(4,22,124,32);
        u8g2.setFont(u8g2_font_helvB10_tr);
        // u8g2.drawStr(8,42, "Connect Wheel!");
        u8g2.drawButtonUTF8(62, 30, U8G2_BTN_SHADOW1|U8G2_BTN_HCENTER|U8G2_BTN_BW2, 34,  2,  2, "Connect Wheel!" );
        u8g2.drawStr(60,52, String(Usb.getUsbTaskState()).c_str());

    }
    u8g2.sendBuffer();
    // delay(1000);  
    Serial.println(esp_get_free_heap_size());
}


