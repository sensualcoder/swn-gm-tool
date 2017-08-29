#include <iostream>
#include <memory>
#include <typeinfo>
#include <vector>

#include "Asset.hpp"
#include "AssetManager.hpp"
#include "Faction.hpp"
#include "FactionManager.hpp"
#include "Manager.hpp"

using namespace SwnGmTool;

void printTestDivider(char div, std::string lineEnd)
{
    std::cout << std::string(50, div) << lineEnd;
}

void printTestHeader(std::string str)
{
    printTestDivider('=', "\n");
    std::cout << "=====" << str << "=====" << std::endl;
    printTestDivider('=', "\n");
}

void printTestLine(std::string str)
{
    std::cout << "***" << str << "***" << std::endl;
}

template <typename T>
void test_manager(Manager<T>* manager, std::string name)
{
    printTestLine(name + " Tests");

    T testItem = { "Test" };

    printTestLine("Create test manager");
    std::unique_ptr<Manager<T>> testManager(manager);
    std::cout << "Manager size: " << sizeof(*testManager) << "\n\n";

    printTestLine("Check manager list size");
    std::cout << "List size: " << testManager->GetList().size() << "\n\n";

    printTestLine("Add manager to faction list");
    testManager->Add(testItem);
    std::cout << "List size: " << testManager->GetList().size() << "\n\n";

    printTestLine("Check item name");
    std::cout << "Item name: " << testManager->GetItem(0).Name << "\n\n";

    printTestLine("Remove item from list");
    testManager->Remove(0);
    std::cout << "List size: " << testManager->GetList().size() << "\n\n";

    printTestLine("Add item back and then clear list");
    testManager->Add(testItem);
    std::cout << "List size: " << testManager->GetList().size() << std::endl;
    testManager->ClearList();
    std::cout << "List size: " << testManager->GetList().size() << "\n\n";

    printTestLine("Add a large amount of items to the list");
    int test_count = 1000000;
    for(int i = 0; i < test_count; i++)
    {
        std::string name = "Test" + std::to_string(i);
        std::unique_ptr<T> tmp = std::unique_ptr<T>(new T { name });
        testManager->Add(*tmp);
    }
    std::cout << "List size: " << testManager->GetList().size() << std::endl;
    std::cout << "First item: " << testManager->GetList().front().Name << std::endl;
    std::cout << "Last item: " << testManager->GetList().back().Name << "\n\n";

    printTestDivider('=', "\n\n");
}

template <typename T>
void test_struct(std::string name)
{
    printTestLine(name + "struct tests");
    
    printTestLine("Create test struct");
    T testStruct = { "Test" };
    std::cout << name + "struct size: " << sizeof(testStruct) << "\n\n";

    printTestDivider('=', "\n\n");
}

void runAllTests()
{
    printTestHeader("Faction Control Tests");
    test_struct<Asset>("Asset");
    test_struct<Faction>("Faction");
    test_manager<Asset>(new AssetManager, "AssetManager");
    test_manager<Faction>(new FactionManager, "FactionManager");

    printTestHeader("Sector Generator Tests");
}

int main(int argc, char* argv[])
{
    runAllTests();

    return 0;
}
