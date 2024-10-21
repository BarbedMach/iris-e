#include "Client.hpp"

namespace irise {

Client::Client(const std::string& socketPath) : socketPath(socketPath), clientSocket(socket(AF_UNIX, SOCK_STREAM, 0)) {}

auto Client::connect() -> void {
    clientSocket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        throw std::runtime_error("Client: socket creation failed.");
    }

    sockaddr_un serverAddr;
    serverAddr.sun_family = AF_UNIX;
    strcpy(serverAddr.sun_path, socketPath.c_str());

    if (::connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) < 0) {
        throw std::runtime_error("Client: connection to server failed.");
    }

    std::cout << "Client connected to server at: " << socketPath << std::endl;

    state = ClientState::Connected;
}

auto Client::sendMessage(const std::string& message) -> void {
    ssize_t bytesSent = write(clientSocket, message.c_str(), message.size());
    if (bytesSent < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            std::cerr << "Client: Socket is not ready for writing." << std::endl;
        } else {
            throw std::runtime_error("Client: failed to send message.");
        }
    }
}

auto Client::receiveMessage() -> std::string {
    std::string incomingMessage{};
    char buffer[256];

    ssize_t bytesRead = read(clientSocket, buffer, sizeof(buffer) - 1);
    if (bytesRead < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return incomingMessage;
        }
        throw std::runtime_error("Client: Error reading from client socket.");
    } else if (bytesRead == 0) {
        std::cerr << "Client: Connection closed by server." << std::endl;
        return incomingMessage;
    }

    incomingMessage.append(buffer, bytesRead);
    return incomingMessage;
}

auto Client::getState() -> ClientState {
    return state;
}

auto Client::setState(ClientState nextState) -> void {
    state = nextState;
}

auto Client::sendACK() -> void {
    sendMessage(Message{MessageType::ACK});
}

auto Client::handleMessage(const std::string& response) -> void {
    auto serverMessage = irise::Message::fromJSONString(response);

    switch (serverMessage.getMessageType()) {
        case MessageType::HELLO_ACK:
            std::cout << "Received HELLO_ACK from server." << std::endl;
            setState(ClientState::Ready);
            break;

        case MessageType::DEV_INFO: {
            std::cout << "Received Device Info from server." << std::endl;

            // Deserialize device info from JSON and append it to the vector
            DeviceInfo deviceInfo = DeviceInfo::fromJSON(serverMessage.getBody());
            devices.push_back(deviceInfo);

            // Set the state to DeviceInfo
            setState(ClientState::DeviceInfo);
            
            // Send ACK back to the server
            sendACK();
            std::cout << "ACK sent back to server." << std::endl;
            break;
        }

        case MessageType::KERNEL_INFO: {
            std::cout << "Received Device Info from server." << std::endl;

            KernelInfo kernelInfo = KernelInfo::fromJSON(serverMessage.getBody());
            kernels.push_back(kernelInfo);

            setState(ClientState::KernelInfo);

            sendACK();
            std::cout << "ACK sent back to server." << std::endl;
            break;
        }
        case MessageType::ACK: {
            std::cout << "ACK received from server." << std::endl;
            break;
        }

        default:
            std::cerr << "Unhandled message type from server." << std::endl;
            break;
    }
}

auto Client::mapKernelsToDevicesRandomly() -> std::vector<KernelDeviceMapping> {
    std::vector<KernelDeviceMapping> mappings;

    auto kernelsCopy = kernels;
    auto devicesCopy = devices;

    std::shuffle(devicesCopy.begin(), devicesCopy.end(), std::mt19937{ std::random_device{}() });

    for (auto i = 0; i < kernelsCopy.size(); ++i) {
        auto mapping{ KernelDeviceMapping{ devicesCopy[i], kernelsCopy[i] } };
        mappings.push_back(mapping);
    }

    return mappings;
}

} // namespace irise
