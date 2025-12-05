#include "../include/ConsoleObserver.h"

void ConsoleObserver::update(const std::string& message) {
    std::cout << "[FIGHT] " << message << std::endl;
}