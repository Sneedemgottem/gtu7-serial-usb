#include <iostream>
#include <string>
#include <string.h>
#include <termios.h>
#include <fcntl.h>
#include <errno.h>

#include "razgtu7/gps.h"

GPS::GPS() {
    this->serial_port_ = open(TTY, O_RDWR);

    if (this->serial_port_ < 0) {
        std::cout << "Error " << errno << " from open: " << strerror(errno) << "\n";
    }

    if (tcgetattr(this->serial_port_, &this->tty_) != 0) {
        std::cout << "Error " << errno << " from tcgetattr: " << strerror(errno) << "\n";
    }

    this->SetTTYFlags();
}

// set tty flags in accordance to the ascii data sent over usb
void GPS::SetTTYFlags() {
    // control flags
    // this->tty_.c_cflag &= ~PARENB; // clear parity bit
    // this->tty_.c_cflag &= ~CSTOPB; // clear stop field
    // this->tty_.c_cflag &= ~CSIZE; // clear size bits
    // this->tty_.c_cflag |= CS8; // 8 bits per byte (standard)
    // this->tty_.c_cflag &= ~CRTSCTS; // disable hardware RTS
    // this->tty_.c_cflag |= CREAD | CLOCAL; // disbles modem-specific signal lines. CREAD lets us read

    // // local flags
    // this->tty_.c_lflag |= ICANON; // turn on canonical mode
    // // disable echo
    // this->tty_.c_lflag &= ~ECHO;
    // this->tty_.c_lflag &= ~ECHOE;
    // this->tty_.c_lflag &= ~ECHONL;
    // this->tty_.c_lflag &= ~ISIG; // disable interpretation of INTR, QUIT and SUSP

    // // input flags
    // this->tty_.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off software flow control
    // this->tty_.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

    // // output flags
    // this->tty_.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    // this->tty_.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed

    // // tweak these
    // this->tty_.c_cc[VTIME] = 0;
    // this->tty_.c_cc[VMIN] = 0;

    this->tty_.c_lflag |= ICANON;
    this->tty_.c_cc[VEOL] = '\n';
    this->tty_.c_cc[VEOL2] = '\r';

    cfsetspeed(&this->tty_, B9600);

    if (tcsetattr(this->serial_port_, TCSANOW, &this->tty_) != 0) {
        std::cout << "Error " << errno << " from tcsetattr: " << strerror(errno) << "\n";
    }
}

void GPS::ReadMessage(char *read_buf, int buf_size) {
    int n = read(this->serial_port_, read_buf, sizeof(read_buf) * buf_size);
    std::cout << "Read " << n << " bytes " << read_buf << "\n";
}