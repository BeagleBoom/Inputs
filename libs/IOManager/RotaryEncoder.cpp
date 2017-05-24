//
// Created by Friedemann Stoffregen on 12.04.17.
//

#include <iostream>
#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(std::string name, std::function<void(InputDeviceType type, std::string name, int value)> callback,
                             int stateHeader, int statePin, int directionHeader, int directionPin) : InputDevice(name, callback) {
    this->addInput(stateHeader, statePin);
    this->addInput(directionHeader, directionPin);
    this->directionHeader = directionHeader;
    this->directionPin = directionPin;
}

void RotaryEncoder::onChange(InputDevice::Pin pin) {
    if (pin.header == this->directionHeader && pin.pin == this->directionPin)
        return;

    InputDevice::Pin directionPin = pins.at(1);
    if (pin.value == 0) {
        emit(directionPin.value);
    }
}

InputDeviceType RotaryEncoder::getInputDeviceType() {
    return InputDeviceType::ROTARY_ENCODER;
}