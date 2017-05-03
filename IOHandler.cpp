#include <iostream>
#include "libs/BBBio_lib/BBBiolib.h"
#include "libs/IOManager/Button.h"
#include "libs/IOManager/IOManager.h"
#include "libs/IOManager/RotaryEncoder.h"
#include <unistd.h>

int main() {
    iolib_free();
    iolib_init();
    IOManager io;
    io.init();
    /*Button *btn = new Button("Button1", 8, 13);
    Button *btn2 = new Button("Button2", 9, 24);
    Button *btn3 = new Button("Button3", 9, 12);
    RotaryEncoder *enc = new RotaryEncoder("Rotary1", 8, 11, 8, 12);
    io.add(btn);
    io.add(btn2);
    io.add(btn3);
    io.add(enc);*/
    while (true) {
        io.check();
        usleep(100);
    }


    iolib_free();
    return 0;
}
