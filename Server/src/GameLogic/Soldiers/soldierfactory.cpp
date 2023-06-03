#include "../../../include/GameLogic/Soldiers/soldierfactory.h"

std::unique_ptr<Soldier> SoldierFactory::create(uint8_t soldier_type) {
    WeaponFactory wpfactory;
    GrenadeFactory gfactory;
    switch(soldier_type) {
        case P90SOLDIER: {
            return std::unique_ptr<Soldier> (new P90Soldier(1,1,1,1,1,1,P90SOLDIERHEALTH, std::move(wpfactory.create(P90WEAPON)), std::move(gfactory.create(AERIAL))));
        }
        case SCOUTSOLDIER: {
            return std::unique_ptr<Soldier> (new ScoutSoldier(1,1,1,1,1,1,SCOUTSOLDIERHEALTH, std::move(wpfactory.create(SCOUTWEAPON)), std::move(gfactory.create(EXPLOSIVE))));
        }
        case IDFSOLDIER: {
            return std::unique_ptr<Soldier> (new IdfSoldier(1,1,1,1,1,1,IDFSOLDIERHEALTH, std::move(wpfactory.create(IDFWEAPON)), std::move(gfactory.create(EXPLOSIVE))));
        }
    }
    return std::unique_ptr<Soldier>(nullptr);
}
