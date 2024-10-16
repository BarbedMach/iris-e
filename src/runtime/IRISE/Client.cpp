#include "Client.hpp"

namespace irise {
    Client& Client::instance() {
        static Client instance;
        return instance;
    }
}