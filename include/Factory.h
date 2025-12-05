#pragma once
#include "npc.h"
#include"WorkerTrader.h"
#include "Knight.h"
#include "Squirrel.h"
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>

class NPCFactory {
public:
    static std::unique_ptr<NPC> createNPC(NPCType, const std::string& name, int x, int y);
    static std::vector<std::unique_ptr<NPC>> loadFromFile(const std::string& filename);
    static void saveToFile(const std::string& filename, const std::vector<std::unique_ptr<NPC>>& npcs);

private:
    static std::string typeToString(NPCType type);
    static NPCType stringToType(const std::string& typeStr);
};