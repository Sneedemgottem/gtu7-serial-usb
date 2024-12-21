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

    this->PrepareTTYPort();
}

// set tty flags in accordance to the ascii data sent over usb
void GPS::PrepareTTYPort() {
    if (tcgetattr(this->serial_port_, &this->tty_) != 0) {
        std::cout << "Error " << errno << " from tcgetattr: " << strerror(errno) << "\n";
    }

    cfsetospeed(&this->tty_, BAUDRATE);
    cfsetispeed(&this->tty_, BAUDRATE);

    // Configure 8N1 (8 data bits, no parity, 1 stop bit)
    this->tty_.c_cflag |= (CLOCAL | CREAD);
    this->tty_.c_cflag &= ~PARENB;
    this->tty_.c_cflag &= ~CSTOPB;
    this->tty_.c_cflag &= ~CSIZE;
    this->tty_.c_cflag |= CS8;

    this->tty_.c_lflag |= ICANON;
    this->tty_.c_lflag &= ~(ECHO | ECHOE | ISIG);
    this->tty_.c_cc[VEOL] = '\n';

    if (tcsetattr(this->serial_port_, TCSANOW, &this->tty_) != 0) {
        std::cout << "Error " << errno << " from tcsetattr: " << strerror(errno) << "\n";
    }
}

std::string GPS::ReadRawSerialMessage() {
    int bytes_read = read(this->serial_port_, this->read_buffer_, sizeof(char) * BUFSIZE);

    this->read_buffer_[bytes_read] = '\0';
    std::string message(this->read_buffer_, bytes_read - 2); // get rid of \r\n at the end

    // flush buffer to remove residual data
    memset(this->read_buffer_, '\0', sizeof(this->read_buffer_));
    return message;
}