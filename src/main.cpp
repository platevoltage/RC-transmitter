#include "wireless.h"

uint8_t receiverMacAddress[] = {0x84, 0xF7, 0x03, 0xF1, 0x1E, 0xDC};
Wireless wireless;

void setup() {
    // Initialize Serial Monitor
    Serial.begin(115200);
    pinMode(18, INPUT_PULLUP);
    wireless.init(receiverMacAddress);

}

// int value = 0xFF0000;
int value = 0;
void loop() {
    if (digitalRead(18)) {
    //   value = 0x0000FF;
    value = 90;
    } else {
    //   value = 0xFF0000;
    value = 100;
    }
    // Sample message
    struct_message myData;
    strcpy(myData.text, "Hello");
    myData.value = value;

    // Send message
    esp_err_t result = wireless.sendData(myData);
    

    if (result == ESP_OK) {
        Serial.println("Sent with success");
    } else {
        Serial.println("Error sending the data");
    }

    Serial.print("button - ");
    Serial.println(digitalRead(18));

    delay(100); // Wait for 3 seconds before sending the next packet
}
