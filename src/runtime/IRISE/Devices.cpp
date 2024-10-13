#include "Devices.hpp"

namespace irise {
    Devices& Devices::instance() {
        static Devices instance;
        return instance;
    }

    void Devices::registerDevice(iris::rt::Device* device) {
        deviceList.push_back(device);
    }
}