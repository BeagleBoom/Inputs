#include <iostream>
#include <EventQueue/MessageQueue.h>

using namespace std;

int main() {
    MessageQueue queue(1);
    bool stop = false;

    do {
        Event e = queue.receive();
        std::cout << "Message" << std::endl;
        std::cout << "\tType: " << e.getType() << std::endl;
        std::cout << "\tMessage: " << e.getString(0) << std::endl;
    } while (!stop);
}