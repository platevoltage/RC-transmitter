#ifndef WIRELESS_H
#define WIRELESS_H

#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>

extern uint8_t broadcastAddress[];

typedef struct struct_message {
    char text[32];
    int value;
} struct_message;

void initializeWireless();
esp_err_t sendData(struct_message data);


#endif