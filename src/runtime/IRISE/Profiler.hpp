#pragma once

#include "CommandProfile.hpp"
#include <iostream>
#include <string>
#include <set>

namespace iris::rt {
    class Command;
}

namespace irise {
    class Profiler {
        public:
            Profiler(const Profiler&) = delete;
            Profiler& operator=(const Profiler&) = delete;
            
            static Profiler& instance();

            void profileCommand(iris::rt::Command* command);

        private:
            Profiler() = default;

            std::set<CommandProfile> commandProfiles{};
    };
}