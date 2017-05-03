//
// Created by Friedemann Stoffregen on 12.04.17.
//

#include <iostream>
#include "Button.h"

Button::Button(std::string name, int header, int pin) : InputDevice(name) {
    this->addInput(header, pin);
}

void Button::onChange(InputDevice::Pin pin) {
    if (pin.value == 1) {
        emit(pin.value);
    }
}
