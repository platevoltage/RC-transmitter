#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>

// Structure to hold the MAC address and other info
typedef struct struct_message {
    char text[32];
    int value;
} struct_message;

// MAC address of the receiver
// uint8_t broadcastAddress[] = {0x84, 0xF7, 0x03, 0xF1, 0x1E, 0xDC};
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("Last Packet Send Status:");
    if (status == ESP_NOW_SEND_SUCCESS) {
        Serial.println("Delivery Success");
    } else {
        Serial.println("Delivery Fail");
    }
}

void setup() {
    // Initialize Serial Monitor
    Serial.begin(115200);
    pinMode(18, INPUT_PULLUP);
    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);
    esp_wifi_set_max_tx_power(84);
    esp_wifi_set_protocol( WIFI_IF_STA , WIFI_PROTOCOL_LR);

    // Initialize ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Register peer
    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    // Add peer
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }

    // Register callback function
    esp_now_register_send_cb(OnDataSent);

}

// int value = 0xFF0000;
int value = 0;
void loop() {
    if (digitalRead(18)) {
    //   value = 0x0000FF;
    value = 0;
    } else {
    //   value = 0xFF0000;
    value = 180;
    }
    // Sample message
    struct_message myData;
    strcpy(myData.text, "Hello");
    myData.value = value;

    // Send message
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

    if (result == ESP_OK) {
        Serial.println("Sent with success");
    } else {
        Serial.println("Error sending the data");
    }

    Serial.print("button - ");
    Serial.println(digitalRead(18));

    delay(100); // Wait for 3 seconds before sending the next packet
}
