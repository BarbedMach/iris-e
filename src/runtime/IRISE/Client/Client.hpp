#pragma once

#include <string>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdexcept>
#include <iostream>
#include "../Messages.hpp"

namespace irise {

class Client {
    public:
        Client(const std::string& socketPath);
        ~Client();

        auto sendMessage(const std::string& message) const -> void;
        auto receiveMessage() const -> std::string;

    private:
        std::string socketPath;
        int clientSocket;
};


} // namespace irise