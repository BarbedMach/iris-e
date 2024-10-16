#include "MessageQueue.hpp"

namespace irise {
    MessageQueue::~MessageQueue() {
        msgctl(msgid, IPC_RMID, NULL);
    }

    MessageQueue& MessageQueue::instance() {
        static MessageQueue instance;
        return instance;
    }

    void MessageQueue::setKey(const std::string& path, int projectId) {
        key = ftok(path.data(), projectId);
        msgid = msgget(key, 0666 | IPC_CREAT);

        if (msgid == -1) {
            perror("msgget failed.");
            exit(EXIT_FAILURE);
        }
    }

    int MessageQueue::getMsgid() {
        return msgid;
    }
}