#pragma once

#include <vector>
#include "Messages.hpp"

namespace irise {

class Scheduler {
    public:
        Scheduler(const Scheduler&) = delete;
        Scheduler& operator==(const Scheduler&) = delete;

        static auto instance() -> Scheduler&;

        auto registerDevice(const DeviceInfo& deviceInfo) -> void;
        auto registerKernel(const KernelInfo& kernelInfo) -> void;

        auto getDevices() -> std::vector<DeviceInfo>&;
        auto getDevices() const ->  const std::vector<DeviceInfo>&;

        auto getKernels() -> std::vector<KernelInfo>&;
        auto getKernels() const -> const std::vector<KernelInfo>&;

    private:
        Scheduler() = default;

        std::vector<DeviceInfo> devices;
        std::vector<KernelInfo> kernels;
};

} // namepsace irise