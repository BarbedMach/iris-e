#include "Server.hpp"

namespace irise {

auto Server::handleClient(int clientSocket) -> void {
    
}

auto Server::loop() -> void {
    while(true) {
        auto lock{ std::unique_lock<std::mutex>{ mutex } };
        if (!running) {
            break;
        }
        lock.unlock();

        auto clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket < 0) {
            std::cerr << "Server: accept failed." << std::endl;
            continue;
        }

        handleClient(clientSocket);
        close(clientSocket);
    }
}

auto Server::instance(const std::string& socketPath) -> Server& {
    static Server server{socketPath};
    return server;
}

auto Server::instance() -> Server& {
    return Server::instance("tmp/irise_socket");
}

Server::Server(const std::string& socketPath) : serverSocket(socket(AF_UNIX, SOCK_STREAM, 0)), socketPath(socketPath) {
    if (serverSocket < 0) {
        throw std::runtime_error("Server: socket creation failed.");
    }

    sockaddr_un serverAddr;
    serverAddr.sun_family = AF_UNIX;
    strcpy(serverAddr.sun_path, socketPath.c_str());
    unlink(socketPath.c_str());

    if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) < 0) {
        throw std::runtime_error("Server: socket bind failed.");
    }

    if (listen(serverSocket, 1) < 0) {
        throw std::runtime_error("Server: socket listen failed.");
    }

    std::cout << "Server listening on: " << socketPath << std::endl;

    {
        auto lock{ std::lock_guard<std::mutex>{ mutex } };
        running = true;
    }

    serverThread = std::thread(&Server::loop, this);
}

Server::~Server() {
    if (serverSocket >= 0) {
        close(serverSocket);
    }
    unlink(socketPath.c_str());
}

} // namepsace irise