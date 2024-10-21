#include "PolicyClient.hpp"

#include "Task.h"

namespace iris::rt {

PolicyClient::PolicyClient(Scheduler* scheduler, Policies* policies) : policies(policies) {
    SetScheduler(scheduler);
}

PolicyClient::~PolicyClient() {}

auto PolicyClient::GetDevices(Task* task, Device** devs, int* ndevs) -> void {
    auto taskName{ std::string{task->name()} };
    
    auto& kernels = irise::Scheduler::instance().getKernels();

    if (auto it = std::ranges::find(kernels, taskName, &irise::KernelInfo::taskName); it != kernels.end()) {
        irise::Server::instance().sendMappingForKernelPending(irise::PendingMapping{ *it }).waitForACK();

        auto& deviceToUse = irise::Scheduler::instance().getMapping()[*it];
        devs[0] = devs[deviceToUse.devNo];
        *ndevs = 1;
    } else {
        return policies->GetPolicy(iris_default, NULL)->GetDevices(task, devs, ndevs);
    }
}

} // namespace iris::rt