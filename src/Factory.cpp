#include "../include/Factory.h"

std::unique_ptr<NPC> NPCFactory::createNPC(NPCType type, 
                                          const std::string& name, 
                                          int x, int y) {
    switch (type) {
        case NPCType::WORKER_TRADER:
            return std::make_unique<WorkerTrader>(name, x, y);
        case NPCType::KNIGHT:
            return std::make_unique<Knight>(name, x, y);
        case NPCType::SQUIRREL:
            return std::make_unique<Squirrel>(name, x, y);
        default:
            throw std::invalid_argument("Unknown NPC type");
    }
}

std::string NPCFactory::typeToString(NPCType type) {
    switch (type) {
        case NPCType::WORKER_TRADER: return "WORKER_TRADER";
        case NPCType::KNIGHT: return "KNIGHT";
        case NPCType::SQUIRREL: return "SQUIRREL";
        default: return "UNKNOWN";
    }
}

NPCType NPCFactory::stringToType(const std::string& typeStr) {
    if (typeStr == "WORKER_TRADER") return NPCType::WORKER_TRADER;
    if (typeStr == "KNIGHT") return NPCType::KNIGHT;
    if (typeStr == "SQUIRREL") return NPCType::SQUIRREL;
    throw std::invalid_argument("Unknown NPC type string: " + typeStr);
}

void NPCFactory::saveToFile(const std::string& filename,
                           const std::vector<std::unique_ptr<NPC>>& npcs) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file for writing: " + filename);
    }
    
    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            file << typeToString(npc->getType()) << " "
                 << npc->getName() << " "
                 << npc->getX() << " "
                 << npc->getY() << "\n";
        }
    }
}

std::vector<std::unique_ptr<NPC>> NPCFactory::loadFromFile(
    const std::string& filename) {
    
    std::vector<std::unique_ptr<NPC>> npcs;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string typeStr, name;
        int x, y;
        
        if (iss >> typeStr >> name >> x >> y) {
            NPCType type = stringToType(typeStr);
            npcs.push_back(createNPC(type, name, x, y));
        }
    }
    
    return npcs;
}