
#ifndef MONSTER_H
#define MONSTER_H

typedef struct MOP {
    char name[50];
    int base_hp, hp;
    int basDam, dam;
    int base_exp, exp;
    int base_gold, reward_gold;

    int isPoisoned, poisonTurns;
    int isBleeding, bleedTurns;
    int isStunned, stunTurns;
    int isFrozen, freezeTurns;
} MOP;

void resetMop(MOP* m, int difficulty, int isNight);
int isBossFloor(int level);
void resetBoss(MOP* boss, int level, int isNight);

#endif
