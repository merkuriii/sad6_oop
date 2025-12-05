#include "include/DungeonEditor.h"
#include "include/BattleVisitor.h"
#include <iostream>
//bb
void DungeonEditor::addNPC(NPCType type, const std::string& name, int x, int y) {
    try {
        auto npc = NPCFactory::createNPC(type, name, x, y);
        npcs.push_back(std::move(npc));
        std::cout << "Добавлен NPC: " << name << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка добавления NPC: " << e.what() << std::endl;
    }
}

bool DungeonEditor::removeNPC(const std::string& name) {
    auto it = std::remove_if(npcs.begin(), npcs.end(),
        [&name](const std::unique_ptr<NPC>& npc) {
            return npc->getName() == name;
        });
    
    if (it != npcs.end()) {
        npcs.erase(it, npcs.end());
        return true;
    }
    return false;
}

void DungeonEditor::saveToFile(const std::string& filename) const {
    try {
        NPCFactory::saveToFile(filename, npcs);
        std::cout << "Сохранено в файл: " << filename << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка сохранения: " << e.what() << std::endl;
    }
}

void DungeonEditor::loadFromFile(const std::string& filename) {
    try {
        npcs = NPCFactory::loadFromFile(filename);
        std::cout << "Загружено из файла: " << filename 
                  << " (" << npcs.size() << " NPC)" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка загрузки: " << e.what() << std::endl;
    }
}

void DungeonEditor::printAll() const {
    std::cout << "\n=== Список NPC (" << getAliveCount() << " живых) ===\n";
    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            std::cout << npc->getTypeString() << " \"" << npc->getName()
                      << "\" (" << npc->getX() << ", " << npc->getY() << ")\n";
        }
    }
    std::cout << "=====================\n";
}

void DungeonEditor::startBattle(double range) {
    std::cout << "\n=== НАЧАЛО БОЯ (дальность: " << range << "м) ===\n";
    
    // Создаем копию для безопасной итерации
    auto npcsCopy = npcs;
    
    for (size_t i = 0; i < npcsCopy.size(); i++) {
        if (!npcsCopy[i]->isAlive()) continue;
        
        for (size_t j = 0; j < npcsCopy.size(); j++) {
            if (i == j || !npcsCopy[j]->isAlive()) continue;
            
            double distance = npcsCopy[i]->distanceTo(*npcsCopy[j]);
            if (distance <= range) {
                BattleVisitor visitor(
                    npcsCopy[i].get(), 
                    npcsCopy[j].get(), 
                    range, 
                    BattleLogger::getInstance()
                );
                npcsCopy[i]->accept(visitor);
            }
        }
    }
    
    // Обновляем оригинальный вектор
    npcs = std::move(npcsCopy);
    removeDeadNPCs();
    
    std::cout << "=== КОНЕЦ БОЯ ===\n";
    std::cout << "Осталось живых: " << getAliveCount() << "\n";
}

size_t DungeonEditor::getAliveCount() const {
    return std::count_if(npcs.begin(), npcs.end(),
        [](const std::unique_ptr<NPC>& npc) {
            return npc->isAlive();
        });
}

void DungeonEditor::removeDeadNPCs() {
    npcs.erase(
        std::remove_if(npcs.begin(), npcs.end(),
            [](const std::unique_ptr<NPC>& npc) {
                return !npc->isAlive();
            }),
        npcs.end()
    );
}