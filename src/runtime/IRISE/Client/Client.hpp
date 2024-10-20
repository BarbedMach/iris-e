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

        auto sendMessage(const std::string& message) const -> void;
        auto receiveMessage() const -> std::string;

    private:
        std::string socketPath;
        int clientSocket;
};


} // namespace irise