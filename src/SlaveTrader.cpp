#include "SlaveTrader.h"
#include "Squirrel.h"
#include "Visitor.h"

SlaveTrader::SlaveTrader(double x, double y, const std::string& name) : NPC(x, y, name) {}

std::string SlaveTrader::getType() const { 
    return "SlaveTrader"; 
}

void SlaveTrader::accept(const Visitor& v) const { v.visit(*this); }

bool SlaveTrader::canKill(const NPC* other) const {
    return dynamic_cast<const Squirrel*>(other) != nullptr;
}