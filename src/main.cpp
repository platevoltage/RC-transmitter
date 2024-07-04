#include "wireless.h"

void setup() {
    // Initialize Serial Monitor
    Serial.begin(115200);
    pinMode(18, INPUT_PULLUP);
    initializeWireless();

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
    esp_err_t result = sendData(myData);
    

    if (result == ESP_OK) {
        Serial.println("Sent with success");
    } else {
        Serial.println("Error sending the data");
    }

    Serial.print("button - ");
    Serial.println(digitalRead(18));

    delay(100); // Wait for 3 seconds before sending the next packet
}
