#include <iostream>
#include <EventQueue/MessageQueue.h>
#include <EventQueue/QueueEventEnum.h>

using namespace std;

int main() {
    MessageQueue queue(1);
    bool stop = false;

    do {
        Event e = queue.receive();
        std::cout << "Message" << std::endl;
        std::cout << "\tType: " << e.getType() << std::endl;
        std::cout << "\tMessage: " << e.getString(0) << std::endl;
        std::cout << "\tEvent:";
        switch (e.getType()) {
            case static_cast<int>(QueueEventEnum::BUTTON_UP):
                std::cout << "BUTTON_UP" << std::endl;
                break;
            case static_cast<int>(QueueEventEnum::BUTTON_DOWN):
                std::cout << "BUTTON_DOWN" << std::endl;
                break;
            case static_cast<int>(QueueEventEnum::ROTARY_RIGHT):
                std::cout << "ROTARY_RIGHT" << std::endl;
                break;
            case static_cast<int>(QueueEventEnum::ROTARY_LEFT):
                std::cout << "ROTARY_LEFT" << std::endl;
                break;
            case static_cast<int>(QueueEventEnum::ADC_VALUES):
                std::cout << "ADC_VALUES" << std::endl;
                std::cout << "\tValues:" << std::endl;
                std::cout << "\t\t TBA" << std::endl;
                // TODO: Extract channel values.
                break;
        }
    } while (!stop);
}