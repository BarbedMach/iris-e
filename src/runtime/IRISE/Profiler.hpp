#pragma once

#include "../Platform.h"
#include "../Task.h"
#include <string>

namespace irise {
    class Profiler {
        public:
            Profiler(iris::rt::Platform* platform);
            ~Profiler();

            void profileCompletedTask(iris::rt::Task* task);
            
        private:
            iris::rt::Platform* platform;
    };
}