#pragma once

#include "Policy.h"
#include "Scheduler.h"
#include "IRISE/Scheduler.hpp"

namespace iris::rt {

class PolicyClient : public Policy {
    public:
        PolicyClient(Scheduler* scheduler);
        virtual ~PolicyClient();

        virtual auto GetDevices(Task* task, Device** devs, int* ndevs) -> void;
};

} // namespace iris::rt
