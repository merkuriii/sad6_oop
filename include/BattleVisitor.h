#pragma once
#include "npc.h"
#include "Observer.h"

class WorkerTrader;
class Knight;
class Squirrel;

class NPCVisitor {
public:
    virtual ~NPCVisitor() = default;
    virtual void visit(WorkerTrader& worker) = 0;
    virtual void visit(Knight& knight) = 0;
    virtual void visit(Squirrel& squirrel) = 0;
};

class BattleVisitor : public NPCVisitor {
private:
    NPC* attacker;
    NPC* defender;
    double range;
    BattleLogger& logger;

public:
    BattleVisitor(NPC* attacker, NPC* defender, double range, BattleLogger& logger);

    void visit(WorkerTrader& worker) override;
    void visit(Knight& knight) override;
    void visit(Squirrel& squirrel) override;

    bool shouldFight() const;
};