#pragma once

#include <string>
#include <vector>
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
    std::string name;
    std::string taskName;
    std::vector<int> devices;

    auto toJSON() const -> json;
    static auto fromJSON(const json& json) -> KernelInfo;
};


class Message {
    public:
        Message() = default;

        Message(MessageType messageType);
        Message(const DeviceInfo& deviceInfo);
        Message(const KernelInfo& KernelInfo);

        Message(MessageType messageType, std::string body);

        static auto toString(MessageType messageType) -> std::string;
        static auto toMessageType(const std::string& messageTypeString) -> MessageType;

        auto setMessageType(MessageType messageType) -> void;
        auto setBody(const std::string& bodyString) -> void;

        static auto fromJSONString(const std::string& jsonString) -> Message;
        static auto fromJSON(const json& json) -> Message;
        auto toJSON() const -> json;

        auto getMessageType() const -> MessageType;
        auto getBody() const -> std::string;

        operator std::string() const;

    private:
        MessageType header{};
        std::string body{};
};


} // namespace irise