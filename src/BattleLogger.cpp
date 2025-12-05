#include "../include/BattleLogger.h"

void BattleLogger::addObserver(std::shared_ptr<Observer> observer) {
    observers.push_back(observer);
}

void BattleLogger::removeObserver(std::shared_ptr<Observer> observer) {
    observers.erase(
        std::remove(observers.begin(), observers.end(), observer),
        observers.end()
    );
}

void BattleLogger::notify(const std::string& message) {
    for (auto& observer : observers) {
        observer->update(message);
    }
}