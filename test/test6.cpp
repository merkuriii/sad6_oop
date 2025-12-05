#include <gtest/gtest.h>
#include "../include/DungeonEditor.h"
#include "../include/Factory.h"
#include "../include/FileObserver.h"
#include <fstream>

TEST(NPCTest, CreationAndProperties) {
    auto worker = NPCFactory::createNPC(NPCType::WORKER_TRADER, "Worker1", 100, 100);
    EXPECT_EQ(worker->getName(), "Worker1");
    EXPECT_EQ(worker->getX(), 100);
    EXPECT_EQ(worker->getY(), 100);
    EXPECT_TRUE(worker->isAlive());
    EXPECT_EQ(worker->getType(), NPCType::WORKER_TRADER);
}

TEST(NPCTest, InvalidCoordinates) {
    EXPECT_THROW(
        NPCFactory::createNPC(NPCType::WORKER_TRADER, "Worker", -10, 100),
        std::invalid_argument
    );
    
    EXPECT_THROW(
        NPCFactory::createNPC(NPCType::WORKER_TRADER, "Worker", 100, 600),
        std::invalid_argument
    );
}

TEST(DungeonEditorTest, AddAndRemoveNPC) {
    DungeonEditor editor;
    
    editor.addNPC(NPCType::WORKER_TRADER, "TestNPC1", 50, 50);
    editor.addNPC(NPCType::KNIGHT, "TestNPC2", 100, 100);
    
    EXPECT_EQ(editor.getNPCs().size(), 2);
    EXPECT_EQ(editor.getAliveCount(), 2);
    
    bool removed = editor.removeNPC("TestNPC1");
    EXPECT_TRUE(removed);
    EXPECT_EQ(editor.getNPCs().size(), 1);
    EXPECT_EQ(editor.getAliveCount(), 1);
}

TEST(DungeonEditorTest, BattleWorkerVsSquirrel) {
    DungeonEditor editor;
    
    editor.addNPC(NPCType::WORKER_TRADER, "Worker", 100, 100);
    editor.addNPC(NPCType::SQUIRREL, "Squirrel", 105, 105);
    
    EXPECT_EQ(editor.getAliveCount(), 2);
    
    // Работоторговец должен убить белку
    editor.startBattle(10.0);
    
    EXPECT_EQ(editor.getAliveCount(), 1);
    EXPECT_EQ(editor.getNPCs()[0]->getName(), "Worker");
}

TEST(DungeonEditorTest, BattleKnightVsWorker) {
    DungeonEditor editor;
    
    editor.addNPC(NPCType::KNIGHT, "Knight", 200, 200);
    editor.addNPC(NPCType::WORKER_TRADER, "Worker", 205, 205);
    
    // Рыцарь должен убить работоторговца
    editor.startBattle(10.0);
    
    EXPECT_EQ(editor.getAliveCount(), 1);
    EXPECT_EQ(editor.getNPCs()[0]->getName(), "Knight");
}

TEST(DungeonEditorTest, BattleSquirrelVsSquirrel) {
    DungeonEditor editor;
    
    editor.addNPC(NPCType::SQUIRREL, "Squirrel1", 300, 300);
    editor.addNPC(NPCType::SQUIRREL, "Squirrel2", 305, 305);
    
    // Две белки должны убить друг друга
    editor.startBattle(10.0);
    
    EXPECT_EQ(editor.getAliveCount(), 0);
}

TEST(DungeonEditorTest, SaveAndLoad) {
    DungeonEditor editor;
    
    editor.addNPC(NPCType::WORKER_TRADER, "WorkerSave", 10, 10);
    editor.addNPC(NPCType::KNIGHT, "KnightSave", 20, 20);
    editor.addNPC(NPCType::SQUIRREL, "SquirrelSave", 30, 30);
    
    editor.saveToFile("test_save.txt");
    
    DungeonEditor editor2;
    editor2.loadFromFile("test_save.txt");
    
    EXPECT_EQ(editor2.getNPCs().size(), 3);
    EXPECT_EQ(editor2.getAliveCount(), 3);
}

TEST(FactoryTest, StringConversion) {
    EXPECT_EQ(NPCFactory::typeToString(NPCType::WORKER_TRADER), "WORKER_TRADER");
    EXPECT_EQ(NPCFactory::typeToString(NPCType::KNIGHT), "KNIGHT");
    EXPECT_EQ(NPCFactory::typeToString(NPCType::SQUIRREL), "SQUIRREL");
    
    EXPECT_EQ(NPCFactory::stringToType("WORKER_TRADER"), NPCType::WORKER_TRADER);
    EXPECT_EQ(NPCFactory::stringToType("KNIGHT"), NPCType::KNIGHT);
    EXPECT_EQ(NPCFactory::stringToType("SQUIRREL"), NPCType::SQUIRREL);
    
    EXPECT_THROW(NPCFactory::stringToType("UNKNOWN"), std::invalid_argument);
}

TEST(ObserverTest, FileObserver) {
    // Удаляем старый лог файл
    std::remove("test_log.txt");
    
    FileObserver observer("test_log.txt");
    observer.update("Test message 1");
    observer.update("Test message 2");
    
    std::ifstream file("test_log.txt");
    ASSERT_TRUE(file.is_open());
    
    std::string line;
    std::getline(file, line);
    EXPECT_EQ(line, "Test message 1");
    
    std::getline(file, line);
    EXPECT_EQ(line, "Test message 2");
    
    file.close();
}

TEST(DistanceTest, CalculateDistance) {
    auto npc1 = NPCFactory::createNPC(NPCType::WORKER_TRADER, "N1", 0, 0);
    auto npc2 = NPCFactory::createNPC(NPCType::WORKER_TRADER, "N2", 3, 4);
    
    double distance = npc1->distanceTo(*npc2);
    EXPECT_DOUBLE_EQ(distance, 5.0); // 3-4-5 треугольник
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}