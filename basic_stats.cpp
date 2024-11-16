/*
this is to outline basic stat prio
*/

#include <iostream>
#include <string>

struct statPrio // core stats for characters 
{
    int strengthStat;
    int hasteStat;
    int critStat;
    int versatilityStat;
    int masteryStat;
};

struct ability
{
    std::string ability_name;
    int ability_cooldown;
    std::string ability_description;
    int ability_runicpower;
    int ability_runes;
};

struct items
{
    std::string item_name;
    std::string item_slot;
    int item_level;

    // below are primary and tertiary attributes used in items        

    int item_stamina;               // primary
    int item_strength;              // primary
    int item_agility;               // primary
    int item_intellect;             // primary

    int item_criticalstrike;        // tertiary
    int item_haste;                 // tertiary
    int item_mastery;               // tertiary
    int item_versatility;           // tertiary

    // some items, especially trinkets, have special abilities associated with them other than just raw stats
    std::string effectType; // active or passive
    int effectDamage;
    int effectHeal;
    int effectCooldown;
    int effectDuration;

    // some items have bonuses if the part of a set is complete
    std::string set_name;
    int set_pieceamount;
    bool set_bonus2;
    bool set_bonus4;
    std::string set_bonus2desc;
    std::string set_bonus4desc;
};

