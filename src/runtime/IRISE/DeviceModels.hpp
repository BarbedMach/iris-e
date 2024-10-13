#pragma once

#include "../Device.h"

namespace irise {
    enum class DevModel {
        CUDA,
        HIP,
        LZ,
        CL,
        MP,
        HEX
    };

    namespace Device {
        DevModel model(iris::rt::Device* device);
    }
}