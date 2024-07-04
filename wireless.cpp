#include "wireless.h"

// Structure to hold the MAC address and other info
// typedef struct struct_message {
//     char text[32];
//     int value;
// } struct_message;

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

void initializeWireless() {
    Serial.println("Initialize ESP-NOW");
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
        Serial.println(esp_now_add_peer(&peerInfo));
        return;
    }

    // Register callback function
    esp_now_register_send_cb(OnDataSent);
}