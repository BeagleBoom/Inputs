#include <iostream>
#include <EventQueue/MessageQueue.h>

int main() {
    MessageQueue queue(1);

    bool stop = false;
    do {
        Event e = queue.receive();
                std::cout << "Message"
                          << "\tNumber: " << e.getInt(0) << std::endl
                          << "\tMessage: " << e.getString(1) << std::endl;
    } while (!stop);
}