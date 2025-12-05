#pragma once
#include "npc.h"

class Knight : public NPC {
public:
    Knight(const std::string& name, int x, int y);
    void accept(NPCVisitor& visitor) override;
    std::string getTypeString() const override;
};
