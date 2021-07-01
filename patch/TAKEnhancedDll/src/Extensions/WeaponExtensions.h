#pragma once
#include "Context.h"
#include "Unit.h"
#include "WeaponExtension.h"

std::map<Weapon*, WeaponExtension> weaponsMap;

extern "C" __declspec(dllexport) void __stdcall WeaponOnHitPropertiesExtension()
{    
    std::map<Weapon*, WeaponExtension>::iterator it;

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
    
    unit->currentHealth += it->second.lifesteal * damageDealt;
}

extern "C" __declspec(dllexport) void __stdcall LoadWeaponPropertiesExtension()
{
    // weaponsMap...
}


void WeaponExtensionPatch()
{
    // weapons = ?

    // MemoryHandling::insertFunctionCall(&WeaponExtension, ...);
}