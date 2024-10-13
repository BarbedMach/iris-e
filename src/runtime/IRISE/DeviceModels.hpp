#pragma once

namespace iris::rt {
    class Device;
}

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