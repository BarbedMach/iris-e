#pragma once

#include <string>
#include <sys/msg.h>
#include <sys/ipc.h>

namespace irise {
    class MessageQueue {
        public:
            virtual ~MessageQueue();
            MessageQueue(const MessageQueue&) = delete;
            MessageQueue& operator=(const MessageQueue&) = delete;

            static MessageQueue& instance();

            void setKey(const std::string& path, int projectId);
            int getMsgid();
        
        protected:
            MessageQueue() = default;
        
        private:
            key_t key;
            int msgid;
    };
}