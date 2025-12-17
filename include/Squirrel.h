#ifndef SQUIRREL_H
#define SQUIRREL_H

#include "npc.h"

class Squirrel : public NPC {
public:
    Squirrel(double x, double y, const std::string& name);
    std::string getType() const override;
    void accept(const Visitor& v) const override;
    bool canKill(const NPC* other) const override;
};

#endif