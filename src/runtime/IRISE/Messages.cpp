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
        case PENDING_MAPPING: return "PENDING_MAPPING";
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
    if (messageTypeString == "PENDING_MAPPING") { return PENDING_MAPPING; }
    
    return UNKNOWN;
}

Message::Message(MessageType messageType) : header(messageType), body("") {}

auto Message::setMessageType(MessageType messageType) -> void {
    header = messageType;
}

auto Message::setBody(const std::string& bodyString) -> void {
    body = bodyString;
}

Message::Message(MessageType messageType, std::string body) : header(std::move(messageType)), body(std::move(body)) {}

auto Message::fromJSONString(const std::string& jsonString) -> Message {
    auto json = nlohmann::json::parse(jsonString);
    
    if (!json.contains("header") || !json.contains("body")) {
        throw std::runtime_error("Missing required fields in JSON.");
    }

    std::string header = json.at("header").get<std::string>();
    std::string body = json.at("body").get<std::string>();

    return Message{Message::toMessageType(header), body};
}

auto Message::fromJSON(const json& json) -> Message {
    Message message{};
    message.setMessageType(Message::toMessageType(json.at("header").get<std::string>()));
    message.setBody(json.at("body").get<std::string>());
    return message;
} 

auto Message::toJSON() const -> json {
    return json{
        {"header", Message::toString(header)},
        {"body", body}
    };
}

auto Message::getMessageType() const -> MessageType {
    return header;
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

    if (json.is_string()) {
        auto parsedJson = nlohmann::json::parse(json.get<std::string>());

        deviceInfo.devNo = parsedJson.at("devNo").get<int>();
        deviceInfo.platformNo = parsedJson.at("platformNo").get<int>();
        deviceInfo.vendor = parsedJson.at("vendor").get<std::string>();
        deviceInfo.name = parsedJson.at("name").get<std::string>();
        deviceInfo.type = parsedJson.at("type").get<int>();
        deviceInfo.model = parsedJson.at("model").get<int>();
    } else {
        
        deviceInfo.devNo = json.at("devNo").get<int>();
        deviceInfo.platformNo = json.at("platformNo").get<int>();
        deviceInfo.vendor = json.at("vendor").get<std::string>();
        deviceInfo.name = json.at("name").get<std::string>();
        deviceInfo.type = json.at("type").get<int>();
        deviceInfo.model = json.at("model").get<int>();
    }

    return deviceInfo;
}

Message::Message(const DeviceInfo& deviceInfo) : header(MessageType::DEV_INFO), body(deviceInfo.toJSON().dump()) {}

auto KernelInfo::toJSON() const -> json {
    return json{
        {"name", name},
        {"taskName", taskName}
    };
}

auto KernelInfo::fromJSON(const json& json) -> KernelInfo {
    KernelInfo kernelInfo;

    if (json.is_string()) {
        auto parsedJson = nlohmann::json::parse(json.get<std::string>());

        kernelInfo.name = parsedJson.at("name").get<std::string>();
        kernelInfo.taskName = parsedJson.at("taskName").get<std::string>();
    } else {

        kernelInfo.name = json.at("name").get<std::string>();
        kernelInfo.taskName = json.at("taskName").get<std::string>();
    }

    return kernelInfo;
}

Message::Message(const KernelInfo& KernelInfo) : header(MessageType::KERNEL_INFO), body(KernelInfo.toJSON().dump()) {}

auto KernelDeviceMapping::toJSON() const -> json {
    return json{
        {"device", device.toJSON()},
        {"kernel", kernel.toJSON()}
    };
}

auto KernelDeviceMapping::fromJSON(const json& jsonInput) -> KernelDeviceMapping {
    KernelDeviceMapping mapping;
    json parsedJson;

    if (jsonInput.is_string()) {
        parsedJson = nlohmann::json::parse(jsonInput.get<std::string>());
    } else {
        parsedJson = jsonInput;
    }

    mapping.device = DeviceInfo::fromJSON(parsedJson.at("device"));
    mapping.kernel = KernelInfo::fromJSON(parsedJson.at("kernel"));

    return mapping;
}

Message::Message(const KernelDeviceMapping& mapping) : header(MessageType::KERNEL_DEVICE_MAP), body(mapping.toJSON().dump()) {}

auto PendingMapping::toJSON() const -> json {
    return json{
        {"kernel", kernel.toJSON()}
    };
}

auto PendingMapping::fromJSON(const json& jsonInput) -> PendingMapping {
    PendingMapping pendingMapping;
    json parsedJson;

    if (jsonInput.is_string()) {
        parsedJson = json::parse(jsonInput.get<std::string>());
    } else {
        parsedJson = jsonInput;
    }

    pendingMapping.kernel = KernelInfo::fromJSON(parsedJson.at("kernel"));

    return pendingMapping;
}

Message::Message(const PendingMapping& pendingMapping) : header(MessageType::PENDING_MAPPING), body(pendingMapping.toJSON().dump()) {}

} // namespace irise