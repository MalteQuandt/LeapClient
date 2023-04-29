#include <cxxopts.hpp>
#include <iostream>

#define ENDL "\n"

#include <util/command_line_options.hpp>

using namespace ctag::util;

// CommandLineOptionsContainer

CLOptions::CLOptions(int argc, char **argv) {
    // set the name & description of the program
    cxxopts::Options options {"LeapMotionSender", "Read data from a connected leap motion device"
                                                 "and send them over osc to an osc server"};
    // define the console options
    options.add_options()
            ("ip", "The id-address of the osc-server to connect to", cxxopts::value<std::string>()->default_value("127.0.0.1"))
            ("port", "The port of the osc-server to connect to", cxxopts::value<signed int>()->default_value("9000"))
            ("h,help", "Print the help commands");

    // parse the options
    const auto result = options.parse(argc, argv);

    if (result.count("help")) {
        std::cout << options.help() << ENDL;
        exit(0);
    }

    this->ip = result["ip"].as<std::string>();
    this->port = result["port"].as<unsigned int>();
}

const std::string &CLOptions::getIp() const {
    return this->ip;
}

const unsigned int &CLOptions::getPort() const {
    return this->port;
}