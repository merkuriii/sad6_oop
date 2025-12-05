#include "../include/FileObserver.h"
#include <fstream>

FileObserver::FileObserver(const std::string& filename) 
    : filename(filename) {}

void FileObserver::update(const std::string& message) {
    std::ofstream file(filename, std::ios::app);
    if (file.is_open()) {
        file << message << std::endl;
    }
}