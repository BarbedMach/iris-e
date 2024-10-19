#pragma once

#include <string>
#include "json.hpp"

namespace irise {

using json = nlohmann::json;    

enum class MessageType {
    UNKNOWN,
    ACK,
    HELLO,
    HELLO_ACK,
    DEV_INFO,
    KERNEL_INFO,
    KERNEL_DEVICE_MAP,
    KERNEL_DEVICE_PROFILING_RES
};

class Message {
    public:
        Message() = default;

        Message(const DeviceInfo& deviceInfo);

        static auto toString(MessageType messageType) -> std::string;
        static auto toMessageType(const std::string& messageTypeString) -> MessageType;

        auto setMessageType(MessageType messageType) -> void;
        auto setBody(const std::string& bodyString) -> void;

        static auto fromJSON(const json& json) -> Message;
        auto toJSON() const -> json;

        auto getMessageType() const -> MessageType;
        auto getBody() const -> std::string;

    private:
        MessageType messageType{};
        std::string body{};
};

struct DeviceInfo {
    int devNo;
    int platformNo;
    std::string vendor;
    std::string name;
    int type;
    int model;

    auto toJSON() const -> json;
    static auto fromJSON(const json& json) -> DeviceInfo;
};

struct KernelInfo {

};



} // namespace irise