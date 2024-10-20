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

enum class ClientState {
    Start,
    Connected,
    Ready,
    DeviceInfo,
    KernelInfo,
    MappingProfilingLoop
};

class Client {
    public:
        Client(const std::string& socketPath);
        ~Client() = default;

        auto connect() -> void;
        auto sendMessage(const std::string& message) -> void;
        auto receiveMessage() -> std::string;

        auto getState() -> ClientState;
        auto setState(ClientState nextState) -> void;

    private:
        ClientState state{ Start };

        std::string socketPath;
        int clientSocket{ -1 };
};


} // namespace irise