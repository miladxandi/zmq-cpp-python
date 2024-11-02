#ifndef ZMQ_PROJECT_SECURITY_HPP
#define ZMQ_PROJECT_SECURITY_HPP

#include <string>
#include <vector>

class Security {
public:
    std::string command;
    bool Check();
private:
    bool isDangerousCommand(const std::string& cmd);
    std::vector<std::string> dangerousCommands = {
            "rm -rf",
            ":(){ :|:& };:",
            "mkfs",
            "dd if=",
            "shutdown",
            "reboot",
            "kill -9"
    };
};

#endif //ZMQ_PROJECT_SECURITY_HPP
