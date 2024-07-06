#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>

typedef struct struct_message {
    int steering;
    int drive;
} struct_message;

class Transmitter {
    
    public:
        Transmitter();
        ~Transmitter();

        void init(const uint8_t *receiverMacAddress);
        esp_err_t sendData(struct_message data);
    private:
        static uint8_t broadcastAddress[6];
        static void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);

};

#endif