#include "../../../include/GameLogic/Soldiers/soldierfactory.h"

std::shared_ptr<Soldier> SoldierFactory::create(uint32_t soldier_id, uint8_t soldier_type) {
    WeaponFactory wpfactory;
    GrenadeFactory gfactory;
    switch(soldier_type) {
        case P90SOLDIER: {
            return std::shared_ptr<Soldier> (new P90Soldier(soldier_id, RIGHT, P90SOLDIERWIDTH, P90SOLDIERHEIGTH, P90SOLDIERSPEED, P90SOLDIERHEALTH, std::move(wpfactory.create(P90WEAPON)), std::move(gfactory.create(AERIAL))));
        }
        case SCOUTSOLDIER: {
            return std::shared_ptr<Soldier> (new ScoutSoldier(soldier_id, RIGHT, SCOUTSOLDIERWIDTH,SCOUTSOLDIERHEIGTH,SCOUTSOLDIERSPEED,SCOUTSOLDIERHEALTH, std::move(wpfactory.create(SCOUTWEAPON)), std::move(gfactory.create(EXPLOSIVE))));
        }
        case IDFSOLDIER: {
            return std::shared_ptr<Soldier> (new IdfSoldier(soldier_id, RIGHT,IDFSOLDIERWIDTH,IDFSOLDIERHEIGTH,IDFSOLDIERSPEED,IDFSOLDIERHEALTH, std::move(wpfactory.create(IDFWEAPON)), std::move(gfactory.create(EXPLOSIVE))));
        }
    }
    return std::shared_ptr<Soldier>(nullptr);
}
