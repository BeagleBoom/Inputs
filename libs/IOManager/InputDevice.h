//
// Created by Friedemann Stoffregen on 12.04.17.
//

#ifndef SAMPLERV2_INPUTDEVICE_H
#define SAMPLERV2_INPUTDEVICE_H

#include <vector>
#include <string>
#include "../BBBio_lib/BBBiolib.h"

enum InputDeviceType { BUTTON, ROTARY_ENCODER };


class InputDevice {
    /**
     * Return PINs
     *
     */
protected:

    struct Pin {
        int header;
        int pin;
        int value = -1;
    };

    std::vector<Pin> pins;
    std::string name;
    void addInput(int header, int pin);
    std::function<void(InputDeviceType type, std::string name, int value)> callback;

public:
    InputDevice(std::string name, std::function<void(InputDeviceType type, std::string name, int value)> callback);
    virtual void onChange(Pin pin) = 0;
    virtual void check();
    virtual void emit(int value);

    virtual InputDeviceType getInputDeviceType();
};

#endif //SAMPLERV2_INPUTDEVICE_H
