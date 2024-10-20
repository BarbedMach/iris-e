#pragma once

#include <string>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdexcept>
#include <iostream>
#include <fcntl.h>
#include "../Messages.hpp"

namespace irise {

class Client {
    public:
        Client(const std::string& socketPath);
        ~Client() = default;

        auto reconnect() -> void;
        auto sendMessage(const std::string& message) -> void;
        auto receiveMessage() -> std::string;

    private:
        std::string socketPath;
        int clientSocket;
};


} // namespace irise