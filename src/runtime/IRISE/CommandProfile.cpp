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
        cmdName = command->name();
        cmdType = command->type_name();
        startTime = command->time_start();
        endTime = command->time_end();
        duration = endTime - startTime;
        workSize = (command->type_kernel()) ? command->ws() : command->size();
        cmdPolicy = policyToString(command->task()->brs_policy());
        deviceName = command->task()->dev()->name();
        deviceId = command->task()->dev()->devno();

        std::cout << "Command Profile\n"
        << "Name: " << cmdName << " Type: " << cmdType << " WorkSize: " << workSize << " Duration: " << duration << "µs Device: " << deviceName << " : " << deviceId << " Policy: " << cmdPolicy << std::endl;
    }
}