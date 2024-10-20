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
    std::cout << "To client [" << clientSocket << "] : '" << message << "'" << std::endl;
    ssize_t bytesWritten = write(clientSocket, message.c_str(), message.size());
    if (bytesWritten < 0 && (errno != EAGAIN && errno != EWOULDBLOCK)) {
        std::cerr << "Server: Error writing to client socket." << std::endl;
    }
}

auto Server::handleClient(int clientSocket) -> void {
    auto clientMessage = readFromClient(clientSocket);
    std::cout << "Server received message: " << clientMessage << std::endl; // Debug output

    auto message = Message::fromJSONString(clientMessage);
    auto messageType = message.getMessageType();

    std::cout << "Message type is : " << Message::toString(messageType) << std::endl;

    {
        std::cout << "Entered the lock guard for conditionMutex!" << std::endl;
        auto lock{ std::lock_guard<std::mutex>{ conditionMutex } };
        std::cout << "Lock guard for conditionMutex passed" << std::endl;

        switch(messageType) {
            using enum MessageType;
            std::cout << "Message type switch entered." << std::endl;
            case HELLO:
                std::cout << "HELLO case reached!" << std::endl;
                writeToClient(clientSocket, Message{HELLO_ACK});
                std::cout << "Server sent HELLO_ACK" << std::endl; // Debug output

                helloAcknowledged = true;
                helloReceivedCondition.notify_one();
                break; // Use break instead of default
            default:
                writeToClient(clientSocket, Message{UNKNOWN});
                std::cout << "Server sent UNKNOWN response" << std::endl; // Debug output
                break;
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

        auto clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket < 0) {
            std::cerr << "Server: accept failed. Retrying in 2 seconds..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
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

    serverThread = std::thread(&Server::loop, this);
}

Server::~Server() {
    if (serverSocket >= 0) {
        close(serverSocket);
    }
    if (serverThread.joinable()) {
        serverThread.join();
    }
    unlink(socketPath.c_str());
}

auto Server::waitForHello() -> void {
    std::cout << "Wait for hello entered" << std::endl;
    std::unique_lock<std::mutex> lock{conditionMutex};
    std::cout << "Wait for hello lock passed." << std::endl;
    helloReceivedCondition.wait(lock, [this] {return helloAcknowledged;});
}

} // namepsace irise