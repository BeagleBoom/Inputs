#include <iostream>
#include "libs/BBBio_lib/BBBiolib.h"
#include "libs/IOManager/Button.h"
#include "libs/IOManager/IOManager.h"

#include <EventQueue/QueueEventEnum.h>
#include <EventQueue/Event.h>
#include <EventQueue/MessageQueue.h>
#include <unistd.h>
#include <memory>

int main() {
    const int queueValue = 2;

    iolib_free();
    iolib_init();
    IOManager io;

    MessageQueue queue = MessageQueue(queueValue);

    io.init([&queue](InputDeviceType type, std::string name, int value) -> void {
        std::unique_ptr<Event> event;
        switch (type) {
            case InputDeviceType::BUTTON:
                if (value == 0) {
                    event.reset(new Event((int) QueueEventEnum::BUTTON_UP));
                } else {
                    event.reset(new Event((int) QueueEventEnum::BUTTON_DOWN));
                }
                break;
            case InputDeviceType::ROTARY_ENCODER:
                if (value == 1) {
                    event.reset(new Event((int) QueueEventEnum::ROTARY_LEFT));
                } else {
                    event.reset(new Event((int) QueueEventEnum::ROTARY_RIGHT));
                }
                break;
            default:
                return;
        }


        event->addString(name);
        std::cout << ">> " << name << "(value: " << value << ")" << std::endl;
        queue.send(*event.get());
    });
    while (true) {
        io.check();
        usleep(100);
    }

    iolib_free();
    return 0;
}
