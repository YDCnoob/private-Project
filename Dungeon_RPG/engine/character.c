
#include "engine.h"

static void assignCommon(CHARACTER* c) {
    c->level = 1;
    c->hp = c->max_hp;
    c->exp = 0;
    c->gold = 0;
    c->weapondmg = 0;
    c->weaponup = 0;
    c->isNight = 0;
    c->evadeTurns = 0;
}

void SetWarrior(CHARACTER* c) {
    strcpy(c->job, "전사");
    c->strength = 15; c->agility = 5; c->intelligence = 4; c->luck = 6; c->max_hp = 250;
    strcpy(c->skills[0].name, "강타"); c->skills[0].damage_multiplier = 1.2; c->skills[0].effect = smash;
    strcpy(c->skills[1].name, "방패 밀치기"); c->skills[1].damage_multiplier = 1.0; c->skills[1].effect = shield_bash;
    strcpy(c->skills[2].name, "분노의 일격"); c->skills[2].damage_multiplier = 1.0; c->skills[2].effect = rage_strike;
    c->defense = 40; c->evasion = 10;
}
void SetArcher(CHARACTER* c) {
    strcpy(c->job, "궁수");
    c->strength = 6; c->agility = 15; c->intelligence = 2; c->luck = 7; c->max_hp = 230;
    strcpy(c->skills[0].name, "연속 사격"); c->skills[0].damage_multiplier = 0.7; c->skills[0].effect = rapid_shot;
    strcpy(c->skills[1].name, "독화살"); c->skills[1].damage_multiplier = 1.0; c->skills[1].effect = poison_arrow;
    strcpy(c->skills[2].name, "치명 사격"); c->skills[2].damage_multiplier = 1.3; c->skills[2].effect = critical_shot;
    c->defense = 10; c->evasion = 30;
}
void SetMage(CHARACTER* c) {
    strcpy(c->job, "마법사");
    c->strength = 3; c->agility = 4; c->intelligence = 16; c->luck = 7; c->max_hp = 180;
    strcpy(c->skills[0].name, "파이어볼"); c->skills[0].damage_multiplier = 1.5; c->skills[0].effect = fireball;
    strcpy(c->skills[1].name, "얼음 화살"); c->skills[1].damage_multiplier = 1.0; c->skills[1].effect = ice_arrow;
    strcpy(c->skills[2].name, "체력 흡수"); c->skills[2].damage_multiplier = 1.0; c->skills[2].effect = drain_life;
    c->defense = 10; c->evasion = 10;
}
void SetRogue(CHARACTER* c) {
    strcpy(c->job, "도적");
    c->strength = 3; c->agility = 8; c->intelligence = 4; c->luck = 15; c->max_hp = 210;
    strcpy(c->skills[0].name, "그림자 일격"); c->skills[0].damage_multiplier = 1.2; c->skills[0].effect = shadow_strike;
    strcpy(c->skills[1].name, "연막"); c->skills[1].damage_multiplier = 0.0; c->skills[1].effect = smoke_bomb;
    strcpy(c->skills[2].name, "치명 상처"); c->skills[2].damage_multiplier = 1.0; c->skills[2].effect = bleed;
    c->defense = 10; c->evasion = 40;
}

void CreateCharacter(CHARACTER* c) {
    textcolor(WHITE);
    printf("이름을 입력하세요: ");
    scanf_s("%49s", c->name, (unsigned)sizeof(c->name));
    printf("\n--- 직업 선택 ---\n");
    textcolor(RED);   printf("1. 전사(Warrior)\n");
    textcolor(GREEN); printf("2. 궁수(Archer)\n");
    textcolor(BLUE);  printf("3. 마법사(Mage)\n");
    textcolor(YELLOW);printf("4. 도적(Rogue)\n");
    textcolor(WHITE); printf("선택 (1-4): ");
    int choice = 1; scanf_s("%d", &choice);
    while (getchar()!='\n');
    switch (choice) {
        case 1: SetWarrior(c); break;
        case 2: SetArcher(c); break;
        case 3: SetMage(c); break;
        case 4: SetRogue(c); break;
        default: SetWarrior(c); break;
    }
    assignCommon(c);
    printf("\n캐릭터 생성 완료!\n");
    PrintCharacterStat(c);
}

