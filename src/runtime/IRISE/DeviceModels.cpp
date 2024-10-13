#include "DeviceModels.hpp"

namespace irise::Device {
    DevModel model(iris::rt::Device *device) {
        switch(device->model()) {
            case iris_cuda: return DevModel::CUDA;
            case iris_hip: return DevModel::HIP;
            case iris_levelzero: return DevModel::LZ;
            case iris_opencl: return DevModel::CL;
            case iris_openmp: return DevModel::MP;
            case iris_hexagon: return DevModel::HEX;
        }
    }
}