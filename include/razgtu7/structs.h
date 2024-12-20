#pragma once

#include <cstdint>

// GPGGA message
typedef struct GGA {
    uint8_t identifier[6]; // $GPGGA fixed 6 bytes
    uint8_t utc_time[10]; // hhmmss.ss
    uint8_t latitude[9]; // in degrees and minutes; llll.ll
    uint8_t latitude_hemisphere[1]; // one byte N or S
    uint8_t longitude[10]; // yyyyy.yy; longitude in degrees and minutes
    uint8_t longitude_hemisphere[1]; // E or W
    uint8_t quality_indicator[1];
    uint8_t num_sattelites[2]; // num sattelites in use
    uint8_t horizontal_dilution[5]; // x.x; dilution of precision
    uint8_t altitude_above_mean_sea[6]; // x.x
    uint8_t altitude_units[1]; // always 'M'
    uint8_t geoidal_separation[5]; // x.x
    uint8_t geoidal_separation_units[1];
    uint8_t age_of_differential_GPS_data[5]; // optional; x.x
    uint8_t differential_reference_station_id[4]; // xxxx
    uint8_t checksum[2]; // 2 bytes fixed
    uint8_t message_terminator[2]; // 2 bytes fixed <CR><LF>
} GGA;