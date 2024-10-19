#include <iostream>
#include "Client.hpp"

auto main() -> int {
    auto client{irise::Client{"tmp/irise_socket"}};

    client.sendMessage(irise::Message{irise::MessageType::HELLO});

    std::cout << client.receiveMessage() << std::endl;

    std::cout << "-------" << std::endl;
}