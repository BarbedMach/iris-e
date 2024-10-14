#include "../Command.h"
#include "Profiler.hpp"

namespace irise {
    Profiler& Profiler::instance() {
        static Profiler instance;
        return instance;
    }

    void Profiler::profileCommand(iris::rt::Command* command) {
        auto commandProfile{ CommandProfile{command} };
        commandProfile.profile();
        auto result = commandProfiles.insert(commandProfile);
        if (result.second) {
            std::cout << commandProfile;
        }
    }
}