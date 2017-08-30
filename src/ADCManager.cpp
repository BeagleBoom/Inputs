#include <fcntl.h>
#include <unistd.h>
#include <EventQueue/MessageQueue.h>
#include <EventQueue/QueueEventEnum.h>

#define REFERENCE_VCC 5


int getTone(int16_t value) {
    float_t oneToneSize = 0xfff / (REFERENCE_VCC * 12);
    return (int) lround(0.5 + (value / oneToneSize));
}

struct ADCOut {
    bool gpio6;
    bool gpio7;
    int tone_adc02 = 0;
    int tone_adc03 = 0;
};

void publish(ADCOut out, int queueValue) {
    MessageQueue queue = MessageQueue(queueValue);
    Event event = Event((int) QueueEventEnum::ADC_VALUES);
    event.addString("ADC");
    event.addInt(6);
    event.addInt(static_cast<int>(out.gpio6));

    event.addInt(7);
    event.addInt(static_cast<int>(out.gpio7));

    event.addInt(2);
    event.addInt(out.tone_adc02);

    event.addInt(3);
    event.addInt(out.tone_adc03);

    queue.send(event);
}

int main(int argc, char **argv) {
    int pru_data, pru_clock; // file descriptors
    //  Open a file in write mode.

    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " <Queue Channel Number>" << std::endl;
        return -1;
    }

    int queueValue = std::stoi(argv[1]);

    int16_t buffer[490];
    //  Now, open the PRU character device.
    //  Read data from it in chunks and write to the named pipe.
    ssize_t readpru, prime_char, pru_clock_command;
    pru_data = open("/dev/rpmsg_pru30", O_RDWR);
    if (pru_data < 0)
        std::cout << "Failed to open pru character device rpmsg_pru30." << std::endl;
    //  The character device must be "primed".
    prime_char = write(pru_data, "prime", 6);
    if (prime_char < 0)
        std::cout << "Failed to prime the PRU0 char device." << std::endl;
    //  Now open the PRU1 clock control char device and start the clock.
    pru_clock = open("/dev/rpmsg_pru31", O_RDWR);
    // start reading the adc
    std::cout << "Syncing with pru_clock" << std::endl;
    pru_clock_command = write(pru_clock, "g", 2);
    if (pru_clock_command < 0)
        std::cout << "The pru clock start command failed." << std::endl;

    while (true) {
        readpru = read(pru_data, buffer, 8);
        if (readpru > 0) {
            ADCOut out;
            for (int j = 0; j < 3; j++) {
                if ((buffer[j] >> 8) == 0) {
                    // GPIO Input value
                    out.gpio6 = static_cast<bool>((buffer[j] >> 6) & 1);
                    out.gpio7 = static_cast<bool>((buffer[j] >> 7) & 1);
                } else {
                    // ADC values
                    int16_t value = static_cast<int16_t>(buffer[j] & 0x0fff);
                    int tone = getTone(value);
                    if ((buffer[j] >> 12) == 0x1) {
                        out.tone_adc02 = tone;
                    } else if ((buffer[j] >> 12) == 0x2) {
                        out.tone_adc03 = tone;
                    }
                }
            }
            publish(out, queueValue);
        }

        // tell PRU that we processed the values
        write(pru_data, "ok", 3);
    }
}