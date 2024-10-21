#include "PolicyClient.hpp"

#include "Task.h"

namespace iris::rt {

PolicyClient::PolicyClient(Scheduler* scheduler) {
    SetScheduler(scheduler);
}

PolicyClient::~PolicyClient() {}

auto PolicyClient::GetDevices(Task* task, Device** devs, int* ndevs) -> void {
    
}

} // namespace iris::rt