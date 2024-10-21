#pragma once

#include "Policies.h"
#include "Policy.h"
#include "Scheduler.h"
#include "IRISE/Server.hpp"
#include "IRISE/Scheduler.hpp"
#include <string>
#include <ranges>

namespace iris::rt {

class PolicyClient : public Policy {
    public:
        PolicyClient(Scheduler* scheduler, Policies* policies);
        virtual ~PolicyClient();

        virtual auto GetDevices(Task* task, Device** devs, int* ndevs) -> void;

    private:
        Policies* policies;
};

} // namespace iris::rt
