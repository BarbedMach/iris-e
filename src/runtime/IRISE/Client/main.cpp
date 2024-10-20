#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "Client.hpp"

auto main() -> int {
    std::cout << "Enter socket path: ";
    std::string socketPath;
    std::cin >> socketPath;

    auto client{ irise::Client{socketPath} };

    try {
        client.connect();
    } catch(const std::exception& e) {
        std::cerr << "Error connecting to server. Details: " << e.what() << std::endl;
        return 1;
    }

    bool helloAcknowledged = false;

    while (true) {
        try {
            // Initial state: Start or Connected
            if (client.getState() == irise::ClientState::Start || client.getState() == irise::ClientState::Connected) {
                client.sendMessage(irise::Message{irise::MessageType::HELLO});
                std::cout << "Sent HELLO to server." << std::endl;
                client.setState(irise::ClientState::Connected);
            }

            // Receive response from server
            std::string response = client.receiveMessage();
            if (!response.empty()) {
                std::cout << "Response from server: " << response << std::endl;

                // Update client state based on server response
                auto serverMessage = irise::Message::fromJSONString(response);

                switch (serverMessage.getMessageType()) {
                    case irise::MessageType::HELLO_ACK:
                        std::cout << "Received HELLO_ACK from server." << std::endl;
                        client.setState(irise::ClientState::Ready);
                        helloAcknowledged = true;
                        break;

                    case irise::MessageType::UNKNOWN:
                        std::cerr << "Server sent UNKNOWN message type." << std::endl;
                        break;

                    case irise::MessageType::ACK:
                        std::cout << "Received ACK from server." << std::endl;
                        break;

                    default:
                        std::cerr << "Unhandled message type from server." << std::endl;
                        break;
                }
            } else {
                std::cerr << "No response received. The server may be down." << std::endl;
            }

            // Based on state, transition to other tasks (e.g., sending device info)
            if (helloAcknowledged && client.getState() == irise::ClientState::Ready) {
                // Client is now ready to send other messages, such as DeviceInfo
                irise::DeviceInfo deviceInfo{/* populate with actual data */};
                client.sendDeviceInfo(deviceInfo);
                client.setState(irise::ClientState::DeviceInfo);
            }

        } catch(const std::exception& e) {
            std::cerr << "Error during communication. Details: " << e.what() << std::endl;
        }

        // Sleep to avoid flooding the server with messages
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "-------" << std::endl;
}