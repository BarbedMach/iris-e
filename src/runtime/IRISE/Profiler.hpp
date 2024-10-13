#pragma once

#include "../Platform.h"
#include "../Task.h"
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

        private:
            Profiler() = default;

            iris::rt::Platform* platform = nullptr;
            std::vector<CommandProfile> commandProfiles{};
    };
}