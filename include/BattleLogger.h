#pragma once
#include "Observer.h"
#include <memory>
#include <vector>
//bb

class BattleLogger {
private:
    std::vector<std::shared_ptr<Observer>> observers;
    
public:
    void addObserver(std::shared_ptr<Observer> observer);
    void removeObserver(std::shared_ptr<Observer> observer);
    void notify(const std::string& message);
    
    static BattleLogger& getInstance() {
        static BattleLogger instance;
        return instance;
    }
    
private:
    BattleLogger() = default;
    BattleLogger(const BattleLogger&) = delete;
    BattleLogger& operator=(const BattleLogger&) = delete;
};