#include "npc.h"

NPC::NPC(double x, double y, const std::string& name) : x(x), y(y), name(name) {}

double NPC::getX() const { return x; }
double NPC::getY() const { return y; }
const std::string& NPC::getName() const { return name; }

double NPC::distanceTo(const NPC* other) const {
    return std::sqrt(std::pow(x - other->x, 2) + std::pow(y - other->y, 2));
}