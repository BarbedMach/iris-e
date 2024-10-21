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

    private:
        Scheduler() = default;

        std::vector<DeviceInfo> devices;
        std::vector<KernelInfo> kernels;
};

} // namepsace irise