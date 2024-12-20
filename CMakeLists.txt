cmake_minimum_required(VERSION 3.15...3.30)

project(
    GTU7Interface
    LANGUAGES CXX
)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_EXTENSIONS OFF)
    set_property(GLOBAL PROPERTY USER_FOLDERS ON)
    include(CTest)
endif()

add_subdirectory(src)
add_subdirectory(app)

if ((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR MODERN_CMAKE_BUILD_TESTING)
AND BUILD_TESTING)
    add_subdirectory(tests)
endif()