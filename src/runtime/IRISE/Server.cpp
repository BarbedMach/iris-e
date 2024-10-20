#include "Server.hpp"

namespace irise {

auto Server::readFromClient(int clientSocket) -> std::string {
    std::string incomingMessage{};
    char buffer[256];

    while(true) {
        ssize_t bytesRead = read(clientSocket, buffer, sizeof(buffer) - 1);
        if (bytesRead <= 0 && (errno = EAGAIN || errno == EWOULDBLOCK)) {
            break;
        }
        incomingMessage.append(buffer, bytesRead);
    }

    return incomingMessage;
}

auto Server::writeToClient(int clientSocket, const std::string& message) -> void {
    ssize_t bytesWritten = write(clientSocket, message.c_str(), message.size());
    if (bytesWritten < 0 && (errno != EAGAIN && errno != EWOULDBLOCK)) {
        std::cerr << "Server: Error writing to client socket." << std::endl;
    }
}

auto Server::handleClient(int clientSocket) -> void {
    while(true) {
        auto clientMessage = readFromClient(clientSocket);
        if (clientMessage.empty()) {
            break;
        }

        auto message = Message::fromJSONString(clientMessage);
        auto messageType = message.getMessageType();

        {
            auto lock{ std::lock_guard<std::mutex>{ conditionMutex } };

            switch(messageType) {
                using enum MessageType;
                case HELLO:
                    writeToClient(clientSocket, Message{HELLO_ACK});
                    helloAcknowledged = true;
                    helloReceivedCondition.notify_one();
                    break;
                default:
                    writeToClient(clientSocket, Message{UNKNOWN});
                    break;
            }
        }
        }
}

auto Server::loop() -> void {
    while(true) {
        auto lock{ std::unique_lock<std::mutex>{ mutexRunning } };
        if (!running) {
            break;
        }
        lock.unlock();

        handleClient(clientSocket);
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

    int flags = fcntl(serverSocket, F_GETFL, 0);
    if (flags == -1) {
        throw std::runtime_error("Server: fcntl failed to get flags.");
    }
    if (fcntl(serverSocket, F_SETFL, flags | O_NONBLOCK) == -1) {
        throw std::runtime_error("Server: fcntl failed to set non-blocking.");
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
        auto lock{ std::lock_guard<std::mutex>{ mutexRunning } };
        running = true;
    }

    auto clientFound{ false };
    std::cout << "Waiting for a client to connect!" << std::endl;
    while(!clientFound) {
        clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket < 0) {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            continue;
        }
        clientFound = true;

        int flags = fcntl(clientSocket, F_GETFL, 0);
        fcntl(clientSocket, F_SETFL, flags | O_NONBLOCK);
    }

    serverThread = std::thread(&Server::loop, this);
}

Server::~Server() {
    if (serverSocket >= 0) {
        close(serverSocket);
    }
    if (clientSocket >= 0) {
        close(clientSocket);
    }
    if (serverThread.joinable()) {
        serverThread.join();
    }
    unlink(socketPath.c_str());
}

auto Server::waitForHello() -> void {
    std::unique_lock<std::mutex> lock{conditionMutex};
    helloReceivedCondition.wait(lock, [this] {return helloAcknowledged;});
}

} // namepsace irise