//
// Created by Friedemann Stoffregen on 12.04.17.
//

#ifndef SAMPLERV2_INPUTDEVICE_H
#define SAMPLERV2_INPUTDEVICE_H

#include <vector>
#include <string>
#include "../BBBio_lib/BBBiolib.h"

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
public:
    InputDevice(std::string name);
    virtual void onChange(Pin pin) = 0;
    virtual void check();
    virtual void emit(int value);
};

#endif //SAMPLERV2_INPUTDEVICE_H
