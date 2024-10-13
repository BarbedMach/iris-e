#include "Devices.hpp"

namespace irise {
    Devices& Devices::instance() {
        static Devices instance;
        return instance;
    }

    Devices::~Devices() {
        auto unsetEnvironmentVariable = [](const std::string& name) {
            if (unsetenv(name.data()) != 0) {
                std::cerr << "!!! Error unsetting environment variable `" << name << "` !!!" << std::endl;
                return;
            }
            std::cout << "Environment variable `" << name << "` unset" << std::endl; 
        };

        for (auto i = 0; i < modelCounts[0]; ++i) {
            unsetEnvironmentVariable(std::string{"IRIS_DEVICE_CUDA_" + std::to_string(i)});
        }
        for (auto i = 0; i < modelCounts[1]; ++i) {
            unsetEnvironmentVariable(std::string{"IRIS_DEVICE_HIP_" + std::to_string(i)});
        }
        for (auto i = 0; i < modelCounts[2]; ++i) {
            unsetEnvironmentVariable(std::string{"IRIS_DEVICE_LZ_" + std::to_string(i)});
        }
        for (auto i = 0; i < modelCounts[3]; ++i) {
            unsetEnvironmentVariable(std::string{"IRIS_DEVICE_CL_" + std::to_string(i)});
        }
        for (auto i = 0; i < modelCounts[4]; ++i) {
            unsetEnvironmentVariable(std::string{"IRIS_DEVICE_MP_" + std::to_string(i)});
        }
        for (auto i = 0; i < modelCounts[5]; ++i) {
            unsetEnvironmentVariable(std::string{"IRIS_DEVICE_HEX_" + std::to_string(i)});
        }
    }

    void Devices::registerDevice(iris::rt::Device* device) {
        deviceList.push_back(device);

        auto setEnvironmentVariable = [](const std::string& name, const std::string& value) {
            if (setenv(name.data(), value.data(), 1) != 0) {
                std::cerr << "!!! Error setting environment variable `" << name << "` with the value `" << value << "` !!!" << std::endl;
                return;
            }
            std::cout << "New environment variable `" << name << "` : `" << value << "`" << std::endl;
        };
        
        auto envVarPrefix{ std::string{"IRIS_DEVICE_"} };
        std::string envVarModel{};
        std::size_t modelCountIndex{};

        switch (Device::model(device)) {
            case DevModel::CUDA: envVarModel = "CUDA_"; modelCountIndex = 0; break;
            case DevModel::HIP: envVarModel = "HIP_"; modelCountIndex = 1; break;
            case DevModel::LZ: envVarModel = "LZ_"; modelCountIndex = 2; break;
            case DevModel::CL: envVarModel = "CL_"; modelCountIndex = 3; break;
            case DevModel::MP: envVarModel = "MP_"; modelCountIndex = 4; break;
            case DevModel::HEX: envVarModel = "HEX_"; modelCountIndex = 5; break;
        }

        auto envVarName = envVarPrefix + envVarModel + std::to_string(modelCounts[modelCountIndex]);
        auto envVarValue = std::to_string(device->devno());

        setEnvironmentVariable(envVarName, envVarValue);
        modelCounts[modelCountIndex]++;
    }
}