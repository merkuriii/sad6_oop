#ifndef WORLD_H
#define WORLD_H

#include "npc.h"
#include "Observer.h"
#include <vector>
#include <string>
#include <fstream>
#include <memory>

class World : public Subject {
private:
    std::vector<std::unique_ptr<NPC>> npcs;

    bool nameExists(const std::string& name) const;

public:
    bool addNPC(NPC* npc);
    void printAll() const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    void fightMode(double radius);
};

#endif