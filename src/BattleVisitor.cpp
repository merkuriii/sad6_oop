#include "../include/BattleVisitor.h"
#include "../include/WorkerTrader.h"
#include "../include/Knight.h"
#include "../include/Squirrel.h"
// bb

BattleVisitor::BattleVisitor(NPC* attacker, NPC* defender, 
                            double range, BattleLogger& logger)
    : attacker(attacker), defender(defender), range(range), logger(logger) {}

bool BattleVisitor::shouldFight() const {
    if (!attacker || !defender) return false;
    if (!attacker->isAlive() || !defender->isAlive()) return false;
    if (attacker == defender) return false;
    
    return attacker->distanceTo(*defender) <= range;
}

void BattleVisitor::visit(WorkerTrader& worker) {
    if (!shouldFight()) return;
    
    // Работоторговец убивает белку
    if (defender->getType() == NPCType::SQUIRREL) {
        defender->kill();
        logger.notify(worker.getName() + " убил " + defender->getName());
    }
}

void BattleVisitor::visit(Knight& knight) {
    if (!shouldFight()) return;
    
    // Рыцарь убивает работоторговцев
    if (defender->getType() == NPCType::WORKER_TRADER) {
        defender->kill();
        logger.notify(knight.getName() + " убил " + defender->getName());
    }
}

void BattleVisitor::visit(Squirrel& squirrel) {
    if (!shouldFight()) return;
    
    // Белка убивает белку (делит территорию)
    if (defender->getType() == NPCType::SQUIRREL) {
        defender->kill();
        logger.notify(squirrel.getName() + " убил " + defender->getName());
        
        // Также белка может погибнуть в бою с другой белкой
        squirrel.kill();
        logger.notify(defender->getName() + " убил " + squirrel.getName());
    }
}