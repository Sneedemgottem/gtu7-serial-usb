#pragma once
#include <termios.h>
#include <unistd.h>
#include <string>
#include "razgtu7/structs.h"

#define TTY "/dev/ttyACM0"
#define BAUDRATE B9600
#define BUFSIZE 128 // messages range from 30 - 80 bytes so 128 is very safe for capturing any message

class GPS {
    public:
        GPS();
        ~GPS() {
            close(this->serial_port_);
        }

        //void ReadMessageIntoBuffer(); // TODO: turn into private when done testing
        std::string ReadRawSerialMessage();
        void ParseGPSBuffer(char *read_buf);
        void* ParseGPSMessage(const std::string &message); // possibly use a union for returning different structs

    private:
        struct termios tty_;
        int serial_port_;
        char read_buffer_[BUFSIZE];

        void PrepareTTYPort();
};