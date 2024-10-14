#pragma once

#include <string>
#include <cstddef>
#include <iostream>
#include "Policies.hpp"

namespace iris::rt {
    class Command;
    class Task;
    class Device;
}

namespace irise {
    class CommandProfile {
        public:
            CommandProfile(iris::rt::Command* command);
            ~CommandProfile();

            void profile();

            bool operator==(const CommandProfile& other) const;
            bool operator<(const CommandProfile& other) const;

            friend std::ostream& operator<<(std::ostream& os, const CommandProfile& cmdProfile);
        private:
            iris::rt::Command* command = nullptr;
            
            std::string cmdName{};
            std::string cmdType{};
            double startTime{};
            double endTime{};
            double duration{};
            std::size_t workSize{};
            std::string cmdPolicy{};
            std::string deviceName{};
            std::size_t deviceId{};
    };
}