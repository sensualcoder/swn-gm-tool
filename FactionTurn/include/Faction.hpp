#ifndef FACTION_HPP
#define FACTION_HPP

#include <cstdint>
#include <map>

#include "Asset.hpp"
#include "Events.hpp"
#include "FactionCreateModel.hpp"
#include "FactionModel.hpp"
#include "Subject.hpp"

namespace FT
{
    using FactionCreateModel = SwnGmTool::FactionCreateModel;
    using FactionModel = SwnGmTool::FactionModel;

    // Enums, structs, const values and objects
    
    // TODO: Make into a configurable object that is loaded in from a file
    const std::map<int, int> RatingHpMap
    {
        {1, 1},
        {2, 2},
        {3, 4},
        {4, 6},
        {5, 9},
        {6, 12},
        {7, 16},
        {8, 20}
    };

    // Helper methods
    uint8_t CalcHp(uint8_t force, uint8_t cunning, uint8_t wealth);
    uint8_t CalcIncome(uint8_t force, uint8_t cunning, uint8_t wealth);

    // Class definition
    /** Faction
     */
    class Faction : public Subject
    {
        public:
            Faction(const FactionCreateModel& faction);
            Faction(const FactionModel& faction);

            void Attack(Asset& target);
            void BuyAsset(const AssetModel& asset);
            void ChangeHomeworld();
            void ExpandInfluence();
            void RefitAsset(Asset& asset, const Asset& refitTo);
            void Repair(Asset& target);
            void Repair(Faction& target);
            void Sell(Asset& asset);
            void SeizePlanet();
            void UseAssetAbility(Asset& asset);

            void TakeDamage(unsigned int damage); 

            const FactionModel& GetModel() const;

            inline bool operator==(const FactionCreateModel& b) const
            {
                return(this->Model.Name == b.Name
                    && this->Model.Force == b.Force
                    && this->Model.Cunning == b.Cunning
                    && this->Model.Wealth == b.Wealth);
            }

            inline bool operator==(const FactionModel& b) const
            {
                return(this->Model == b);
            }

            inline bool operator==(const Faction& b) const
            {
                return(this->Model == b.GetModel() );
            }

        private:
            FactionModel Model;
            std::vector<Asset> AssetList;

            // TODO:
            // Add Homeworld
            // Add list of Planets with bases
    };
}

#endif // FACTION_HPP
