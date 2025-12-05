#pragma once
#include "Factory.h"
#include "BattleLogger.h"
#include <memory>
#include <vector>
#include <algorithm>
// bb
class DungeonEditor {
private:
    std::vector<std::unique_ptr<NPC>> npcs;
    static const int MAP_SIZE = 500;
    
public:
    void addNPC(NPCType type, const std::string& name, int x, int y);
    bool removeNPC(const std::string& name);
    
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    
    void printAll() const;
    void startBattle(double range);
    
    const std::vector<std::unique_ptr<NPC>>& getNPCs() const { return npcs; }
    size_t getAliveCount() const;
    
private:
    void removeDeadNPCs();
};