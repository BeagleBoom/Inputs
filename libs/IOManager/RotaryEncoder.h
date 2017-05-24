//
// Created by Friedemann Stoffregen on 12.04.17.
//

#ifndef SAMPLERV2_ROTARYENCODER_H
#define SAMPLERV2_ROTARYENCODER_H


#include "InputDevice.h"

class RotaryEncoder: public InputDevice {
    int stateHeader;
    int statePin;
    int directionHeader;
    int directionPin;
    void onChange(Pin pin) override;
    InputDeviceType getInputDeviceType() override;

public:
    RotaryEncoder(std::string name, std::function<void(InputDeviceType type, std::string name, int value)> callback, int stateHeader, int statePin, int directionHeader, int directionPin);
};


#endif //SAMPLERV2_ROTARYENCODER_H
