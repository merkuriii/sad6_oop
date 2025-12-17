// src/main.cpp
#include "World.h"
#include "Factory.h"
#include "Observer.h"
#include <iostream>

int main() {
    World world;
    ConsoleObserver co;
    FileObserver fo("log.txt");
    world.addObserver(&co);
    world.addObserver(&fo);

    // Demo: Add NPCs
    world.addNPC(NPCFactory::create("SlaveTrader", 10.0, 10.0, "Trader1"));
    world.addNPC(NPCFactory::create("Squirrel", 15.0, 15.0, "Squirrel1"));
    world.addNPC(NPCFactory::create("KnightErrant", 20.0, 20.0, "Knight1"));
    world.addNPC(NPCFactory::create("Squirrel", 16.0, 16.0, "Squirrel2"));

    std::cout << "Initial NPCs:\n";
    world.printAll();

    // Save
    world.saveToFile("npcs.txt");

    // Fight mode with radius 10.0
    std::cout << "\nFight mode:\n";
    world.fightMode(10.0);

    std::cout << "\nAfter fight:\n";
    world.printAll();

    // Load (demo reload)
    World world2;
    world2.addObserver(&co);
    world2.addObserver(&fo);
    world2.loadFromFile("npcs.txt");
    std::cout << "\nLoaded NPCs:\n";
    world2.printAll();

    return 0;
}