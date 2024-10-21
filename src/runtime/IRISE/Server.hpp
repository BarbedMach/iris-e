#pragma once

#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <fcntl.h>
#include <exception>
#include <thread>
#include <mutex>
#include <string>
#include <chrono>
#include <condition_variable>
#include "Messages.hpp"

namespace irise {

enum class ServerState {
    Start,
    Connected,
    Ready,
    DeviceInfo,
    KernelInfo,
    MappingProfilingLoop
};

class Server {
    public:
        Server(const Server&) = delete;
        Server& operator==(const Server&) = delete;

        static auto instance() -> Server&;
        static auto instance(const std::string& socketPath) -> Server&;

        ~Server();

        auto getState() -> ServerState;
        auto setState(ServerState nextState) -> void;

        auto waitForHelloACK() -> void;
        auto waitForACK() -> void;

        auto sendDeviceInfo(DeviceInfo deviceInfo) -> Server&;
        auto sendKernelInfo(KernelInfo kernelInfo) -> Server&;

        auto sendMappingForKernelPending(PendingMapping pendingMapping) -> Server&;
    private:
        Server(const std::string& socketPath);

        ServerState state{ ServerState::Start };

        int serverSocket;
        int clientSocket{ -1 };
        std::string socketPath;

        bool running{ false };
        std::mutex mutexRunning;

        std::thread serverThread;

        bool helloAcknowledged{ false };
        std::mutex conditionMutex;
        std::condition_variable helloReceivedCondition;

        bool acknowledged{ false };
        std::condition_variable messageAcknowledged;

        auto readFromClient() -> std::string;
        auto writeToClient(const std::string& message) -> void;

        auto loop() -> void;
        auto handleClient() -> void;
};

} // namespace irise