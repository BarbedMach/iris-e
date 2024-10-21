#pragma once

#include "Policy.h"
#include "Scheduler.h"
#include "IRISE/Server.hpp"
#include "IRISE/Scheduler.hpp"
#include <string>

namespace iris::rt {

class PolicyClient : public Policy {
    public:
        PolicyClient(Scheduler* scheduler);
        virtual ~PolicyClient();

        virtual auto GetDevices(Task* task, Device** devs, int* ndevs) -> void;
};

} // namespace iris::rt
