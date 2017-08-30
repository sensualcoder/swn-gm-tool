#include <string>

#include "Asset.hpp"
#include "AssetManager.hpp"
#include "Faction.hpp"
#include "FactionManager.hpp"
#include "Planet.hpp"
#include "SectorGen.hpp"

#include "Tests.hpp"
#include "FactionControl_Tests.hpp"
#include "SectorGen_Tests.hpp"

using namespace SwnGmTool;

void runAllTests()
{
    Tests::printTestHeader("Faction Control Tests");
    Tests::test_struct<Asset>("Asset");
    Tests::test_struct<Faction>("Faction");
    Tests::test_manager<Asset>(new AssetManager, "AssetManager");
    Tests::test_manager<Faction>(new FactionManager, "FactionManager");

    Tests::printTestHeader("Sector Generator Tests");
    Tests::test_hexelement<HexElement>("HexElement");
    Tests::test_hexelement<Planet>("Planet");
    Tests::test_map<HexElement>(new Map<HexElement>(), "Map");
}

int main(int argc, char* argv[])
{
    runAllTests();

    return 0;
}
