#pragma once
#include "npc.h"

class WorkerTrader : public NPC {
public:
    WorkerTrader(const std::string& name, int x, int y);
    void accept(NPCVisitor& visitor) override;
    std::string getTypeString() const override;
};