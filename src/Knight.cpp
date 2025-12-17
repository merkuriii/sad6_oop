#include "Knight.h"
#include "SlaveTrader.h"
#include "Visitor.h"

Knight::Knight(double x, double y, const std::string& name) : NPC(x, y, name) {}

std::string Knight::getType() const { return "Knight"; }

void Knight::accept(const Visitor& v) const { v.visit(*this); }

bool Knight::canKill(const NPC* other) const {
    return dynamic_cast<const SlaveTrader*>(other) != nullptr;
}