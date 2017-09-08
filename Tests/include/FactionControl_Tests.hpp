#ifndef FACTION_CONTROL_TESTS_HPP
#define FACTION_CONTROL_TESTS_HPP

#include <fstream>
#include <iostream>
#include <memory>

#include <cereal/archives/json.hpp>

#include "AssetDTO.hpp"
#include "DiceRoll.hpp"
#include "FactionDTO.hpp"
#include "FactionControl.hpp"

#include "TestHelpers.hpp"

using namespace SwnGmTool;

namespace Tests
{
    void printList(std::vector<FactionDTO>& list)
    {
        std::unique_ptr<std::vector<FactionDTO> > listPtr = std::unique_ptr<std::vector<FactionDTO> >(&list);

        if(listPtr->size() == 0)
            return;

        for(auto i : *listPtr)
        {
            std::cout << i.Name << std::endl;
        }
    }

    void test_control()
    {
        printTestLine("Faction Control Tests");

        FactionManager testFaction = FactionManager(FactionDTO { "Test" } );

        printTestLine("Create test control");
        std::unique_ptr<FactionControl> testControl(new FactionControl() );
        std::cout << "Control size: " << sizeof(*testControl) << "\n\n";

        {
            printTestLine("Add test faction to control");
            testControl->AddFaction(testFaction);
            printTestLine("Show faction list size");
            std::cout << "List size: " << testControl->GetMapSize() << std::endl;
            printTestLine("Show faction list");
            printList(testControl->GetFactionList() );
            std::cout << std::endl;
        }

        {
            printTestLine("Remove faction from control");
            testControl->RemoveFaction("Test");
            printTestLine("Show faction list");
            std::cout << "Faction list:\n";
            printList(testControl->GetFactionList() );
            std::cout << std::endl;
        }

        {
            printTestLine("Add a large amount of factions to the map");
            int test_count = 1000;
            for(int i = 0; i < test_count; i++)
            {
                std::string name = "Test" + std::to_string(i);
                std::unique_ptr<FactionDTO> tmp = std::unique_ptr<FactionDTO>(new FactionDTO { name });
                testControl->AddFaction(*tmp);
            }
            std::cout << "List size: " << testControl->GetMapSize() << "\n\n";
        }

        {
            printTestLine("Clear faction list");
            testControl->ClearMap();
            std::cout << "List size: " << testControl->GetMapSize() << "\n\n";
        }

        {
            printTestLine("Add test faction to control");
            testControl->AddFaction(testFaction);
            printTestLine("Show faction list");
            printList(testControl->GetFactionList() );
            std::cout << std::endl;
        }

        {
            printTestLine("Add a large amount of assets to one faction");
            AssetList assetList = testControl->GetAssetList("Test");
            int test_count = 1000000;
            for(int i = 0; i < test_count; i++)
            {
                std::string name = "Test" + std::to_string(i);
                std::unique_ptr<AssetDTO> tmp = std::unique_ptr<AssetDTO>(new AssetDTO { name });
                testControl->AddAsset(assetList, *tmp);
            }
            std::cout << "List size: " << testControl->GetMapSize() << std::endl;
            std::cout << "Asset list size: " << testControl->GetAssetList("Test").size() << "\n\n";
        }

        printTestDivider('=', "\n\n");
    }

    void test_factionmanager()
    {
        printTestLine("Faction manager tests");

        FactionDTO testFaction { "Test" };

        printTestLine("Create test faction manager");
        std::unique_ptr<FactionManager> testManager = std::unique_ptr<FactionManager>(new FactionManager(testFaction) );
        std::cout << "Faction manager size: " << sizeof(*testManager) << "\n\n";

        printTestDivider('=', "\n\n");
    }

    void test_faction()
    {
        printTestLine("Faction struct tests");

        printTestLine("Create test faction");
        FactionDTO testFaction { "Test" };
        std::cout << "Faction name: " << testFaction.Name << std::endl;
        std::cout << "Faction struct size: " << sizeof(testFaction) << "\n\n";

        printTestDivider('=', "\n\n");
    }

    void test_asset()
    {
        printTestLine("Asset struct tests");

        printTestLine("Create test asset");
        AssetDTO testAsset { "Test", "Force", 1, "Special Forces", { 1, 4, 0 }, "Force", { 1, 4, 0 }, 0, 1, 5, 5 };
        std::cout << "Asset name: " << testAsset.Name << std::endl;
        std::cout << "Asset struct size: " << sizeof(testAsset) << "\n\n";

        {
            printTestLine("Serialize test struct");
            std::ofstream file("out.json");
            cereal::JSONOutputArchive farchive(file);
            cereal::JSONOutputArchive parchive(std::cout);
            farchive(cereal::make_nvp("Asset", testAsset) );
            parchive(cereal::make_nvp("Asset", testAsset) );
        }
        std::cout << "\n\n";

        {
            printTestLine("Deserialize test struct");
            std::ifstream file("out.json");
            cereal::JSONInputArchive archive(file);
            AssetDTO tmp;
            archive(tmp);
            cereal::JSONOutputArchive parchive(std::cout);
            parchive(cereal::make_nvp("Asset", tmp) );
        }
        std::cout << "\n\n";

        {
            printTestLine("Test dice roll");
            setup_basic_randomizer();

            for(int i = 0; i < 5; i++)
            {
                std::cout << "Attack roll " << to_string(testAsset.Attack) << ": " << roll_dice(testAsset.Attack) << std::endl;
            }
        }
        std::cout << "\n\n";

        printTestDivider('=', "\n\n");
    }
}

#endif
