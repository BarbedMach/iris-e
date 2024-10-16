#pragma once

#include <string>

namespace irise::Message {
    template<typename T>
    concept MessageType = requires(T a) {
        a.mtype;
    };

    enum class Type : long {
        Result = 1,
        DeviceInfo = 2,
        KernelInfo = 3
    };

    struct Result {
        long mtype;
        int result;
    };

    struct DeviceInfo {
        long mtype;
        int devNo;
        int platformNo;
        std::string vendor;
        std::string name;
        int type;
        int model;
    };

    struct KernelInfo {
        long mtype;
        unsigned long uid;
    };

    template<MessageType T>
    void sendMessage(int msgid, const T& message, Type messageType) {
        T msg = message;
        msg.mtype = messageType
        if (msgsnd(msgid, &msg, sizeof(msg) - sizeof(msg.mtype), 0) == -1) {
            perror("msgsnd failed.");
            exit(EXIT_FAILURE);
        }
    }

    template<MessageType T>
    T receiveMessage(int msgid, Type messageType, int messageFlag) {
        T msg{}
        if (msgrcv(msgid, &msg, sizeof(msg) - sizeof(msg.mtype), messageType, messageFlag) == -1) {
            perror("msgrcv failed.");
            exit(EXIT_FAILURE);
        
        return msg;
        }
    }
}