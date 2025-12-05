#include "../include/npc.h"
#include <stdexcept>

NPC::NPC(const std::string& name, int x, int y, NPCType type)
    : name(name), x(x), y(y), alive(true), type(type) {
    if (x < 0 || x > 500 || y < 0 || y > 500) {
        throw std::invalid_argument("Coord must be in range [0, 500]");
    }
}

double NPC::distanceTo(const NPC& other) const {
    int dx = x - other.x;
    int dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}