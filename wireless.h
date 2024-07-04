#ifndef WIRELESS_H
#define WIRELESS_H

#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>

// extern uint8_t broadcastAddress[];

void initializeWireless();
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);

typedef struct struct_message {
    char text[32];
    int value;
} struct_message;

#endif