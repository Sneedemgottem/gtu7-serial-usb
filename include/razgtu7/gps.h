#pragma once
#include <termios.h>
#include <unistd.h>
#include <string>
#include "razgtu7/structs.h"

#define TTY "/dev/ttyACM0"
#define BAUDRATE B9600
#define BUFSIZE 100 // messages range from 30 - 80 bytes so 100 is very safe for capture any message

class GPS {
    public:
        GPS();
        ~GPS() {
            close(this->serial_port_);
        }

        //void ReadMessageIntoBuffer(); // TODO: turn into private when done testing
        std::string ReadRawSerialMessage();
        void ParseGPSBuffer(char *read_buf);

    private:
        struct termios tty_;
        int serial_port_;
        char read_buffer_[BUFSIZE]; // this buffer is gonna get reused over and over again to prevent too much allocation

        void SetTTYStructFlags();
};