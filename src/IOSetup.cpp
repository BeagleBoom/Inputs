#include "../libs/Util/JsonHelper.h"
#include <fcntl.h>
#include <zconf.h>


void writeToFile(char *path, int gpio) {
    int fd;
    char buf[255];
    fd = open(path, O_WRONLY);
    sprintf(buf, "%d", gpio);
    write(fd, buf, strlen(buf));
    close(fd);
}

int getLinuxPin(int header, int pin) {
    JsonHelper *json = new JsonHelper((char *) "configs/pins.json");
    std::string port = "port_" + std::to_string(header);
    std::string gpio_str = "pin_" + std::to_string(pin);

    Object::Ptr headerObj = json->getObject(port.c_str());
    return json->getInt(headerObj, gpio_str.c_str());
}

void addExport(int header, int pin) {
    writeToFile((char *) "/sys/class/gpio/export", getLinuxPin(header, pin));
}

void removeExport(int header, int pin) {
    writeToFile((char *) "/sys/class/gpio/unexport", getLinuxPin(header, pin));
}


int main() {
    JsonHelper *ios = new JsonHelper((char *) "configs/io.json");

    /**
     * ADD ALL TE BUTTNS
     */
    for (int i = 0; i < ios->getArray("Buttons")->size(); i++) {
        Object::Ptr obj = ios->getArray("Buttons")->getObject(i);
        addExport(ios->getInt(obj, "header"),
                  ios->getInt(obj, "pin"));

    }

    /**
     * Add all rotary encoders
     */
    for (int i = 0; i < ios->getArray("RotaryEncoders")->size(); i++) {
        Object::Ptr obj = ios->getArray("RotaryEncoders")->getObject(i);
        Object::Ptr state = obj->getObject("state");
        Object::Ptr direction = obj->getObject("direction");
        addExport(
                ios->getInt(state, "header"),
                ios->getInt(state, "pin"));
        addExport(
                ios->getInt(direction, "header"),
                ios->getInt(direction, "pin")
        );

    }

    return 0;
}
