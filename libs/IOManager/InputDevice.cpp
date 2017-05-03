//
// Created by Friedemann Stoffregen on 12.04.17.
//

#include <iostream>
#include "InputDevice.h"
#include "../Util/JsonHelper.h"

void InputDevice::check() {
    for (auto &i:pins) {
        // because it's pull-up...
        int value = is_low(i.header, i.pin);
        if (value != i.value) {
            i.value = value;
            this->onChange(i);
        }
    }
}

/**
 * Initialize pins
 * @param pins
 */
void InputDevice::addInput(int header, int pin) {
    Pin p;
    p.header = header;
    p.pin = pin;
    //this->addExport(p);
    this->pins.push_back(p);
    iolib_setdir(p.header, p.pin, BBBIO_DIR_IN);
}


InputDevice::InputDevice(std::string name) {
    this->name = name;
}

void InputDevice::emit(int value) {
    std::cout << this->name << " " << value << std::endl;
}
