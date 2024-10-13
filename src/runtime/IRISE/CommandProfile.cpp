#include "CommandProfile.hpp"
#include "../Device.h"
#include "../Command.h"
#include "../Task.h"

namespace irise {
    CommandProfile::CommandProfile(iris::rt::Command* command) : command(command) {
        profile();
    }

    CommandProfile::~CommandProfile() = default;

    void CommandProfile::profile() {
        auto timeToTimePoint = [](double time_in_nanoseconds) {
            auto time = nanoseconds{static_cast<std::size_t>(time_in_nanoseconds)};
            return time_point<system_clock, system_clock::duration>(time);
        };

        cmdName = command->name();
        cmdType = command->type_name();
        startTime = timeToTimePoint(command->time_start());
        endTime = timeToTimePoint(command->time_end());
        duration = duration_cast<nanoseconds>(endTime - startTime);
        workSize = (command->type_kernel()) ? command->ws() : command->size();
        cmdPolicy = policyToString(command->task()->brs_policy());
        deviceName = command->task()->dev()->name();
        deviceId = command->task()->dev()->devno();

        std::cout << "Command Profile\n"
        << "Name: " << cmdName << " Type: " << cmdType << " WorkSize: " << workSize << " Duration: " << std::to_string(duration.count()) << "ns Device: " << deviceName << " : " << deviceId << " Policy: " << cmdPolicy << std::endl;
    }
}