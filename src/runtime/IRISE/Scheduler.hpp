#pragma once

namespace irise {

class Scheduler {
    public:
        Scheduler(const Scheduler&) = delete;
        Scheduler& operator==(const Scheduler&) = delete;

        static auto instance() -> Scheduler&;

           

    private:
        Scheduler() = default;
};

} // namepsace irise