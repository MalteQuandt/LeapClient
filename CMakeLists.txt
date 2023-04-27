cmake_minimum_required(VERSION 3.25)
project(CTAG_Projekt_SS23)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(libs)

# generate the executable
add_executable(CTAG_Project_SS23 main.cpp)
target_include_directories(CTAG_Project_SS23
        PUBLIC
            "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(CTAG_Project_SS23
        PUBLIC
            LeapMotionSDK)
