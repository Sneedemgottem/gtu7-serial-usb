#pragma once
#include <termios.h>
#include <unistd.h>

#define TTY "/dev/ttyACM0"

class GPS {
    public:
        GPS();
        ~GPS() {
            close(this->serial_port_);
        }

        void ReadMessage(char *read_buf, int buf_size);
    private:
        struct termios tty_;
        int serial_port_;

        void SetTTYFlags();
};