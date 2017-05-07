//
// Created by Friedemann Stoffregen on 12.04.17.
//

#ifndef SAMPLERV2_BUTTON_H
#define SAMPLERV2_BUTTON_H


#include "InputDevice.h"

class Button: public InputDevice {
    void onChange(Pin pin) override;
    InputDeviceType getInputDeviceType() override;
public:
    Button(std::string name, std::function<void(InputDeviceType type, std::string name, int value)> callback,
           int header, int pin);
};


#endif //SAMPLERV2_BUTTON_H
