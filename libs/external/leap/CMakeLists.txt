cmake_minimum_required(VERSION 3.20)
project(LeapMotionSDK)

message(STATUS "Creating Leap Library")

# if there are any errors, please refer to this page>
# https://developer-archive.leapmotion.com/documentation/v2/cpp/devguide/Leap_SDK_Overview.html#c

set(CMAKE_CXX_STANDARD 11)
set(WINDOWS_PATH $ENV{PATH})

option(ARCHITECTURE_IS_X64 "Is the system that this project is build on x64?" ON)

if(ARCHITECTURE_IS_X64)
    message(STATUS "build the system using x64 libraries")
    set(ARCHITECTURE "x64")
else()
    message(STATUS "build the system using x86 libraries")
    set(ARCHITECTURE "x86")
endif()

# create the library
add_library(LeapMotionSDK INTERFACE)
target_include_directories(LeapMotionSDK INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
message(STATUS "Define the Libraries and copy the DLL's")
target_link_libraries(LeapMotionSDK
        INTERFACE
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/${ARCHITECTURE}/Leap.lib"
        )

# define a list of the dlls that have to be moved to the top level directory
set(LEAP_DLLS "Leap" "msvcp120" "msvcr120")
# copy the dll's into the folder of the executable
foreach(DLL ${LEAP_DLLS})
    target_link_libraries(LeapMotionSDK
            INTERFACE
                "${CMAKE_CURRENT_SOURCE_DIR}/lib/${ARCHITECTURE}/${DLL}.dll"
            )
    configure_file("${PROJECT_SOURCE_DIR}/lib/${ARCHITECTURE}/${DLL}.dll" # input file
            "${CMAKE_BINARY_DIR}/"
            COPYONLY) # output dir
endforeach ()

message(STATUS "Done Building Leap Connector")
