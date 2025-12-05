#include "../include/WorkerTrader.h"
#include "../include/BattleVisitor.h"

WorkerTrader::WorkerTrader(const std::string& name, int x, int y)
    : NPC(name, x, y, NPCType::WORKER_TRADER) {}

void WorkerTrader::accept(NPCVisitor& visitor) {
    visitor.visit(*this);
}

std::string WorkerTrader::getTypeString() const {
    return "Работорговец";
}