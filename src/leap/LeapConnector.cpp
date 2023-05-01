#include <string>

#include <leap/LeapConnector.hpp>

#define END_LINE "\n"

using namespace Leap;
using namespace ctag;
using namespace ctag::leap;
using namespace ctag::osc;
using namespace std::string_literals;

LeapConnector::LeapConnector(const ctag::util::CLOptions &clo) :
    controller{},
    client{clo} {

    // enable gestures
    this->controller.enableGesture(Gesture::TYPE_CIRCLE);
    this->controller.enableGesture(Gesture::TYPE_KEY_TAP);
    this->controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
    this->controller.enableGesture(Gesture::TYPE_SWIPE);

    // set the policies
    // make sure that the leap motion controller always works,
    // even with the application running in the background
    this->controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);

    // add the listener
    this->controller.addListener(*this);
}

void LeapConnector::onFrame(const Controller& c) {
    const auto frame = c.frame();
    if (not frame.hands().isEmpty()) {
        this->sendPalm(frame);
    }
}

void LeapConnector::onConnect(const Controller& c) {
    // send the leap-connection message
    this->client.sendPacket(this->client.prepare()
        .openMessage("/godot/leap/connected", 0)
        .closeMessage());
}

void LeapConnector::onDeviceChange(const Leap::Controller &c) {
    // todo: send server message
}

void LeapConnector::onExit(const Leap::Controller &) {
    // todo: send server message
}

void LeapConnector::onDisconnect(const Leap::Controller &) {
    this->client.sendPacket(this->client.prepare()
                                    .openMessage("/godot/leap/disconnect", 0)
                                    .closeMessage());
}

// utility functions

void LeapConnector::sendPalm(const Leap::Frame& frame) {

    const auto& hands = frame.hands();
    // iterate over the hands and send the data
    for(auto i{0ull}; i< hands.count() ;i++){
        // fetch the data to send
        const auto palmPos {frame.hands()[0].palmPosition()};
        const auto palmOrientation {frame.hands()[0].palmNormal()};

        std::cout << "Position: " << palmPos.toString() << END_LINE;
        std::cout << "Orientation: " << palmOrientation.toString() << END_LINE;

        const auto handPalmPath {"/godot/hand/"s + std::to_string(i) + "/palmPos"};
        const auto handOrientationPath {"/godot/hand/"s + std::to_string(i) + "/palmOrientation"};

        this->client.sendPacket(this->client.prepare().
            openBundle(getUnixTimestamp())
                    .openMessage(handPalmPath.c_str(), OSCPP::Tags::array(6))
                        .openArray()
                            .string("x")
                                .float32(palmPos.x)
                            .string("y")
                                .float32(palmPos.y)
                            .string("z")
                                .float32(palmPos.z)
                        .closeArray()
                    .closeMessage()
                        .openMessage(handOrientationPath.c_str(), OSCPP::Tags::array(6) )
                            .openArray()
                                .string("x")
                                    .float32(palmOrientation.x)
                                .string("y")
                                    .float32(palmOrientation.y)
                                .string("z")
                                    .float32(palmOrientation.z)
                            .closeArray()
                        .closeMessage()
                    .closeBundle()
        );
    }
}

LeapConnector::~LeapConnector() {}