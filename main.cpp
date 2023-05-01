#include <iostream>

#include <util/command_line_options.hpp>
#include <leap/LeapConnector.hpp>
#include <osc/OSCLeapClient.hpp>

// custom end-line definition to not always flush the console...
#define END_LINE "\n"

// namespace definitions
using namespace Leap;
using namespace ctag;
using namespace ctag::util;
using namespace ctag::osc;
using namespace ctag::leap;

int main(int argc, char ** argv) {
    // parse the command line options
    const CLOptions cloc{argc, argv};
    const LeapConnector connector{cloc};

    // define the exit condition, in this case: press exit on the console!
    std::cout << "Press Enter to quit..." END_LINE;
    std::cin.get();

    return 0;
}