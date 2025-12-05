#include "../include/DungeonEditor.h"
#include "../include/ConsoleObserver.h"
#include "../include/FileObserver.h"
#include <iostream>
#include <memory>

void printMenu() {
    std::cout << "\n=== Редактор подземелья Balagur Fate 3 ===\n";
    std::cout << "1. Добавить NPC\n";
    std::cout << "2. Удалить NPC по имени\n";
    std::cout << "3. Показать всех NPC\n";
    std::cout << "4. Сохранить в файл\n";
    std::cout << "5. Загрузить из файла\n";
    std::cout << "6. Начать бой\n";
    std::cout << "7. Выход\n";
    std::cout << "Выбор: ";
}

int main() {
    DungeonEditor editor;
    
    // Добавляем наблюдателей
    auto consoleObserver = std::make_shared<ConsoleObserver>();
    auto fileObserver = std::make_shared<FileObserver>("log.txt");
    BattleLogger::getInstance().addObserver(consoleObserver);
    BattleLogger::getInstance().addObserver(fileObserver);
    
    std::cout << "Добро пожаловать в редактор подземелья!\n";
    std::cout << "Логи боя будут записываться в log.txt\n";
    
    while (true) {
        printMenu();
        
        int choice;
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(256, '\n');
            continue;
        }
        
        switch (choice) {
            case 1: {
                int type;
                std::string name;
                int x, y;
                
                std::cout << "Тип NPC (0-Работоторговец, 1-Рыцарь, 2-Белка): ";
                std::cin >> type;
                
                std::cout << "Имя NPC: ";
                std::cin >> name;
                
                std::cout << "Координата X (0-500): ";
                std::cin >> x;
                
                std::cout << "Координата Y (0-500): ";
                std::cin >> y;
                
                editor.addNPC(static_cast<NPCType>(type), name, x, y);
                break;
            }
            
            case 2: {
                std::string name;
                std::cout << "Имя NPC для удаления: ";
                std::cin >> name;
                
                if (editor.removeNPC(name)) {
                    std::cout << "NPC удален\n";
                } else {
                    std::cout << "NPC не найден\n";
                }
                break;
            }
            
            case 3:
                editor.printAll();
                break;
                
            case 4: {
                std::string filename;
                std::cout << "Имя файла для сохранения: ";
                std::cin >> filename;
                editor.saveToFile(filename);
                break;
            }
                
            case 5: {
                std::string filename;
                std::cout << "Имя файла для загрузки: ";
                std::cin >> filename;
                editor.loadFromFile(filename);
                break;
            }
                
            case 6: {
                double range;
                std::cout << "Дальность боя (в метрах): ";
                std::cin >> range;
                editor.startBattle(range);
                break;
            }
                
            case 7:
                std::cout << "Выход из программы\n";
                return 0;
                
            default:
                std::cout << "Неверный выбор\n";
        }
    }
    
    return 0;
}