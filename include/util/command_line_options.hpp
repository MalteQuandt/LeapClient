#pragma once

#include <tuple>

/**
 * Representation of a simple ipv4
 * arg1 = ip
 * arg2 = port
 */
using Address = std::tuple<std::string, signed int>;

namespace ctag::util {
    /**
     * Container for options that can be provided through the command line
     */
    class CLOptions {
    public:
        /**
         * Define and Parse the command line options from the
         *
         * @param argc The length of command line options
         * @param argv All command line options
         */
        explicit CLOptions(int argc, char ** argv);

        /**
         * @brief Fetch the port that was parsed from the command line options
         *
         * @return The port
         */
        const unsigned int& getPort [[nodiscard]] () const;

        /**
         * @brief Fetch the ip that was parsed from the command line options
         *
         * @return The ip
         */
        const std::string& getIp [[nodiscard]] () const;

        /**
         * @brief Fetch the ip and port of the currently set address
         *
         * @return The address tuple
         */
        Address getAddress [[nodiscard]] () const;

    private:
        std::string ip;
        unsigned int port;
    };
}