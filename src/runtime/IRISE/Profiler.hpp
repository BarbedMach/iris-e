#pragma once

#include "../Platform.h"
#include "../Command.h"
#include "CommandProfile.hpp"
#include <string>
#include <vector>

namespace irise {
    class Profiler {
        public:
            Profiler(const Profiler&) = delete;
            Profiler& operator=(const Profiler&) = delete;
            
            static Profiler& instance();
            void setPlatform(iris::rt::Platform* platform);

            void profileCommand(iris::rt::Command* command);

        private:
            Profiler() = default;

            iris::rt::Platform* platform = nullptr;
            std::vector<CommandProfile> commandProfiles{};
    };
}