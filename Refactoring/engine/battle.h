
#ifndef BATTLE_H
#define BATTLE_H

#include "character.h"
#include "monster.h"

void gameLoop(struct CHARACTER* character, struct MOP* mop, int* dun_lev);
int enterDungeon(int* dun_lev, struct CHARACTER* character, struct MOP* mop);
void fightmop(struct CHARACTER* character, struct MOP* mop, int* dun_lev);
void fightBoss(struct CHARACTER* character, struct MOP* boss, int* dun_lev);

int calculateDamage(struct CHARACTER* character, int* isCrit);
void applyStatusEffects(struct MOP* m);
void printCritMessage(const char* attacker, const char* target, int isPlayer);

#endif
