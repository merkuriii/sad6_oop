#include "PrintVisitor.h"
#include <iostream>

void PrintVisitor::visit(const SlaveTrader& st) const {
    std::cout << "Type: " << st.getType() << ", Name: " << st.getName()
              << ", Position: (" << st.getX() << ", " << st.getY() << ")\n";
}

void PrintVisitor::visit(const Squirrel& sq) const {
    std::cout << "Type: " << sq.getType() << ", Name: " << sq.getName()
              << ", Position: (" << sq.getX() << ", " << sq.getY() << ")\n";
}

void PrintVisitor::visit(const Knight& ke) const {
    std::cout << "Type: " << ke.getType() << ", Name: " << ke.getName()
              << ", Position: (" << ke.getX() << ", " << ke.getY() << ")\n";
}