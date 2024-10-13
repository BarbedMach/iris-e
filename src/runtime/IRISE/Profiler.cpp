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

    void Profiler::profileCommand(iris::rt::Command* command) {
        auto commandProfile{ CommandProfile{command} };
        commandProfile.profile();

        commandProfiles.push_back(commandProfile);
    }
}