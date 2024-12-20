#include <iostream>
#include "razgtu7/gps.h"

int main() {
    GPS gps;
    char read_buf[100];
    gps.ReadMessage(read_buf, 100);

    return EXIT_SUCCESS;
}