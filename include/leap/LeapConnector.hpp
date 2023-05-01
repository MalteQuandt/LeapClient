#pragma once

#include <Leap.h>

#include <osc/OSCLeapClient.hpp>
#include <osc/OSCLeapClient.hpp>

namespace ctag::leap {
    // listener object that checks if the leap motion controller currently exists, and if it does, send the data to it
    class LeapConnector : Leap::Listener {
    public:
        /**
         * @brief Establish a connection to the Leap Motion Controller
         *
         * @param clo The command line options that should be used to create the connection
         */
        explicit LeapConnector(const ctag::util::CLOptions& clo);

        // explicitly imported/overwritten leap motion functions

        void onConnect(const Leap::Controller& c) override;
        void onDeviceChange(const Leap::Controller& c) override;

        void onDisconnect(const Leap::Controller &) override;
        void onExit(const Leap::Controller &) override;
        void onFrame(const Leap::Controller &) override;

        /**
         * @brief Close the connection to the leap motion controller
         */
        ~LeapConnector();
    private:

        /**
         * @brief Send the Palm orientation and other data to the server
         */
        void sendPalm(const Leap::Frame& frame);

        /**
         * @brief Send the type of the Hand (Left or right!)
         * @param frame
         */
        void sendHandType(const Leap::Frame& frame);
        /**
         * The internal representation of the Leap Motion Controller.
         */
        Leap::Controller controller;
        ctag::osc::OSCLeapClient client;
    };
}