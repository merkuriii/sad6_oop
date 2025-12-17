#include "Factory.h"
#include "SlaveTrader.h"
#include "Squirrel.h"
#include "Knight.h"

NPC* NPCFactory::create(const std::string& type, double x, double y, const std::string& name) {
    if (type == "SlaveTrader") return new SlaveTrader(x, y, name);
    if (type == "Squirrel") return new Squirrel(x, y, name);
    if (type == "Knight") return new Knight(x, y, name);
    return nullptr;
}