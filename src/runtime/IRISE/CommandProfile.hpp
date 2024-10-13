#pragma once

#include <string>
#include <chrono>
#include <cstddef>
#include "Policies.hpp"

namespace iris::rt {
    class Command;
    class Task;
    class Device;
}

namespace irise {
    using namespace std::chrono;
    class CommandProfile {
        public:
            CommandProfile(iris::rt::Command* command);
            ~CommandProfile();

            void profile();
        private:
            iris::rt::Command* command = nullptr;
            
            std::string cmdName{};
            std::string cmdType{};
            time_point<system_clock, nanoseconds> startTime{};
            time_point<system_clock, nanoseconds> endTime{};
            nanoseconds duration{};
            std::size_t workSize{};
            std::string cmdPolicy{};
            std::string deviceName{};
            std::size_t deviceId{};
    };
}