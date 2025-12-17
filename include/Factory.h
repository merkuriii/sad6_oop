#ifndef FACTORY_H
#define FACTORY_H

#include "npc.h"
#include <string>

class NPCFactory {
public:
    static NPC* create(const std::string& type, double x, double y, const std::string& name);
};

#endif