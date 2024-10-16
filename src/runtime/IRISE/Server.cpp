#include "Server.hpp"

namespace irise {
    Server& Server::instance() {
        static Server instance;
        return instance;
    }

    void Server::sendResultMsg(const Message::Result& res) {
        Message::sendMessage(MessageQueue::getMsgid(), res, Message::Type::Result);
    }

    void Server::sendDeviceInfoMsg(const Message::DeviceInfo& devInfo) {
        sendMessage(MessageQueue::getMsgid(), devInfo, Message::Type::DeviceInfo);
    }

    void Server::sendKernelInfoMsg(const Message::KernelInfo& kernelInfo) {
        sendMessage(MessageQueue::getMsgid(), kernelInfo, Message::Type::KernelInfo);
    }
}