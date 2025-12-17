#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>
#include <vector>
#include <fstream>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& message) = 0;
};

class Subject {
private:
    std::vector<Observer*> observers;

public:
    void addObserver(Observer* obs);
    void notify(const std::string& message);
};

class ConsoleObserver : public Observer {
public:
    void update(const std::string& message) override;
};

class FileObserver : public Observer {
private:
    std::ofstream file;

public:
    FileObserver(const std::string& filename);
    ~FileObserver();
    void update(const std::string& message) override;
};

#endif