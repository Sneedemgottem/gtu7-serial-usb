#pragma once

#include <cstdint>
#include <string>

typedef union Message {
    std::string message_type;
    GGA gga;
    GLL gll;
    GSA gsa;
    GSV gsv;
    MSS mss;
    RMC rmc;
    VTG vtg;
} Message;

//// MESSAGE DEFINITION

typedef struct GGA {
    UTC utc_time;
    GeographicalCoordinate coord;
    unsigned int position_fix_indicator : 4; // specifies quality and reliability of signal
    unsigned int satellites_used : 4;
    float horizontal_dilution_of_precision;
    float msl_altitude; // in meters
    float geoid_separation; // in meters
    float age_of_differential_correction; // in seconds
    unsigned int checksum : 8;
} GGA;

typedef struct GLL {
    GeographicalCoordinate coord;
    UTC utc_time;
    char status; // A = data valid, V = data not valid
    char mode; // A = Autonomous, D = DGPS, E = DR
    unsigned int checksum : 8;
} GLL;

typedef struct GSA {
    char mode_1; // M = manual - forced to operate in 2D or 3D mode, A = 2D automatic - allowed to automatically switch 2D/3D
    unsigned int mode_2 : 4; // 1 = fix not available, 2 = 2D, 3 = 3D
    unsigned int satellites_used : 72; // 72-bit bit field for satellites used. Each field uses 6 bits between 0 and 32 in decimal
    float pdop; // position dilution of precision
    float hdop; // horizontal dilution of precision
    float vdop; // vertical dilution of precision
    unsigned int checksum : 8;
} GSA;


typedef struct GSV {

} GSV;

typedef struct MSS {

} MSS;

typedef struct RMC {

} RMC;

typedef struct VTG {

} VTG;

//// SPECIAL FIELDS

typedef struct GeographicalCoordinate {
    // latitude measures distance north or south of the equator
    unsigned int latitude_degrees : 7; // degrees between 0 and 90
    char n_s_indicator; // north/south indicator
    // longitude measures distance east or west of the prime meridian
    unsigned int longitude_degrees : 8; // degrees between 0 and 180
    char e_w_indicator; // east/west indicator
} GeographicalCoordinate;

// hhmmss.sss
typedef struct UTC {
    unsigned int hours : 5;
    unsigned int minutes: 8;
    float seconds;
} UTC;

// ddmmyy
typedef struct Date {
    unsigned int day : 5;
    unsigned int month : 4;
    unsigned int year : 8;
} Date;
