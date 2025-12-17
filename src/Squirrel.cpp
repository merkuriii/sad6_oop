#include "Squirrel.h"
#include "Visitor.h"

Squirrel::Squirrel(double x, double y, const std::string& name) : NPC(x, y, name) {}

std::string Squirrel::getType() const { 
    return "Squirrel"; 
}

void Squirrel::accept(const Visitor& v) const { 
    v.visit(*this); 
}

bool Squirrel::canKill(const NPC* other) const {
    return dynamic_cast<const Squirrel*>(other) != nullptr;
}