
#include "engine.h"

void printCritMessage(const char* attacker, const char* target, int isPlayer) {
    textcolor(isPlayer ? RED : DarkRed);
    printf(">> %s의 공격이 %s의 급소에 적중했다! <<\n", attacker, target);
    textcolor(WHITE);
}

int calculateDamage(CHARACTER* c, int* isCrit) {
    int base = 5;
    double mul = 1.0
        + sqrt((double)c->strength) * 1.2
        + sqrt((double)c->agility) * 1.0
        + sqrt((double)c->intelligence) * 0.9
        + sqrt((double)c->luck) * 0.8
        + (double)c->weapondmg;
    int damage = (int)(base * mul);
    if (isCrit) {
        int chance = 5 + (int)(c->luck * 0.75);
        *isCrit = (rand() % 100) < chance;
        if (*isCrit) damage = (int)(damage * 1.3);
    }
    return damage;
}

void applyStatusEffects(MOP* m) {
    if (m->isStunned && m->stunTurns > 0) {
        printf(">> %s는 기절 상태로 행동 불가! (남은 턴: %d)\n", m->name, m->stunTurns);
        m->stunTurns--;
        if (m->stunTurns == 0) { m->isStunned = 0; printf(">> %s의 기절이 풀렸습니다.\n", m->name); }
        return;
    }
    if (m->isFrozen && m->freezeTurns > 0) {
        printf(">> %s는 얼어붙어 움직일 수 없다! (남은 턴: %d)\n", m->name, m->freezeTurns);
        m->freezeTurns--;
        if (m->freezeTurns == 0) { m->isFrozen = 0; printf(">> %s의 빙결 해제.\n", m->name); }
        return;
    }
    if (m->isPoisoned && m->poisonTurns > 0) {
        int poisonDmg = 5;
        m->hp = clampHP(m->hp - poisonDmg);
        printf(">> %s는 중독으로 %d 피해! (HP: %d)\n", m->name, poisonDmg, m->hp);
        m->poisonTurns--;
        if (m->poisonTurns == 0) { m->isPoisoned = 0; printf(">> %s의 중독 해제.\n", m->name); }
    }
    if (m->isBleeding && m->bleedTurns > 0) {
        int bleedDmg = 7;
        m->hp = clampHP(m->hp - bleedDmg);
        printf(">> %s는 출혈로 %d 피해! (HP: %d)\n", m->name, bleedDmg, m->hp);
        m->bleedTurns--;
        if (m->bleedTurns == 0) { m->isBleeding = 0; printf(">> %s의 출혈 종료.\n", m->name); }
    }
}

int enterDungeon(int* dun_lev, CHARACTER* character, MOP* mop) {
    resetMop(mop, *dun_lev, character->isNight);
    textcolor(WHITE);
    printf("던전 깊은 곳으로 내려가는 중... (Press any key)\n");
    (void)_getch();
    return 1;
}

static void playerTurn(CHARACTER* c, MOP* m) {
    if ((rand()%100) < 30) {
        int idx = rand() % MAX_SKILLS;
        SKILL* sk = &c->skills[idx];
        textcolor(SkyBlue);
        printf("★ 스킬 발동! [%s] ★\n", sk->name);
        textcolor(WHITE);
        sk->effect(c, m);
        Sleep(200);
        return;
    }
    int isCrit = 0;
    int dmg = calculateDamage(c, &isCrit);
    if (isCrit) printCritMessage(c->name, m->name, 1);
    m->hp = clampHP(m->hp - dmg);
    printf("%s에게 %d의 데미지! (남은 체력: %d)\n", m->name, dmg, m->hp);
}

static void monsterTurn(CHARACTER* c, MOP* m) {
    if (c->evadeTurns > 0) {
        c->evadeTurns--;
        textcolor(GREEN);
        printf("<< 연막 효과로 %s는 완벽히 회피! >> (남은 턴: %d)\n", c->name, c->evadeTurns);
        textcolor(WHITE);
        return;
    }
    int evade = rand()%100;
    if (evade < c->evasion) {
        textcolor(GREEN);
        printf("%s의 공격을 %s가 회피!\n", m->name, c->name);
        textcolor(WHITE);
        return;
    }
    int mobCrit = (rand()%100) < 10;
    double critMul = mobCrit ? 1.2 : 1.0;
    int raw = (int)(m->dam * critMul);
    int dmg = raw - c->defense; if (dmg < 0) dmg = 0;
    if (mobCrit) printCritMessage(m->name, c->name, 0);
    c->hp = clampHP(c->hp - dmg);
    printf("%s(이/가) %s에게 %d 데미지! (남은 체력: %d)\n", m->name, c->name, dmg, c->hp);
}

