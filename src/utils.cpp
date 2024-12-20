// this file is primarly used to interface with the C termios library to make it look like C++

#include "razgtu7/gps.h"

#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
