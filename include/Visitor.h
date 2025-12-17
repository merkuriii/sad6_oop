#ifndef VISITOR_H
#define VISITOR_H

#include "SlaveTrader.h"
#include "Squirrel.h"
#include "Knight.h"

class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visit(const SlaveTrader& st) const = 0;
    virtual void visit(const Squirrel& sq) const = 0;
    virtual void visit(const Knight& ke) const = 0;
};

#endif