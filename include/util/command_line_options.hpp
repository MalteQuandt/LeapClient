#pragma once


namespace ctag::util {
    class CLOptions {
        // Container for options that can be provided through the command line
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


    private:
        std::string ip;
        unsigned int port;
    };
}