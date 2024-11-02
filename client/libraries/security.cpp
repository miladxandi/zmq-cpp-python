#include "security.hpp"
#include <iostream>

bool Security::Check() {
    return !isDangerousCommand(command);
}

bool Security::isDangerousCommand(const std::string& cmd) {
    // بررسی می‌کنیم که آیا هر کدام از دستورات خطرساز در متن ورودی وجود دارد یا خیر
    for (const auto& dangerous : dangerousCommands) {
        if (cmd.find(dangerous) != std::string::npos) {
            std::cout << "Warning: Dangerous command detected - " << dangerous << std::endl;
            return true;
        }
    }
    return false;
}
