#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "Client.hpp"

auto main() -> int {
    std::cout << "Enter socket path: ";
    std::string socketPath;

    std::cin >> socketPath;

    auto client{irise::Client{socketPath}};

    client.sendMessage(irise::Message{irise::MessageType::HELLO});
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << client.receiveMessage() << std::endl;

    std::cout << "-------" << std::endl;
}