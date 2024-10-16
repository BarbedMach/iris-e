#pragma once

#include <string>
#include "sys/ipc.h"
#include "sys/msg.h"
#include "Message.hpp"
#include "MessageQueue.hpp"

namespace irise {
    class Server : public MessageQueue {
        public:
            Server(const Server&) = delete;
            Server& operator==(const Server&) = delete;

            static Server& instance();

            void sendDeviceInfoMsg(const Message::DeviceInfo& devInfo);
            void sendResultMsg(const Message::Result& res);
            void sendKernelInfoMsg(const Message::KernelInfo& kernelInfo);
        private:
            Server() = default;
            friend MessageQueue;
    };
}