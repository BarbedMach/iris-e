#include "Messages.hpp"

namespace irise {

auto Message::toString(MessageType messageType) -> std::string {
    switch(messageType) {
        using enum MessageType;
        case ACK: return "ACK";
        case HELLO: return "HELLO";
        case HELLO_ACK: return "HELLO_ACK";
        case UNKNOWN: return "UNKNOWN";
        case KERNEL_DEVICE_MAP: return "KERNEL_DEVICE_MAP";
        case KERNEL_DEVICE_PROFILING_RES: return "KERNEL_DEVICE_PROFILING_RES";
        case DEV_INFO: return "DEV_INFO";
        case KERNEL_INFO: return "KERNEL_INFO";
        default: return "UNKNOWN";
    }
}

auto Message::toMessageType(const std::string& messageTypeString) -> MessageType {
    using enum MessageType;
    if (messageTypeString == "ACK") { return ACK; }
    if (messageTypeString == "HELLO") { return HELLO; }
    if (messageTypeString == "HELLO_ACK") { return HELLO_ACK; }
    if (messageTypeString == "UNKNOWN") { return UNKNOWN; }
    if (messageTypeString == "KERNEL_DEVICE_MAP") { return KERNEL_DEVICE_MAP; }
    if (messageTypeString == "KERNEL_DEVICE_PROFILING_RES") { return KERNEL_DEVICE_PROFILING_RES; }
    if (messageTypeString == "DEV_INFO") { return DEV_INFO; }
    if (messageTypeString == "KERNEL_INFO") { return KERNEL_INFO; }
    
    return UNKNOWN;
}

Message::Message(MessageType messageType) : messageType(messageType), body("") {}

auto Message::setMessageType(MessageType messageType) -> void {
    this->messageType = messageType;
}

auto Message::setBody(const std::string& bodyString) -> void {
    body = bodyString;
}

auto Message::fromJSON(const json& json) -> Message {
    Message message{};
    message.setMessageType(Message::toMessageType(json.at("header").get<std::string>()));
    message.setBody(json.at("body").get<std::string>());
    return message;
} 

auto Message::toJSON() const -> json {
    return json{
        {"header", Message::toString(messageType)},
        {"body", body}
    };
}

auto Message::getMessageType() const -> MessageType {
    return messageType;
}

auto Message::getBody() const -> std::string {
    return body;
}

Message::operator std::string() const {
    return toJSON().dump();
}

auto DeviceInfo::toJSON() const -> json {
    return json{
            {"devNo", devNo},
            {"platformNo", platformNo},
            {"vendor", vendor},
            {"name", name},
            {"type", type},
            {"model", model}
        };
}

auto DeviceInfo::fromJSON(const json& json) -> DeviceInfo {
    DeviceInfo deviceInfo;

    deviceInfo.devNo = json.at("devNo").get<int>();
    deviceInfo.platformNo = json.at("platformNo").get<int>();
    deviceInfo.vendor = json.at("vendor").get<std::string>();
    deviceInfo.name = json.at("name").get<std::string>();
    deviceInfo.type = json.at("type").get<int>();
    deviceInfo.model = json.at("model").get<int>();

    return deviceInfo;
}

Message::Message(const DeviceInfo& deviceInfo) : messageType(MessageType::DEV_INFO), body(deviceInfo.toJSON().dump()) {}

auto KernelInfo::toJSON() const -> json {
    return json{
        {"name", name},
        {"taskName", taskName},
        {"devices", devices}
    };
}

auto KernelInfo::fromJSON(const json& json) -> KernelInfo {
    KernelInfo kernelInfo;
    
    kernelInfo.name = json.at("name").get<std::string>();
    kernelInfo.taskName = json.at("taskName").get<std::string>();
    kernelInfo.devices = json.at("devices").get<std::vector<int>>();

    return kernelInfo;
}

Message::Message(const KernelInfo& KernelInfo) : messageType(MessageType::KERNEL_INFO), body(KernelInfo.toJSON().dump()) {}

} // namespace irise