void PrintCharacterStat(CHARACTER* c) {
    textcolor(YELLOW);
    printf("\n--- 캐릭터 상태 ---\n");
    printf("이름: %s\n직업: %s\n레벨: %d\n체력: %d/%d\n", c->name, c->job, c->level, c->hp, c->max_hp);
    printf("STR %d | AGI %d | INT %d | LUCK %d\n", c->strength, c->agility, c->intelligence, c->luck);
    printf("DEF %d | EVA %d%% | GOLD %d | EXP %d\n", c->defense, c->evasion, c->gold, c->exp);
    printf("현재 시간대: %s\n", c->isNight ? "밤" : "낮");
    textcolor(WHITE);
}

void levelUp(CHARACTER* c) {
    while (c->exp >= 100) {
        c->level++; c->exp -= 100;
        c->max_hp += 10; c->hp = c->max_hp;
        printf("\n레벨업! %d 레벨에 도달했습니다.\n", c->level);

        int stat1 = rand()%4, stat2 = rand()%4;
        while (stat1==stat2) stat2 = rand()%4;
        int* stats[] = { &c->strength, &c->agility, &c->intelligence, &c->luck };
        *stats[stat1] += 2; *stats[stat2] += 2;
        c->defense += 1; c->evasion += 1;

        printf("스탯이 상승했습니다!\n");
        PrintCharacterStat(c);

        if (c->level == 20 || c->level == 40) {
            waitForKeyPress();
            promoteCharacter(c);
        }
    }
}

void promoteCharacter(CHARACTER* c) {
    printf("\n--- 전직 가능! ---\n현재 직업: %s\n", c->job);
    if (c->level == 20) {
        if (strcmp(c->job,"전사")==0) { printf("1. 파이터  2. 페이지\n"); }
        else if (strcmp(c->job,"궁수")==0) { printf("1. 헌터  2. 사수\n"); }
        else if (strcmp(c->job,"마법사")==0) { printf("1. 위자드  2. 클레릭\n"); }
        else if (strcmp(c->job,"도적")==0) { printf("1. 어쌔신  2. 시프\n"); }
        int ch=1; printf("선택: "); scanf_s("%d",&ch);
        if (strcmp(c->job,"전사")==0) strcpy(c->job, ch==1?"파이터":"페이지");
        else if (strcmp(c->job,"궁수")==0) strcpy(c->job, ch==1?"헌터":"사수");
        else if (strcmp(c->job,"마법사")==0) strcpy(c->job, ch==1?"위자드":"클레릭");
        else if (strcmp(c->job,"도적")==0) strcpy(c->job, ch==1?"어쌔신":"시프");
    } else if (c->level == 40) {
        if (strcmp(c->job,"파이터")==0) strcpy(c->job,"크루세이더");
        else if (strcmp(c->job,"페이지")==0) strcpy(c->job,"나이트");
        else if (strcmp(c->job,"헌터")==0) strcpy(c->job,"레인저");
        else if (strcmp(c->job,"사수")==0) strcpy(c->job,"저격수");
        else if (strcmp(c->job,"위자드")==0) strcpy(c->job,"메이지");
        else if (strcmp(c->job,"클레릭")==0) strcpy(c->job,"프리스트");
        else if (strcmp(c->job,"어쌔신")==0) strcpy(c->job,"허밋");
        else if (strcmp(c->job,"시프")==0) strcpy(c->job,"시프마스터");
    }
    printf("전직 완료! 현재 직업: %s\n", c->job);
    PrintCharacterStat(c);
}
