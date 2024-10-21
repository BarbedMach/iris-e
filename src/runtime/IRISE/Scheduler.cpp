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

} // namespace irise