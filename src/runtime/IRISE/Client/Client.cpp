#include "Client.hpp"

namespace irise {

Client::Client(const std::string& socketPath) : socketPath(socketPath), clientSocket(socket(AF_UNIX, SOCK_STREAM, 0)) {}

auto Client::sendMessage(const std::string& message) -> void {
    reconnect();
    ssize_t bytesSent = write(clientSocket, message.c_str(), message.size());
    if (bytesSent < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            std::cerr << "Client: Socket is not ready for writing." << std::endl;
            // Handle the situation, e.g., retry later or return
        } else {
            throw std::runtime_error("Client: failed to send message.");
        }
    }
}

auto Client::reconnect() -> void {
    if (clientSocket >= 0) {
        close(clientSocket); // Close the existing socket if it's open
    }

    clientSocket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        throw std::runtime_error("Client: socket creation failed.");
    }

    sockaddr_un serverAddr;
    serverAddr.sun_family = AF_UNIX;
    strcpy(serverAddr.sun_path, socketPath.c_str());

    if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) < 0) {
        throw std::runtime_error("Client: connection to server failed.");
    }

    std::cout << "Client connected to server at: " << socketPath << std::endl;
}

auto Client::receiveMessage() -> std::string {
    reconnect();
    std::string incomingMessage{};
    char buffer[256];

    while (true) {
        ssize_t bytesRead = read(clientSocket, buffer, sizeof(buffer) - 1);
        if (bytesRead < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                break; // No more data available
            }
            throw std::runtime_error("Client: Error reading from client socket.");
        } else if (bytesRead == 0) {
            break; // Connection closed
        }

        incomingMessage.append(buffer, bytesRead);
    }

    return incomingMessage;
}



} // namespace irise