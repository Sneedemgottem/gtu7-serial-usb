add_library(
    gps
    gps.cpp
    utils.cpp
    ../include/razgtu7/gps.h
    ../include/razgtu7/structs.h
)

target_include_directories(
    gps PUBLIC
    ../include
)

source_group(
    TREE "${PROJECT_SOURCE_DIR}/include"
    PREFIX "Header Files"
    FILES ${HEADER_LIST}
)