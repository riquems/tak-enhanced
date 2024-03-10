#include "TAKEnhancedDll/Hooks/WeaponsHook.hpp"
#include "TAKEnhancedDll/Memory/MemoryHandler.hpp"
#include <TAKCore/Models/Unit.h>
#include <TAKEnhancedDll/Wrappers/WeaponWrapper.h>

//std::unordered_map<Weapon*, WeaponExtension> weaponsMap;

__declspec(dllexport) void __stdcall WeaponOnHitPropertiesHook()
{    
    /*std::map<Weapon*, WeaponExtension>::iterator it;

    DWORD weaponAddr = 0;

    it = std::find_if(weaponsMap.begin(), weaponsMap.end(), 
        [&weaponAddr](const std::pair<Weapon*, WeaponExtension> p) { 
            return (DWORD) p.first == weaponAddr;
        });

    if (it == weaponsMap.end()) {
        return;
    }

    Unit* unit;
    int damageDealt = 0;
    
    unit->currentHealth += it->second.lifesteal * damageDealt;*/
}

__declspec(dllexport) void __stdcall LoadWeaponPropertiesHook()
{
    // weaponsMap...
}


void WeaponsHook()
{
    // weapons = ?

    // MemoryHandler::insertFunctionCall(&WeaponExtension, ...);
}