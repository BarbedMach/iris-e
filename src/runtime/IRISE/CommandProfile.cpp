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
    }

    bool CommandProfile::operator==(const CommandProfile& other) const {
        return cmdName == other.cmdName && cmdType == other.cmdType;
    }

    bool CommandProfile::operator<(const CommandProfile& other) const {
        if (cmdName != other.cmdName) {
            return cmdName < other.cmdName;
        }
        return cmdType < other.cmdType;
    }
    
    std::ostream &operator<<(std::ostream &os, const CommandProfile &cmdP) {
        std::cout << "Command Profile\n"
        << "Name: " << cmdP.cmdName << " Type: " << cmdP.cmdType << " WorkSize: " << cmdP.workSize 
        << " Duration: " << cmdP.duration << "µs Device: " << cmdP.deviceName << " : " 
        << cmdP.deviceId << " Policy: " << cmdP.cmdPolicy << std::endl;
        return std::cout;
    }
}