#include <iostream>
#include "../libs/BBBio_lib/BBBiolib.h"
#include "../libs/IOManager/Button.h"
#include "../libs/IOManager/IOManager.h"

#include <EventQueue/EventType.h>
#include <EventQueue/Event.h>
#include <EventQueue/MessageQueue.h>
#include <unistd.h>
// Don't remove this. It's needed on Linux.
#include <memory>

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " <Queue Channel Number>" << std::endl;
        return -1;
    }

    int queueValue = std::stoi(argv[1]);

    iolib_free();
    iolib_init();
    IOManager io;

    MessageQueue queue = MessageQueue(queueValue);

    io.init([&queue](InputDeviceType type, std::string name, int value) -> void {
        std::unique_ptr<Event> event;
        switch (type) {
            case InputDeviceType::BUTTON:
                if (value == 0) {
                    event.reset(new Event(EventType::BUTTON_UP));
                } else {
                    event.reset(new Event(EventType::BUTTON_DOWN));
                }
                break;
            case InputDeviceType::ROTARY_ENCODER:
                if (value == 1) {
                    event.reset(new Event(EventType::ROTARY_LEFT));
                } else {
                    event.reset(new Event(EventType::ROTARY_RIGHT));
                }
                break;
            default:
                return;
        }
        event->addString(name);
        std::cout << ">> (value: " << event->getString(0) << ")" << std::endl;
        queue.send(*event);
    });
    while (true) {
        io.check();
        usleep(100);
    }

    iolib_free();
    return 0;
}
