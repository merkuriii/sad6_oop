#include "Observer.h"
#include <iostream>

void Subject::addObserver(Observer* obs) {
    observers.push_back(obs);
}

void Subject::notify(const std::string& message) {
    for (auto obs : observers) {
        obs->update(message);
    }
}

void ConsoleObserver::update(const std::string& message) {
    std::cout << message << std::endl;
}

FileObserver::FileObserver(const std::string& filename) {
    file.open(filename, std::ios::app);
}

FileObserver::~FileObserver() {
    if (file.is_open()) file.close();
}

void FileObserver::update(const std::string& message) {
    if (file.is_open()) {
        file << message << std::endl;
    }
}