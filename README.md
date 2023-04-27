## Introduction
This Projects aims to be a simple Leap Motion Listener, which can send the hand position and other data over the network.

## Requirements
This project only supports Windows 10 currently. 
It might be possible to get it to run on other versions, and other operating systems with a bit of work, it was not tested.
Additionally, the only supported compiler is visual studio, because of the leap motion controller

## Installation

Clone this Module with the recurse command:
> git clone --recurse <URL_OF_REMOTE>

## Depends On

| Library                                                                                          | Purpose                                                                     |
|--------------------------------------------------------------------------------------------------|-----------------------------------------------------------------------------|
| [LeapMotionSDK/V2.3.1](https://developer-archive.leapmotion.com/documentation/v2/cpp/index.html) | Establish connection to the Leap Motion Device and collect the data from it |
| [oscpp](https://github.com/kaoskorobase/oscpp)                                                   | Send the Leap Motion Data over the network encoded in the TUOI-Protocol!    |