void fightmop(CHARACTER* character, MOP* mop, int* dun_lev) {
    for (int i = 0; i < 3; i++) {
        textcolor(RED);
        printf("%s(이/가) 나타났다! 싸우겠습니까? (Y/n) ", mop[i].name);
        textcolor(WHITE);
        char choice = _getch(); printf("\n");
        if (choice=='n' || choice=='N') { printf("%s(을/를) 회피했습니다..\n", mop[i].name); continue; }
        printf("%s와 전투 시작!\n\n", mop[i].name);
        Sleep(200);

        while (mop[i].hp > 0 && character->hp > 0) {
            applyStatusEffects(&mop[i]);
            if (mop[i].hp <= 0) break;

            playerTurn(character, &mop[i]);
            if (mop[i].hp <= 0) {
                textcolor(YELLOW);
                printf("\n%s를 처치했다!\n", mop[i].name);
                character->exp += mop[i].exp;
                character->gold += mop[i].reward_gold;
                printf("%d EXP, %d GOLD 획득!\n\n", mop[i].exp, mop[i].reward_gold);
                textcolor(WHITE);
                waitForKeyPress();
                levelUp(character);
                break;
            }

            monsterTurn(character, &mop[i]);
            if (clampAndCheckDeath(&character->hp)) {
                printf("%s(이/가) 사망했습니다... 게임 오버!\n", character->name);
                SaveRanking(character, *dun_lev);
                exit(0);
            }
            Sleep(300);
        }
    }
}

void fightBoss(CHARACTER* character, MOP* boss, int* dun_lev) {
    textcolor(RED);
    printf("%s(이/가) 나타났다! 싸우겠습니까? (Y/n) ", boss->name);
    textcolor(WHITE);
    char choice = _getch(); printf("\n");
    if (choice=='n' || choice=='N') { printf("%s(을/를) 회피했습니다..\n", boss->name); return; }
    printf("%s와 전투 시작!\n\n", boss->name);
    Sleep(200);

    while (boss->hp > 0 && character->hp > 0) {
        applyStatusEffects(boss);
        if (boss->hp <= 0) break;

        playerTurn(character, boss);
        if (boss->hp <= 0) {
            textcolor(YELLOW);
            printf("\n%s를 처치했다!\n", boss->name);
            character->exp += boss->exp;
            character->gold += boss->reward_gold;
            printf("%d EXP, %d GOLD 획득!\n\n", boss->exp, boss->reward_gold);
            textcolor(WHITE);
            waitForKeyPress();
            levelUp(character);
            break;
        }

        monsterTurn(character, boss);
        if (clampAndCheckDeath(&character->hp)) {
            printf("%s(이/가) 사망했습니다... 게임 오버!\n", character->name);
            SaveRanking(character, *dun_lev);
            exit(0);
        }
        Sleep(300);
    }
}

void gameLoop(CHARACTER* character, MOP* mop, int* dun_lev) {
    MOP boss = { "보스 몬스터", 500, 500, 150, 150, 200, 200, 500, 500 };
    while (1) {
        if (!enterDungeon(dun_lev, character, mop)) {
            printf("\n게임을 종료합니다.\n");
            break;
        }
        if (isBossFloor(*dun_lev)) {
            resetBoss(&boss, *dun_lev, character->isNight);
            printf("\n※ 보스 층! %s이(가) 기다립니다! ※\n", boss.name);
            fightBoss(character, &boss, dun_lev);
        } else {
            fightmop(character, mop, dun_lev);
        }

        char next;
        resetMop(mop, *dun_lev, character->isNight);
        printf("%d층 클리어!! 다음 층으로 이동(y) / 마을로 귀환(n)? ", *dun_lev);
        scanf_s(" %c", &next, 1);
        while (getchar()!='\n');
        if (next=='y' || next=='Y') (*dun_lev)++;
        else {
            enterTown(character, dun_lev);
            printf("귀환중...\n"); Sleep(300);
        }
    }
}
