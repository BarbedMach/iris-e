#pragma once

#include <vector>
#include "../Device.h"
#include "../Debug.h"

namespace irise {
    class Devices {
        public:
            Devices(const Devices&) = delete;
            Devices& operator=(const Devices&) = delete;

            static Devices& instance();

            void registerDevice(iris::rt::Device* device);
        private:
            Devices() = default;
            
            std::vector<iris::rt::Device*> deviceList{};
    };
}