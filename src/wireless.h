#ifndef WIRELESS_H
#define WIRELESS_H

#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>

typedef struct struct_message {
    char text[32];
    int value;
} struct_message;

class Wireless {
    
    public:
        Wireless();
        ~Wireless();

        void init(const uint8_t *receiverMacAddress);
        esp_err_t sendData(struct_message data);
    private:
        static uint8_t broadcastAddress[6];
        static void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);

};

#endif