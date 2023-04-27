#include <iostream>
#include <string>
#include <windows.h>

// Leap Motion SDKs
#include <Leap.h>

// custom end-line definition to not always flush the console...
#define ENDL "\n"

using namespace Leap;

class BasicHandPrinterListener : public Listener {
public:
    void onConnect(const Controller& c) override {
        std::cout << "Connected!" ENDL;
        // enable the gestures
        c.enableGesture(Gesture::TYPE_CIRCLE);
        c.enableGesture(Gesture::TYPE_KEY_TAP);
        c.enableGesture(Gesture::TYPE_SCREEN_TAP);
        c.enableGesture(Gesture::TYPE_SWIPE);
    }

    void onFrame(const Controller& c) override {
        const auto frame = c.frame();
        if (! frame.hands().isEmpty()) {
            std::cout << "Frame-ID: " << frame.id() << ENDL;
            std::cout << frame.serialize() << ENDL;
        }
    }
};

int main() {
    // generate basic listener and controller objects
    Controller controller{};
    BasicHandPrinterListener listener{};

    // add the listener to the controller
    controller.addListener(listener);

    // define the exit condition, in this case: press exit on the console!
    std::cout << "Press Enter to quit..." ENDL;
    std::cin.get();

    controller.removeListener(listener);

    return 0;
}
