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
        return 1; // Exit if we can't connect
    }

    // Start the client loop
    while (true) {
        try {
            client.sendMessage(irise::Message{irise::MessageType::HELLO});
            std::cout << "Sent HELLO to server." << std::endl;
        } catch(const std::exception& e) {
            std::cout << "Error sending message. Details: " << e.what() << std::endl;
        }

        // Wait for a response
        std::string response = client.receiveMessage();
        if (!response.empty()) {
            std::cout << "Response from server: " << response << std::endl;
        } else {
            std::cerr << "No response received. The server may be down." << std::endl;
            // Here, you might implement logic to attempt to reconnect
        }
        
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Send every second
    }

    std::cout << "-------" << std::endl;
}