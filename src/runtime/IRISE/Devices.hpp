#pragma once

#include <stdlib.h>
#include <vector>
#include <cstddef>
#include <string>
#include <iostream>
#include "../Device.h"
#include "DeviceModels.hpp"

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
}