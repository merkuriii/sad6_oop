#pragma once
#include "npc.h"

class Squirrel : public NPC {
public:
    Squirrel(const std::string& name, int x, int y);
    void accept(NPCVisitor& visitor) override;
    std::string getTypeString() const override;
};
