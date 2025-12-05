#pragma once 
#include "Observer.h"

class ConsoleObserver : public Observer {
public:
    void update(const std::string& message) override;
};