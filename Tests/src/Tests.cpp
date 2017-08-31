#include "Tests.hpp"

#include "FactionManager.hpp"
#include "SectorGen.hpp"

#include "FactionControl_Tests.hpp"
#include "SectorGen_Tests.hpp"
#include "TestHelpers.hpp"

namespace Tests
{
    void runFactionControlTests()
    {
        printTestHeader("Faction Control Tests");

        test_struct<Asset>("Asset");
        test_struct<Faction>("Faction");
        test_manager<Asset>(new AssetManager, "AssetManager");
        test_manager<Faction>(new FactionManager, "FactionManager");
    }

    void runSectorGenTests()
    {
        printTestHeader("Sector Generator Tests");

        test_hexelement<Planet>("Planet");
        test_hex<Planet>("Planet");
        test_map<Planet>("Planet Map");
        test_mapgen<SectorGen>("SectorGen");
    }

    void runAllTests()
    {
        runFactionControlTests();
        runSectorGenTests();
    }
}