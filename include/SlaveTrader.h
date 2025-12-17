#ifndef SLAVETRADER_H
#define SLAVETRADER_H

#include "npc.h"

class SlaveTrader : public NPC {
public:
    SlaveTrader(double x, double y, const std::string& name);
    std::string getType() const override;
    void accept(const Visitor& v) const override;
    bool canKill(const NPC* other) const override;
};

#endif