
#include "engine.h"

void resetMop(MOP* mop, int difficulty, int isNight) {
    int effective_difficulty = (difficulty > 50) ? 50 : difficulty;
    for (int i = 0; i < 3; i++) {
        mop[i].hp = mop[i].base_hp + effective_difficulty * 30;
        mop[i].dam = mop[i].basDam + effective_difficulty * 3;
        mop[i].exp = mop[i].base_exp;
        mop[i].reward_gold = mop[i].base_gold;

        mop[i].isPoisoned = mop[i].poisonTurns = 0;
        mop[i].isBleeding = mop[i].bleedTurns = 0;
        mop[i].isStunned = mop[i].stunTurns = 0;
        mop[i].isFrozen  = mop[i].freezeTurns = 0;

        if (isNight) {
            mop[i].hp = (int)(mop[i].hp * NIGHT_HP_MULT);
            mop[i].dam = (int)(mop[i].dam * NIGHT_DAM_MULT);
            mop[i].exp = (int)(mop[i].exp * NIGHT_EXP_MULT);
            mop[i].reward_gold = (int)(mop[i].reward_gold * NIGHT_GOLD_MULT);
        }
    }
}

int isBossFloor(int dun_lev) { return dun_lev % 5 == 0; }

void resetBoss(MOP* boss, int level, int isNight) {
    const char* bossNames[] = { "슬라임 킹", "임프 군주", "고블린 장군", "오우거", "드래곤" };
    int index = (level / 5 - 1); if (index < 0) index = 0;
    strcpy(boss->name, bossNames[index % 5]);

    boss->base_hp = 500; boss->basDam = 150; boss->base_exp = 200; boss->base_gold = 500;
    boss->hp = boss->base_hp + level * 50;
    boss->dam = boss->basDam + level * 5;
    boss->exp = boss->base_exp + level * 10;
    boss->reward_gold = boss->base_gold + level * 20;

    boss->isPoisoned = boss->poisonTurns = 0;
    boss->isBleeding = boss->bleedTurns = 0;
    boss->isStunned = boss->stunTurns = 0;
    boss->isFrozen  = boss->freezeTurns = 0;

    if (isNight) {
        boss->hp = (int)(boss->hp * NIGHT_HP_MULT);
        boss->dam = (int)(boss->dam * NIGHT_DAM_MULT);
        boss->exp = (int)(boss->exp * NIGHT_EXP_MULT);
        boss->reward_gold = (int)(boss->reward_gold * NIGHT_GOLD_MULT);
    }
}
