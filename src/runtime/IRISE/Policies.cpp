#include "Policies.hpp"

#define iris_default            (1 << 5)
#define iris_cpu                (1 << 6)
#define iris_nvidia             (1 << 7)
#define iris_amd                (1 << 8)
#define iris_gpu_intel          (1 << 9)
#define iris_gpu                (iris_nvidia | iris_amd | iris_gpu_intel)
#define iris_phi                (1 << 10)
#define iris_fpga               (1 << 11)
#define iris_hexagon            (1 << 12)
#define iris_dsp                (iris_hexagon)
#define iris_roundrobin         (1 << 18)
#define iris_depend             (1 << 19)
#define iris_data               (1 << 20)
#define iris_profile            (1 << 21)
#define iris_random             (1 << 22)
#define iris_pending            (1 << 23)
#define iris_any                (1 << 24)
#define iris_all                (1 << 25)
#define iris_ocl                (1 << 26)
#define iris_custom             (1 << 27)

namespace irise {
    
// Refer to iris/rt/iris_runtime.h. I inlined them to save an #include that was giving me issues. F this code base.
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

} // namepsace irise