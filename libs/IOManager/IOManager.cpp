//
// Created by Friedemann Stoffregen on 12.04.17.
//

#include "IOManager.h"
#include "Button.h"
#include "RotaryEncoder.h"

void IOManager::add(InputDevice *dev) {
    this->devices.push_back(dev);
}

void IOManager::check() {
    for (auto &i:this->devices) {
        i->check();
    }
}

void IOManager::init() {
    JsonHelper *json = new JsonHelper((char *) "configs/io.json");
    /**
     * ADD ALL TE BUTTNS
     */
    for (int i = 0; i < json->getArray("Buttons")->size(); i++) {
        Object::Ptr obj = json->getArray("Buttons")->getObject(i);
        Button *btn = new Button(
                json->getString(obj, "name"),
                json->getInt(obj, "header"),
                json->getInt(obj, "pin"));

        this->add(btn);
    }

    /**
     * Add all rotary encoders
     */
    for (int i = 0; i < json->getArray("RotaryEncoders")->size(); i++) {
        Object::Ptr obj = json->getArray("RotaryEncoders")->getObject(i);
        Object::Ptr state = obj->getObject("state");
        Object::Ptr direction = obj->getObject("direction");
        RotaryEncoder *encoder = new RotaryEncoder(
                json->getString(obj, "name"),
                json->getInt(state, "header"),
                json->getInt(state, "pin"),
                json->getInt(direction, "header"),
                json->getInt(direction, "pin")
        );

        this->add(encoder);
    }
}
