#include "Policies.hpp"

namespace irise {
    std::string policyToString(int policy) {
        switch (policy) {
            case iris_default:    return "default";
            case iris_cpu:        return "cpu";
            case iris_nvidia:     return "nvidia";
            case iris_amd:        return "amd";
            case iris_gpu_intel:  return "gpu intel";
            case iris_gpu:        return "gpu";
            case iris_phi:        return "phi";
            case iris_fpga:       return "fpga";
            case iris_dsp:        return "dsp";
            case iris_roundrobin: return "roundrobin";
            case iris_depend:     return "depend";
            case iris_data:       return "data";
            case iris_profile:    return "profile";
            case iris_random:     return "random";
            case iris_pending:    return "pending";
            case iris_any:        return "any";
            case iris_custom:     return "custom";
            default: break;
        }
        return policy & iris_all ? "all" : "?";
    }
}