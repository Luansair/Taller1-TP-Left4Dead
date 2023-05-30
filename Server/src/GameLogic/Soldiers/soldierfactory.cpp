#include "../../../include/GameLogic/Soldiers/soldierfactory.h"

std::unique_ptr<Soldier> SoldierFactory::create(uint8_t soldier_type) {
    switch(soldier_type) {
        case P90SOLDIER: {
            std::unique_ptr<Weapon> weapon(new P90Weapon(P90_AMMO, P90_DAMAGE));
            std::unique_ptr<Grenade> grenade(new AerialGrenade(10,10,10));
            return std::unique_ptr<Soldier> (new P90Soldier(P90SOLDIERHEALTH, std::move(weapon), std::move(grenade)));
        }
        case SCOUTSOLDIER: {
            std::unique_ptr<Weapon> weapon(new ScoutWeapon(SCOUT_AMMO, SCOUT_DAMAGE));
            std::unique_ptr<Grenade> grenade(new ExplosiveGrenade(10,10,10));
            return std::unique_ptr<Soldier> (new ScoutSoldier(SCOUTSOLDIERHEALTH, std::move(weapon), std::move(grenade)));
        }
        case IDFSOLDIER: {
            std::unique_ptr<Weapon> weapon(new IdfWeapon(IDF_AMMO, IDF_DAMAGE));
            std::unique_ptr<Grenade> grenade(new ExplosiveGrenade(10,10,10));
            return std::unique_ptr<Soldier> (new IdfSoldier(IDFSOLDIERHEALTH, std::move(weapon), std::move(grenade)));
        }
    }
    return std::unique_ptr<Soldier>(nullptr);
}

// std::unique_ptr<Soldier> SoldierFactory::create(uint8_t soldier_type) {
//     WeaponFactory wfactory;
//     switch(soldier_type) {
//         case P90SOLDIER: {
//             std::unique_ptr<Grenade> grenade(new AerialGrenade(10,10,10));
//             return std::unique_ptr<Soldier> (new P90Soldier(P90SOLDIERHEALTH, std::move(wfactory.create(soldier_type)), std::move(grenade)));
//         }
//         case SCOUTSOLDIER: {
//             std::unique_ptr<Grenade> grenade(new ExplosiveGrenade(10,10,10));
//             return std::unique_ptr<Soldier> (new ScoutSoldier(SCOUTSOLDIERHEALTH, std::move(wfactory.create(soldier_type)), std::move(grenade)));
//         }
//         case IDFSOLDIER: {
//             std::unique_ptr<Grenade> grenade(new ExplosiveGrenade(10,10,10));
//             return std::unique_ptr<Soldier> (new IdfSoldier(IDFSOLDIERHEALTH, std::move(wfactory.create(soldier_type)), std::move(grenade)));
//         }
//     }
//     return std::unique_ptr<Soldier>(nullptr);
// }
