#pragma once

#include <stdlib.h>
#include <vector>
#include <cstddef>
#include <string>
#include <iostream>
#include "DeviceModels.hpp"

namespace iris::rt {
    class Device;
} // namepsace iris::rt

#define iris_cuda               1
#define iris_hip                3
#define iris_levelzero          4
#define iris_opencl             5
#define iris_openmp             6

namespace irise {

class Devices {
    public:
        Devices(const Devices&) = delete;
        Devices& operator=(const Devices&) = delete;
        virtual ~Devices();
        static Devices& instance();
        void registerDevice(iris::rt::Device* device);
        
    private:
        Devices() = default;
        
        std::vector<iris::rt::Device*> deviceList{};
        std::size_t modelCounts[6] = {0, 0, 0, 0, 0, 0};
};

} // namepsace irise