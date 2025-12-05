#include "../include/Squirrel.h"
#include "../include/BattleVisitor.h"

Squirrel::Squirrel(const std::string& name, int x, int y)
    :NPC(name, x, y, NPCType::SQUIRREl) {}

void Squirrel::accept(NPCVisitor& visitor) {
    visitor.visit(*this);
}

std::string Squirrel::getTypeString() const {
    return "Белка";
}