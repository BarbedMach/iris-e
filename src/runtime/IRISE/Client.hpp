#pragma once

#include <sys/ipc.h>
#include <sys/msg.h>
#include "MessageQueue.hpp"
#include "Message.hpp"

namespace irise {
    class Client : public MessageQueue {
        public:
            Client(const Client&) = delete;
            Client& operator==(const Client&) = delete;

            static Client& instance();
        private:
            Client() = default;
            friend MessageQueue;
    };
}