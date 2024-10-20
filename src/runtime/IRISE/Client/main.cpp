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

    // Start the client loop
    while (true) {
        // Attempt to reconnect before each message send
        // Send a message to the server (e.g., HELLO)
        try {
            client.sendMessage(irise::Message{irise::MessageType::HELLO});
        } catch(const std::exception& e) {
            std::cout << "Error sending message. Details: " << e.what() << std::endl;
        }
        

        // Wait for a response in a loop
        while (true) {
            try {
                auto response = client.receiveMessage();
                if (!response.empty()) {
                    std::cout << "Response from server: " << response << std::endl;
                    break; // Exit the inner loop if we received a message
                }
            } catch(const std::exception& e) {
                std::cout << "Error receiving message. Details: " << e.what() << std::endl;
            }
            
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Wait before trying again
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    std::cout << "-------" << std::endl;
}