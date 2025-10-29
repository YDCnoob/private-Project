
#include "engine.h"

static int baseDamage(struct CHARACTER* c, double mult, int allowCrit) {
    int isCrit = 0;
    int d = (int)(calculateDamage(c, allowCrit ? &isCrit : NULL) * mult);
    return d;
}

// Warrior
void smash(struct CHARACTER* c, struct MOP* m) {
    int damage = baseDamage(c, 1.2, 1);
    m->hp = clampHP(m->hp - damage);
    printf("[강타] %s에게 %d 데미지!\n", m->name, damage);
}

void shield_bash(struct CHARACTER* c, struct MOP* m) {
    int damage = baseDamage(c, 1.0, 0);
    m->hp = clampHP(m->hp - damage);
    m->isStunned = 1; m->stunTurns = 1;
    printf("[방패 밀치기] %s에게 %d 데미지! (기절)\n", m->name, damage);
}

void rage_strike(struct CHARACTER* c, struct MOP* m) {
    int missing_hp = c->max_hp - c->hp;
    int bonus = (int)(missing_hp * 0.2);
    int damage = calculateDamage(c, NULL) + bonus;
    m->hp = clampHP(m->hp - damage);
    printf("[분노의 일격] %s에게 %d 데미지! (보너스 %d)\n", m->name, damage, bonus);
}

// Archer
void rapid_shot(struct CHARACTER* c, struct MOP* m) {
    for (int i = 0; i < 2; ++i) {
        int damage = baseDamage(c, 0.7, 0);
        m->hp = clampHP(m->hp - damage);
        printf("[연속 사격] %s에게 %d 데미지!\n", m->name, damage);
    }
}
void poison_arrow(struct CHARACTER* c, struct MOP* m) {
    int damage = baseDamage(c, 1.0, 0);
    m->hp = clampHP(m->hp - damage);
    m->isPoisoned = 1; m->poisonTurns = 3;
    printf("[독화살] %s에게 %d 데미지! (중독 3턴)\n", m->name, damage);
}
void critical_shot(struct CHARACTER* c, struct MOP* m) {
    int isCrit = (rand() % 100) < 80;
    int damage = calculateDamage(c, NULL);
    if (isCrit) damage = (int)(damage * 1.3);
    m->hp = clampHP(m->hp - damage);
    printf("[치명 사격] %s에게 %d 데미지!\n", m->name, damage);
}

// Mage
void fireball(struct CHARACTER* c, struct MOP* m) {
    int damage = baseDamage(c, 1.5, 0);
    m->hp = clampHP(m->hp - damage);
    printf("[파이어볼] %s에게 %d 데미지!\n", m->name, damage);
}
void ice_arrow(struct CHARACTER* c, struct MOP* m) {
    int damage = baseDamage(c, 1.0, 0);
    m->hp = clampHP(m->hp - damage);
    m->isFrozen = 1; m->freezeTurns = 1;
    printf("[얼음 화살] %s에게 %d 데미지! (빙결 1턴)\n", m->name, damage);
}
void drain_life(struct CHARACTER* c, struct MOP* m) {
    int damage = baseDamage(c, 1.0, 0);
    int heal = damage / 2;
    m->hp = clampHP(m->hp - damage);
    c->hp += heal; if (c->hp > c->max_hp) c->hp = c->max_hp;
    printf("[체력 흡수] %s에게 %d 데미지, %d 회복!\n", m->name, damage, heal);
}

// Rogue
void shadow_strike(struct CHARACTER* c, struct MOP* m) {
    int isCrit = (rand() % 100) < 70;
    int damage = calculateDamage(c, NULL);
    if (isCrit) damage = (int)(damage * 1.2);
    m->hp = clampHP(m->hp - damage);
    printf("[그림자 일격] %s에게 %d 데미지!\n", m->name, damage);
}
void smoke_bomb(struct CHARACTER* c, struct MOP* m) {
    (void)m;
    c->evadeTurns = 2;
    printf("[연막] %s가 2턴 동안 모든 공격 회피!\n", c->name);
}
void bleed(struct CHARACTER* c, struct MOP* m) {
    int damage = baseDamage(c, 1.0, 0);
    m->hp = clampHP(m->hp - damage);
    m->isBleeding = 1; m->bleedTurns = 3;
    printf("[치명 상처] %s에게 %d 데미지! (출혈 3턴)\n", m->name, damage);
}
