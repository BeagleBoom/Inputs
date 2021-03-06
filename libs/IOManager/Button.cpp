//
// Created by Friedemann Stoffregen on 12.04.17.
//

#include <iostream>
#include "Button.h"

Button::Button(std::string name, std::function<void(InputDeviceType type, std::string name, int value)> callback,
               int header, int pin) : InputDevice(name, callback) {
    this->addInput(header, pin);
}

void Button::onChange(InputDevice::Pin pin) {
    emit(pin.value);
}

InputDeviceType Button::getInputDeviceType() {
    return InputDeviceType::BUTTON;
}
