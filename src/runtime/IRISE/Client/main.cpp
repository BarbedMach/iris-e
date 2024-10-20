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
        client.sendMessage(irise::Message{irise::MessageType::HELLO});

        // Wait for a response in a loop
        while (true) {
            auto response = client.receiveMessage();
            if (!response.empty()) {
                std::cout << "Response from server: " << response << std::endl;
                break; // Exit the inner loop if we received a message
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Wait before trying again
        }

        // Optional: Add a delay before sending the next message
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "-------" << std::endl;
}