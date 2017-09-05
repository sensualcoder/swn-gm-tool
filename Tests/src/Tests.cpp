#include "Tests.hpp"

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
        test_asset();
        test_struct<Faction>("Faction");
        test_control();
    }

    void runSectorGenTests()
    {
        printTestHeader("Sector Generator Tests");

        test_hexelement<Planet>("Planet");
        test_hex<HexElement, HexGrid::Hex>("Hex");
        test_hex<Planet, HexGrid::Hex>("Planet");
        test_map<HexElement>("Hex Map");
        test_map<Planet>("Planet Map");
        test_mapgen<MapGen>("MapGen");
        test_mapgen<SectorGen>("SectorGen");
    }

    void runAllTests()
    {
        runFactionControlTests();
        runSectorGenTests();
    }
}