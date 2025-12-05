#pragma once
#include "Observer.h"

class FileObserver : public Observer {
private:
    std::string filename;
    
public:
    FileObserver(const std::string& filename);
    void update(const std::string& message) override;
};