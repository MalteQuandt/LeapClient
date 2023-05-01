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
| [cxxopts](https://github.com/jarro2783/cxxopts)                                                  | Parse console arguments/options                                             |
| [Boost](https://www.boost.org/)                                                                                        | For simple UDP communication                                                |

## Protocol

In order to facilitate the communication with the game, a protocol was designed to send important messages. 
It is a superset of the [TUOI](https://www.tuio.org/?specification), and supports the following commands:

1. **Connection Specific**:

| Command                  | Meaning                                                                   | Example                 |
|--------------------------|---------------------------------------------------------------------------|-------------------------|
| /server/connect          | Connect client to server                                                  | "server/connect/"       |
| /server/disconnect       | Disconnect Client from Server                                             | "server/disconnect/"    |
| /godot/leap/connected    | The Leap Controller has been detected and connection has been initialized | "leapgodot/connected"   |
| /godot/leap/disconnected | The Leap Controller has been disconnected!                               | "leapgodot/disconnected | 
 
2. **Leap Data Specific**

| Command                       | Meaning                                                 | Arguments                                        |
|-------------------------------|---------------------------------------------------------|--------------------------------------------------|
| /godot/hand/<ID>/palmPos | Send the Position data of the Palm                      | Array of \["x", x_val, "y", y_val, "z", z_val\]  |
| /godot/hand/<ID>/palmOrientation | Send the Orientation data of the Palm, the Palm Normal! | Array of \["x", x_val, "y", y_val, "z", z_val\]  |
