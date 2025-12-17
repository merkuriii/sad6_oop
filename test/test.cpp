#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include "World.h"
#include "Factory.h"
#include "PrintVisitor.h"

TEST(WorldTest, AddNPC) {
    World world;

    NPC* npc1 = NPCFactory::create("Squirrel", 100.0, 100.0, "Sq1");
    EXPECT_TRUE(world.addNPC(npc1));

    NPC* npc2 = NPCFactory::create("Squirrel", 200.0, 200.0, "Sq1");
    EXPECT_FALSE(world.addNPC(npc2));
    delete npc2;

    NPC* npc3 = NPCFactory::create("Knight", -10.0, 100.0, "KnightOut");
    EXPECT_FALSE(world.addNPC(npc3));
    delete npc3;

    NPC* npc4 = NPCFactory::create("Knight", 600.0, 100.0, "KnightOut2");
    EXPECT_FALSE(world.addNPC(npc4));
    delete npc4;
}

TEST(NPCTest, CanKillRules) {
    SlaveTrader st(0, 0, "Trader");
    Squirrel sq1(0, 0, "Sq1");
    Squirrel sq2(0, 0, "Sq2");
    Knight kn(0, 0, "Knight");

    EXPECT_TRUE(st.canKill(&sq1));
    EXPECT_FALSE(st.canKill(&kn));
    EXPECT_FALSE(st.canKill(&st));

    EXPECT_TRUE(kn.canKill(&st));
    EXPECT_FALSE(kn.canKill(&sq1));
    EXPECT_FALSE(kn.canKill(&kn));

    EXPECT_TRUE(sq1.canKill(&sq2));
    EXPECT_TRUE(sq2.canKill(&sq1));
    EXPECT_FALSE(sq1.canKill(&st));
    EXPECT_FALSE(sq1.canKill(&kn));
}

TEST(VisitorTest, PrintVisitor) {
    testing::internal::CaptureStdout();

    PrintVisitor pv;
    Squirrel sq(10, 20, "TestSquirrel");
    Knight kn(30, 40, "TestKnight");

    sq.accept(pv);
    kn.accept(pv);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("Squirrel") != std::string::npos);
    EXPECT_TRUE(output.find("TestSquirrel") != std::string::npos);
    EXPECT_TRUE(output.find("(10, 20") != std::string::npos);

    EXPECT_TRUE(output.find("Knight") != std::string::npos);
    EXPECT_TRUE(output.find("TestKnight") != std::string::npos);
}

TEST(WorldTest, SaveLoad) {
    World world1;
    world1.addNPC(NPCFactory::create("SlaveTrader", 50, 50, "Trader1"));
    world1.addNPC(NPCFactory::create("Squirrel", 60, 60, "Sq1"));

    world1.saveToFile("test_npcs.txt");

    std::ifstream file("test_npcs.txt");
    ASSERT_TRUE(file.is_open());
    
    std::string line1, line2;
    std::getline(file, line1);
    std::getline(file, line2);
    EXPECT_TRUE(line1.find("SlaveTrader") != std::string::npos);
    EXPECT_TRUE(line2.find("Squirrel") != std::string::npos);
    file.close();

    World world2;
    world2.loadFromFile("test_npcs.txt");

    testing::internal::CaptureStdout();
    world2.printAll();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("Trader1") != std::string::npos);
    EXPECT_TRUE(output.find("Sq1") != std::string::npos);

    std::remove("test_npcs.txt");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}