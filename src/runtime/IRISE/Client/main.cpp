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
        std::cerr << "Error connecting to client. Details: " << e.what() << std::endl;
        return 1;
    }

    while (true) {
        try {
            if (client.getState() == irise::ClientState::Start || client.getState() == irise::ClientState::Connected) {
                client.sendMessage(irise::Message{irise::MessageType::HELLO});
                std::cout << "Sent HELLO to server." << std::endl;
            }

            // Receive response from server
            std::string response = client.receiveMessage();
            if (!response.empty()) {
                std::cout << "Response from server: " << response << std::endl;
                client.handleMessage(response);
            } else {
                std::cerr << "No response received. The server may be down." << std::endl;
            }

        } catch(const std::exception& e) {
            std::cerr << "Error during communication. Details: " << e.what() << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "-------" << std::endl;
}