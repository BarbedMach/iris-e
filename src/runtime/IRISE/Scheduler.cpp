#include "Scheduler.hpp"

namespace irise {

auto Scheduler::instance() -> Scheduler& {
    static Scheduler instance;
    return instance;
}

} // namespace irise