#pragma once

#include <string>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdexcept>
#include <iostream>
#include <fcntl.h>
#include <vector>
#include <random>
#include <ranges>
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

    auto handleMessage(const std::string& message) -> void;

    auto getState() -> ClientState;
    auto setState(ClientState nextState) -> void;

    auto sendACK() -> void;

    auto mapKernelToDeviceRandomly(const PendingMapping& pendingKernel) -> KernelDeviceMapping;

private:
    ClientState state{ irise::ClientState::Start };

    std::string socketPath;
    int clientSocket{ -1 };

    std::vector<DeviceInfo> devices{};
    std::vector<KernelInfo> kernels{};
};

} // namespace irise
