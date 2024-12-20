add_executable(
    run
    driver.cpp
)

target_link_libraries(
    run PRIVATE
    gps
)