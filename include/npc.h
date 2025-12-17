#ifndef NPC_H
#define NPC_H

#include <string>
#include <cmath>

class Visitor;

class NPC {
protected:
    double x, y;
    std::string name;

public:
    NPC(double x, double y, const std::string& name);
    virtual ~NPC() = default;

    virtual std::string getType() const = 0;
    virtual void accept(const Visitor& v) const = 0;
    virtual bool canKill(const NPC* other) const = 0;

    double getX() const;
    double getY() const;
    const std::string& getName() const;

    double distanceTo(const NPC* other) const;
};

#endif