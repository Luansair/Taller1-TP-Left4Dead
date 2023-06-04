#include "../../../include/GameLogic/Soldiers/soldierfactory.h"

std::shared_ptr<Soldier> SoldierFactory::create(uint8_t soldier_type) {
    WeaponFactory wpfactory;
    GrenadeFactory gfactory;
    switch(soldier_type) {
        case P90SOLDIER: {
            return std::shared_ptr<Soldier> (new P90Soldier(RIGHT, P90SOLDIERWIDTH, P90SOLDIERHEIGTH, P90SOLDIERSPEED,P90SOLDIERHEALTH, std::move(wpfactory.create(P90WEAPON)), std::move(gfactory.create(AERIAL))));
        }
        case SCOUTSOLDIER: {
            return std::shared_ptr<Soldier> (new ScoutSoldier(RIGHT,1,1,1,SCOUTSOLDIERHEALTH, std::move(wpfactory.create(SCOUTWEAPON)), std::move(gfactory.create(EXPLOSIVE))));
        }
        case IDFSOLDIER: {
            return std::shared_ptr<Soldier> (new IdfSoldier(RIGHT,1,1,1,IDFSOLDIERHEALTH, std::move(wpfactory.create(IDFWEAPON)), std::move(gfactory.create(EXPLOSIVE))));
        }
    }
    return std::shared_ptr<Soldier>(nullptr);
}
