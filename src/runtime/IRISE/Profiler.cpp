#include "Profiler.hpp"

namespace irise {
    Profiler::Profiler(iris::rt::Platform* platform) : platform(platform) {}
    Profiler::~Profiler() = default;

    void Profiler::profileCompletedTask(iris::rt::Task* task) {

    }
}