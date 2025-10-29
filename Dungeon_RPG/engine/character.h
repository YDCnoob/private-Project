
#ifndef CHARACTER_H
#define CHARACTER_H

#include "skill.h"

typedef struct CHARACTER {
    char name[50];
    char job[20];
    int level;
    int hp, max_hp;
    int strength, agility, intelligence, luck;
    int exp, gold;
    int weapondmg, weaponup;
    int isNight;
    int defense, evasion, evadeTurns;
    struct SKILL skills[3];
} CHARACTER;

void CreateCharacter(CHARACTER* c);
void PrintCharacterStat(CHARACTER* c);
void levelUp(CHARACTER* c);
void promoteCharacter(CHARACTER* c);
void SetWarrior(CHARACTER* c);
void SetArcher(CHARACTER* c);
void SetMage(CHARACTER* c);
void SetRogue(CHARACTER* c);

#endif
