#include <iostream>
#include <string>
#include "Client.hpp"

auto main() -> int {
    std::cout << "Enter socket path: ";
    std::string socketPath;

    std::cin >> socketPath;

    auto client{irise::Client{socketPath}};

    client.sendMessage(irise::Message{irise::MessageType::HELLO});

    std::cout << client.receiveMessage() << std::endl;

    std::cout << "-------" << std::endl;
}