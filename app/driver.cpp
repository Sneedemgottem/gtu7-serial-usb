#include <iostream>
#include "razgtu7/gps.h"
#include <chrono>
#include <string>
#include <thread>

int main() {
    GPS gps;

    while (true) {
        std::string message = gps.ReadRawSerialMessage();
        std::cout << "message: [" << message << "]\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return EXIT_SUCCESS;
}