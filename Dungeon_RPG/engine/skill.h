
#ifndef SKILL_H
#define SKILL_H

struct CHARACTER;
struct MOP;

typedef void (*SkillEffect)(struct CHARACTER*, struct MOP*);

typedef struct SKILL {
    char name[30];
    char description[100];
    int mp_cost;
    double damage_multiplier;
    SkillEffect effect;
} SKILL;

// Warrior
void smash(struct CHARACTER*, struct MOP*);
void shield_bash(struct CHARACTER*, struct MOP*);
void rage_strike(struct CHARACTER*, struct MOP*);

// Archer
void rapid_shot(struct CHARACTER*, struct MOP*);
void poison_arrow(struct CHARACTER*, struct MOP*);
void critical_shot(struct CHARACTER*, struct MOP*);

// Mage
void fireball(struct CHARACTER*, struct MOP*);
void ice_arrow(struct CHARACTER*, struct MOP*);
void drain_life(struct CHARACTER*, struct MOP*);

// Rogue
void shadow_strike(struct CHARACTER*, struct MOP*);
void smoke_bomb(struct CHARACTER*, struct MOP*);
void bleed(struct CHARACTER*, struct MOP*);

#endif
