#include "wireless.h"

// Define the broadcast address
// uint8_t broadcastAddress[] = {0x84, 0xF7, 0x03, 0xF1, 0x1E, 0xDC}; // Replace with actual receiver MAC address for testing
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; // Broadcast address for general use/

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("Last Packet Send Status: ");
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
    esp_wifi_set_protocol(WIFI_IF_STA, WIFI_PROTOCOL_LR);

    // Initialize ESP-NOW
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Register callback function
    esp_now_register_send_cb(OnDataSent);

    // Clear the peerInfo structure
    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    // Check if the peer already exists
    if (esp_now_is_peer_exist(broadcastAddress)) {
        Serial.println("Peer already exists. Deleting and adding again.");
        if (esp_now_del_peer(broadcastAddress) != ESP_OK) {
            Serial.println("Failed to delete existing peer");
            return;
        }
    }

    // Add peer
    esp_err_t addStatus = esp_now_add_peer(&peerInfo);
    if (addStatus != ESP_OK) {
        Serial.println("Failed to add peer");
        Serial.print("Error code: ");
        Serial.println(addStatus);
        Serial.print("Peer MAC Address: ");
        for (int i = 0; i < 6; i++) {
            Serial.printf("%02X", broadcastAddress[i]);
            if (i < 5) Serial.print(":");
        }
        Serial.println();
        return;
    }
    Serial.println("Peer added successfully");
}

esp_err_t sendData(struct_message data) {
    return esp_now_send(broadcastAddress, (uint8_t *) &data, sizeof(data));
}