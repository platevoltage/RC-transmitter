#include "hidjoystickrptparser.h"


JoystickReportParser::JoystickReportParser(JoystickEvents *evt) :
joyEvents(evt),
oldAccelerator(0xDE),
oldStandardButtons(0) {
        for (uint8_t i = 0; i < RPT_GEMEPAD_LEN; i++)
                oldPad[i] = 0xD;
}

struct_message messageData;

void JoystickReportParser::Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf) {

        bool match = true;
        
        // for (uint8_t i = 0; i < RPT_GEMEPAD_LEN; i++) {
        //         Serial.print("0x");
        //         if (buf[i] < 16) {
        //                 Serial.print("0"); // Add leading zero if value is less than 16
        //         }
        //         Serial.print(buf[i], HEX);
        //         Serial.print("  ");
        // }
        // Serial.println();

        for (uint8_t i = 0; i < RPT_GEMEPAD_LEN; i++) {
        // Checking if there are changes in report since the method was last called
                if (buf[i] != oldPad[i]) {
                        match = false;
                        break;
                }
        }

        // Calling Game Pad event handler
        if (!match && joyEvents) {
                //PRINTS VALUES
                // joyEvents->OnGamePadChanged((const GamePadEventData*)buf);

                for (uint8_t i = 0; i < RPT_GEMEPAD_LEN; i++) oldPad[i] = buf[i];
        }

        uint8_t accelerator = (buf[6]);
        if (accelerator != oldAccelerator && joyEvents) {
                // Serial.println(buf[5], HEX);
                joyEvents->OnAcceleratorChange(accelerator);
                oldAccelerator = accelerator;
        }

        uint8_t brake = (buf[12]);
        if (brake != oldBrake && joyEvents) {
                joyEvents->OnBrakeChange(brake);
                oldBrake = brake;
        }

        uint8_t wheel = (buf[2]);
        if (wheel != oldWheel && joyEvents) {
                joyEvents->OnWheelChange(wheel);
                oldWheel = wheel;
        }

        uint16_t standardButtons = (0x0000 | buf[18]);
        standardButtons <<= 4;
        standardButtons |= (buf[17] >> 4);
        uint16_t standardChanges = (standardButtons ^ oldStandardButtons);

        // Calling Button Event Handler for every button changed
        if (standardChanges) {
                for (uint8_t i = 0; i < 0x0C; i++) {
                        uint16_t mask = (0x0001 << i);

                        if (((mask & standardChanges) > 0) && joyEvents) {
                                if ((standardButtons & mask) > 0)
                                        joyEvents->OnButtonDn(i + 1);
                                else
                                        joyEvents->OnButtonUp(i + 1);
                        }
                }
                oldStandardButtons = standardButtons;
        }


        uint16_t rightButtons = (0x0000 | buf[22]);
        rightButtons <<= 4;
        rightButtons |= (buf[21] >> 4);
        uint16_t rightChanges = (rightButtons ^ oldRightButtons);

        // Calling Button Event Handler for every button changed
        if (rightChanges) {
                for (uint8_t i = 0; i < 0x0C; i++) {
                        uint16_t mask = (0x0001 << i);

                        if (((mask & rightChanges) > 0) && joyEvents) {
                                if ((rightButtons & mask) > 0)
                                        joyEvents->OnRightButtonDn(i + 1);
                                else
                                        joyEvents->OnRightButtonUp(i + 1);
                        }
                }
                oldRightButtons = rightButtons;
        }
}

