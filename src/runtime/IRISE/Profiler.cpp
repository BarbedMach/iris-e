#include "Profiler.hpp"

namespace irise {
    Profiler::~Profiler() = default;
    
    Profiler& Profiler::instance() {
        static Profiler instance;
        return instance;
    }

    void Profiler::setPlatform(iris::rt::Platform* platform_) {
        platform = platform_;
    } 
}