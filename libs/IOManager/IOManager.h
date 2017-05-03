//
// Created by Friedemann Stoffregen on 12.04.17.
//

#ifndef SAMPLERV2_IOMANAGER_H
#define SAMPLERV2_IOMANAGER_H


#include "InputDevice.h"
#include "../Util/JsonHelper.h"
class IOManager {
protected:
    std::vector<InputDevice *> devices;
    void add(InputDevice *dev);
public:
    void init();
    void check();
};


#endif //SAMPLERV2_IOMANAGER_H
