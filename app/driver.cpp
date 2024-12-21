#include <iostream>
#include "razgtu7/gps.h"
#include <chrono>
#include <string>
#include <thread>

int main() {
    GPS gps;

    // there's currently a buffer overflow issue somehow and also it reads \r and \n into the buffer when it gets skipped.
    while (true) {
        std::string message = gps.ReadRawSerialMessage();
        std::cout << "message: [" << message << "]\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return EXIT_SUCCESS;
}