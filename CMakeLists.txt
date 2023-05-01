cmake_minimum_required(VERSION 3.25) # we need module support, so 3.25 is the minimum
project(CTAG_Projekt_SS23)

set(CMAKE_CXX_STANDARD 23)

# user defined variables
set(BOOST_ROOT "C:\\Boost" CACHE STRING "The root of the Boost library")

# boost options
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADING ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost REQUIRED COMPONENTS system)

add_subdirectory(libs)

# generate the executable
add_executable(CTAG_Project_SS23 main.cpp)

target_include_directories(CTAG_Project_SS23
        PUBLIC
            ${CMAKE_CURRENT_SOURCE_DIR}/include
        PRIVATE
            ${BOOST_ROOT}/include
        )

target_sources(CTAG_Project_SS23
        PUBLIC
        # utils
            ${CMAKE_CURRENT_SOURCE_DIR}/src/util/services.cpp
        # command line options
            ${CMAKE_CURRENT_SOURCE_DIR}/src/util/command_line_options.cpp
        # osc
            ${CMAKE_CURRENT_SOURCE_DIR}/src/osc/OSCLeapClient.cpp
        # leap
            ${CMAKE_CURRENT_SOURCE_DIR}/src/leap/LeapConnector.cpp
        )

target_link_libraries(CTAG_Project_SS23
        PUBLIC
            LeapMotionSDK
            cxxopts # command line parser
            OSCPP
            ${Boost_LIBRARIES}
        )