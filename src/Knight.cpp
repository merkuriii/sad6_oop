#include "../include/Knight.h"
#include "../include/BattleVisitor.h"

Knight::Knight(const std::string& name, int x, int y) 
    : NPC(name, x, y, NPCType::KNIGHT) {}

void Knight::accept(NPCVisitor& visitor) {
    visitor.visit(*this);
}

std::string Knight::getTypeString() const {
    return "Рыцарь";
}