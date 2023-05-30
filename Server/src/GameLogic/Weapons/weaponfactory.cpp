// #include "../../../include/GameLogic/Weapons/weaponfactory.h"

// std::unique_ptr<Weapon> WeaponFactory::create(uint8_t weapon_type) {
//     switch(weapon_type) {
//         case P90WEAPON: {
//             return std::unique_ptr<Weapon> (new P90Weapon(P90_AMMO, P90_DAMAGE));
//         }
//         case SCOUTWEAPON: {
//             return std::unique_ptr<Weapon> (new IdfWeapon(SCOUT_AMMO, SCOUT_DAMAGE));
//         }
//         case IDFWEAPON: {
//             return std::unique_ptr<Weapon> (new ScoutWeapon(IDF_AMMO, IDF_DAMAGE));
//         }
//     }
//     return std::unique_ptr<Weapon>(nullptr);
// }
