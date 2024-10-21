#include "Scheduler.hpp"

namespace irise {

auto Scheduler::instance() -> Scheduler& {
    static Scheduler instance;
    return instance;
}

auto Scheduler::registerDevice(const DeviceInfo& deviceInfo) -> void {
    devices.push_back(deviceInfo);
}

auto Scheduler::registerKernel(const KernelInfo& kernelInfo) -> void {
    kernels.push_back(kernelInfo);
}

auto Scheduler::getDevices() -> std::vector<DeviceInfo>& {
    return const_cast<std::vector<DeviceInfo>&>(static_cast<const Scheduler&>(*this).getDevices());
}

auto Scheduler::getDevices() const -> const std::vector<DeviceInfo>& {
    return devices;
}

auto Scheduler::getKernels() const -> const std::vector<KernelInfo>& {
    return kernels;
}

auto Scheduler::getKernels() -> std::vector<KernelInfo>& {
    return const_cast<std::vector<KernelInfo>&>(static_cast<const Scheduler&>(*this).getKernels());
}

auto Scheduler::getMapping() const -> const std::map<KernelInfo, DeviceInfo>& {
    return kernelToDeviceMap;
}

auto Scheduler::getMapping() -> std::map<KernelInfo, DeviceInfo>& {
    return const_cast<std::map<KernelInfo, DeviceInfo>&>(static_cast<const Scheduler&>(*this).getMapping());
}

auto Scheduler::setMapping(const Message& message) -> void {
    if (message.getMessageType() != MessageType::KERNEL_DEVICE_MAP) {
        std::cerr << "IRISE::Scheduler: Incoming message 'msg' to setMapping(msg) is not a mapping message!" << std::endl;
        return;
    }

    auto kernelDeviceMapping = KernelDeviceMapping::fromJSON(message.getBody());

    kernelToDeviceMap[kernelDeviceMapping.kernel] = kernelDeviceMapping.device;
}

} // namespace irise