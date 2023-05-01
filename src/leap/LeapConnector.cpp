#include <leap/LeapConnector.hpp>

#define END_LINE "\n"

using namespace Leap;
using namespace ctag;
using namespace ctag::leap;
using namespace ctag::osc;

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
        // todo: very basic test code, remove for more sturdy one later!
        std::cout << "Frame-ID: " << frame.id() << END_LINE;
        const auto palmPos {frame.hands()[0].palmPosition()};
        const auto palmOrientation {frame.hands()[0].palmNormal()};
        std::cout << palmPos.toString() << END_LINE;
        this->client.sendPacket(this->client.prepare().
            openBundle(getUnixTimestamp())
                .openMessage("/godot/hand/0/palmPos", OSCPP::Tags::array(6) )
                    .openArray()
                        .string("x")
                            .float32(palmPos.x)
                        .string("y")
                            .float32(palmPos.y)
                        .string("z")
                            .float32(palmPos.z)
                    .closeArray()
                .closeMessage()
                    .openMessage("/godot/hand/0/palmOrientation", OSCPP::Tags::array(6) )
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

void LeapConnector::onConnect(const Controller& c) {
    // todo: send server message
}

void LeapConnector::onDeviceChange(const Leap::Controller &c) {
    // todo: send server message
}

void LeapConnector::onExit(const Leap::Controller &) {
    // todo: send server message
}

void LeapConnector::onDisconnect(const Leap::Controller &) {
    // todo: send server message
}

LeapConnector::~LeapConnector() {}