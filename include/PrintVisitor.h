#ifndef PRINTVISITOR_H
#define PRINTVISITOR_H

#include "Visitor.h"

class PrintVisitor : public Visitor {
public:
    void visit(const SlaveTrader& st) const override;
    void visit(const Squirrel& sq) const override;
    void visit(const Knight& ke) const override;
};

#endif