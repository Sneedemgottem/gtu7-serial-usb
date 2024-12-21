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

    this->SetTTYStructFlags();

    if (tcsetattr(this->serial_port_, TCSANOW, &this->tty_) != 0) {
        std::cout << "Error " << errno << " from tcsetattr: " << strerror(errno) << "\n";
    }
}

// set tty flags in accordance to the ascii data sent over usb
void GPS::SetTTYStructFlags() {
    if (tcgetattr(this->serial_port_, &this->tty_) != 0) {
        std::cout << "Error " << errno << " from tcgetattr: " << strerror(errno) << "\n";
    }

    cfsetospeed(&this->tty_, BAUDRATE);
    cfsetispeed(&this->tty_, BAUDRATE);

    // Configure 8N1 (8 data bits, no parity, 1 stop bit)
    this->tty_.c_cflag = (this->tty_.c_lflag & ~CSIZE) | CS8;
    this->tty_.c_cflag |= (CLOCAL | CREAD);
    this->tty_.c_cflag &= ~(PARENB | CSTOPB | CRTSCTS);

    // disable canonical mode and special character interpretation
    this->tty_.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    this->tty_.c_iflag &= ~(IXON | IXOFF | IXANY);

    // raw output mode
    this->tty_.c_oflag &= ~OPOST;

    // disable posix control characters
    memset(this->tty_.c_cc, _POSIX_VDISABLE, sizeof(this->tty_.c_cc));
}

void GPS::ReadMessageIntoBuffer() {
    int n = read(this->serial_port_, this->read_buffer_, sizeof(char) * BUFSIZE);
    std::cout << "Read " << n << " bytes " << this->read_buffer_ << "\n";
}