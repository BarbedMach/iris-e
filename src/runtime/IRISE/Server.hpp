#pragma once

#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <exception>
#include <thread>
#include <mutex>
#include <string>
#include <condition_variable>
#include "Messages.hpp"

namespace irise {

class Server {
    public:
        Server(const Server&) = delete;
        Server& operator==(const Server&) = delete;

        static auto instance() -> Server&;
        static auto instance(const std::string& socketPath) -> Server&;

        ~Server();

        auto waitForHello() -> void;
    private:
        Server(const std::string& socketPath);

        int serverSocket;
        std::string socketPath;

        bool running{ false };
        std::mutex mutexRunning;

        std::thread serverThread;

        bool helloAcknowledged{ false };
        std::mutex conditionMutex;
        std::condition_variable helloReceivedCondition;

        auto readFromClient(int clientSocket) -> std::string;
        auto writeToClient(int clientSocket, const std::string& message) -> void;

        auto loop() -> void;
        auto handleClient(int clientSocket) -> void;
};

} // namespace irise