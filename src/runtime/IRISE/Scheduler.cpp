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

} // namespace irise