void JoystickEvents::OnGamePadChanged(const GamePadEventData *evt) {
        Serial.print("A: ");
        PrintHex<uint8_t > (evt->A, 0x80);
        Serial.print("\tB: ");
        PrintHex<uint8_t > (evt->B, 0x80);
        Serial.print("\tC: ");
        PrintHex<uint8_t > (evt->C, 0x80);
        Serial.print("\tD: ");
        PrintHex<uint8_t > (evt->D, 0x80);
        Serial.print("\tE: ");
        PrintHex<uint8_t > (evt->E, 0x80);
        Serial.print("\tF: ");
        PrintHex<uint8_t > (evt->F, 0x80);
        Serial.print("\tG: ");
        PrintHex<uint8_t > (evt->G, 0x80);
        Serial.print("\tH: ");
        PrintHex<uint8_t > (evt->H, 0x80);
        Serial.print("\tI: ");
        PrintHex<uint8_t > (evt->I, 0x80);
        Serial.print("\tJ: ");
        PrintHex<uint8_t > (evt->J, 0x80);
        Serial.print("\tK: ");
        PrintHex<uint8_t > (evt->K, 0x80);
        Serial.print("\tL: ");
        PrintHex<uint8_t > (evt->L, 0x80);
        Serial.print("\tM: ");
        PrintHex<uint8_t > (evt->M, 0x80);
        Serial.print("\tN: ");
        PrintHex<uint8_t > (evt->N, 0x80);
        Serial.print("\tO: ");
        PrintHex<uint8_t > (evt->O, 0x80);
        Serial.print("\tP: ");
        PrintHex<uint8_t > (evt->P, 0x80);
        Serial.print("\tQ: ");
        PrintHex<uint8_t > (evt->Q, 0x80);
        Serial.print("\tR: ");
        PrintHex<uint8_t > (evt->R, 0x80);
        Serial.print("\tS: ");
        PrintHex<uint8_t > (evt->S, 0x80);
        Serial.print("\tT: ");
        PrintHex<uint8_t > (evt->T, 0x80);
        Serial.print("\tU: ");
        PrintHex<uint8_t > (evt->U, 0x80);
        Serial.print("\tV: ");
        PrintHex<uint8_t > (evt->V, 0x80);
        Serial.print("\tW: ");
        PrintHex<uint8_t > (evt->W, 0x80);
        Serial.print("\tX: ");
        PrintHex<uint8_t > (evt->X, 0x80);
        Serial.println("");
}

void JoystickEvents::OnHatSwitch(uint8_t hat) {
        // Serial.print("Hat Switch: ");
        // PrintHex<uint8_t > (hat, 0x80);
        // Serial.println("");
}

void JoystickEvents::OnButtonUp(uint8_t but_id) {
        Serial.print("Up: ");
        Serial.println(but_id, DEC);
        switch (but_id) {
                case 1: A = false; break;
                case 2: B = false; break;
                case 3: X = false; break;
                case 4: Y = false; break;
                case 5: up = false; break;
                case 6: right = false; break;
                case 7: down = false; break;
                case 8: left = false; break;
        }
}

void JoystickEvents::OnButtonDn(uint8_t but_id) {
        Serial.print("Dn: ");
        Serial.println(but_id, DEC);
        switch (but_id) {
                case 1: A = true; break;
                case 2: B = true; break;
                case 3: X = true; break;
                case 4: Y = true; break;
                case 5: up = true; break;
                case 6: right = true; break;
                case 7: down = true; break;
                case 8: left = true; break;
        }
}

void JoystickEvents::OnRightButtonUp(uint8_t but_id) {
        Serial.print("Up: ");
        Serial.println(but_id, DEC);
        switch (but_id) {
                // case 1: A = false; break;
                // case 2: B = false; break;
                case 3: reverseButton = false; break;
                // case 4: Y = false; break;
                // case 5: up = false; break;
                // case 6: right = false; break;
                // case 7: down = false; break;
                // case 8: left = false; break;
        }
}

void JoystickEvents::OnRightButtonDn(uint8_t but_id) {
        Serial.print("Dn: ");
        Serial.println(but_id, DEC);
        switch (but_id) {
                // case 1: A = true; break;
                // case 2: B = true; break;
                case 3: reverseButton = true; break;
                // case 4: Y = true; break;
                // case 5: up = true; break;
                // case 6: right = true; break;
                // case 7: down = true; break;
                // case 8: left = true; break;
        }
}

void JoystickEvents::OnAcceleratorChange(uint8_t but_id) {
        // Serial.print("Accelerator: ");
        if (but_id >= 128) but_id -= 128;
        else but_id+=128;
        but_id*=.4;
        // Serial.println(but_id, DEC); 
        

        messageData.accelerator = but_id;

        
}

void JoystickEvents::OnBrakeChange(uint8_t but_id) {
        // Serial.print("Brake: ");
        if (but_id >= 128) but_id -= 128;
        else but_id+=128;
        but_id*=.15;
        // Serial.println(but_id, DEC); 
        messageData.brake = but_id;
}

void JoystickEvents::OnWheelChange(uint8_t but_id) {
        // Serial.print("Wheel: ");
        if (but_id >= 128) but_id -= 128;
        else but_id+=128;
        but_id*=.706;

        // Serial.println(but_id, DEC); 

        
        messageData.steering = but_id;


}

struct_message JoystickEvents::getParsedHIDReport() {
        messageData.drive = 90 + messageData.accelerator - messageData.brake;
        if (messageData.drive < 0) {
                messageData.drive = 0;
        }
        return messageData;
}