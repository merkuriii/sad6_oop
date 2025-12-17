#include "World.h"
#include "Factory.h"
#include "PrintVisitor.h"
#include <iostream>
#include <sstream>
#include <algorithm>

bool World::nameExists(const std::string& name) const {
    for (const auto& npc : npcs) {
        if (npc->getName() == name) return true;
    }
    return false;
}

bool World::addNPC(NPC* npc) {
    if (!npc || nameExists(npc->getName())) return false;
    if (npc->getX() < 0 || npc->getX() > 500 || npc->getY() < 0 || npc->getY() > 500) return false;
    npcs.emplace_back(npc);
    return true;
}

void World::printAll() const {
    PrintVisitor pv;
    for (const auto& npc : npcs) {
        npc->accept(pv);
    }
}

void World::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) return;
    for (const auto& npc : npcs) {
        file << npc->getType() << " " << npc->getX() << " " << npc->getY() << " " << npc->getName() << std::endl;
    }
}

void World::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) return;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type, name;
        double x, y;
        iss >> type >> x >> y >> name;
        NPC* npc = NPCFactory::create(type, x, y, name);
        if (npc) addNPC(npc);
    }
}

void World::fightMode(double radius) {
    if (npcs.empty()) return;

    std::vector<bool> is_dead(npcs.size(), false);

    // Первый проход: определяем, кто умирает (только пары i < j)
    for (size_t i = 0; i < npcs.size(); ++i) {
        for (size_t j = i + 1; j < npcs.size(); ++j) {
            const NPC* a = npcs[i].get();
            const NPC* b = npcs[j].get();

            double dist = a->distanceTo(b);
            if (dist > radius) continue;

            bool a_kills_b = a->canKill(b);
            bool b_kills_a = b->canKill(a);

            if (a_kills_b && b_kills_a) {
                // Взаимное убийство
                std::string msg = a->getName() + " (" + a->getType() + ") and " +
                                  b->getName() + " (" + b->getType() + ") killed each other.";
                notify(msg);
                is_dead[i] = true;
                is_dead[j] = true;
            } else if (a_kills_b) {
                std::string msg = a->getName() + " (" + a->getType() + ") killed " +
                                  b->getName() + " (" + b->getType() + ").";
                notify(msg);
                is_dead[j] = true;
            } else if (b_kills_a) {
                std::string msg = b->getName() + " (" + b->getType() + ") killed " +
                                  a->getName() + " (" + a->getType() + ").";
                notify(msg);
                is_dead[i] = true;
            }
        }
    }

    // Второй проход: собираем только живых
    std::vector<std::unique_ptr<NPC>> survivors;
    survivors.reserve(npcs.size());

    for (size_t i = 0; i < npcs.size(); ++i) {
        if (!is_dead[i]) {
            survivors.push_back(std::move(npcs[i]));
        }
    }

    npcs = std::move(survivors);
}