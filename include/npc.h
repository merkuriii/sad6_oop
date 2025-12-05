#pragma once
#include <string>
#include <memory>
#include <cmath>

enum class NPCType {
    WORKER_TRADER,
    KNIGHT,
    SQUIRREL
};

class NPCVisitor;

class NPC {
protected:
    std::string name;
    int x, y;
    bool alive;
    NPCType type;

public:
    NPC(const std::string& name, int x, int y, NPCType type);
    virtual ~NPC() = default;

    virtual void accept(NPCVisitor& visitor) = 0;
    virtual std::string getTypeString() const = 0;

    bool isAlive() const { return alive; } 
    void kill() { alive = false; }

    std::string getName() const { return name; }
    int getX() const { return x; }
    int getY() const { return y; }
    NPCType getType() const { return type; }

    double distanceTo(const NPC& other) const;
};