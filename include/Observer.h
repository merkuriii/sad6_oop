#pragma once
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <fstream>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& message) = 0;
};