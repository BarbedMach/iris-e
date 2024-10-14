#include "Policies.hpp"

namespace irise {
    // Refer to iris/rt/iris_runtime.h. I inlined them to save an #include that was giving me issues. F this code base.
    std::string policyToString(int policy) {
        switch (policy) {
            case (1 << 5):    return "default";
            case (1 << 6):        return "cpu";
            case (1 << 7):     return "nvidia";
            case (1 << 8):        return "amd";
            case (1 << 9):  return "gpu intel";
            case ((1 << 7) | (1 << 8) | (1 << 9)):        return "gpu";
            case (1 << 10):        return "phi";
            case (1 << 11):       return "fpga";
            case ((1 << 12)):        return "dsp";
            case (1 << 18): return "roundrobin";
            case (1 << 19):     return "depend";
            case (1 << 20):       return "data";
            case (1 << 21):    return "profile";
            case (1 << 22):     return "random";
            case (1 << 23):    return "pending";
            case (1 << 24):        return "any";
            case (1 << 27):     return "custom";
            default: break;
        }
        return policy & (1 << 25) ? "all" : "?";
    }
}