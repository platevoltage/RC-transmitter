#if !defined(__HIDJOYSTICKRPTPARSER_H__)
#define __HIDJOYSTICKRPTPARSER_H__

#include <usbhid.h>
#include "Transmitter.h"



struct GamePadEventData {
        uint8_t A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X;
};


class JoystickEvents {
        public:
                virtual void OnGamePadChanged(const GamePadEventData *evt);
                virtual void OnHatSwitch(uint8_t hat);
                virtual void OnButtonUp(uint8_t but_id);
                virtual void OnButtonDn(uint8_t but_id);
                virtual void OnRightButtonUp(uint8_t but_id);
                virtual void OnRightButtonDn(uint8_t but_id);
                virtual void OnAcceleratorChange(uint8_t but_id);
                virtual void OnBrakeChange(uint8_t but_id);
                virtual void OnWheelChange(uint8_t but_id);
                struct_message getParsedHIDReport();
                bool up;
                bool down;
                bool left;
                bool right;

                bool A;
                bool B;
                bool X;
                bool Y;

                bool reverseButton;
        private:
                struct_message messageData;

};

#define RPT_GEMEPAD_LEN		23

class JoystickReportParser : public HIDReportParser {
        JoystickEvents *joyEvents;
        uint8_t oldPad[RPT_GEMEPAD_LEN];
        uint8_t oldAccelerator;
        uint8_t oldBrake;
        uint8_t oldWheel;
        uint16_t oldStandardButtons;
        uint16_t oldRightButtons;

public:
        JoystickReportParser(JoystickEvents *evt);
        virtual void Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
};

#endif // __HIDJOYSTICKRPTPARSER_H__