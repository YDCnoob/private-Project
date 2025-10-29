
#include "engine.h"

void upgrade_weapon(CHARACTER* character) {
    const int upgrade_cost = 100;
    const int max_weaponup = 99;
    const int base_success_rate = 100;
    const int decrease_per_level = 5;
    const int min_success_rate = 40;

    if (character->gold < upgrade_cost) {
        printf("현재 소지 금액: %dG\n골드가 부족합니다. 강화 불가.\n\n", character->gold);
        return;
    }
    if (character->weaponup >= max_weaponup) {
        printf("강화 제한 도달. 최대 +%d\n\n", max_weaponup);
        return;
    }
    character->gold -= upgrade_cost;

    int current_level = character->weaponup;
    int success_rate = (current_level < 10)
        ? base_success_rate
        : base_success_rate - (current_level - 9) * decrease_per_level;
    if (success_rate < min_success_rate) success_rate = min_success_rate;

    int roll = rand()%100;
    if (roll < success_rate) {
        character->weaponup++;
        character->weapondmg += (current_level < 10) ? 2 : 3;
        printf("강화 성공! 무기 데미지 %s 증가. [+%d]\n\n",
            (current_level < 10) ? "+2" : "+3", character->weaponup);
    } else {
        printf("강화 실패... (현재 +%d)\n\n", character->weaponup);
    }
}

void inn(CHARACTER* character) {
    int choice;
    printf("1. 체력 회복\n2. 시간 변경 (낮/밤)\n선택: ");
    scanf_s("%d",&choice); (void)getchar();
    if (choice==1) {
        character->hp = character->max_hp;
        printf("체력 전부 회복.\n");
    } else if (choice==2) {
        Sleep(300);
        character->isNight = !(character->isNight);
        if (character->isNight) printf("밤이 되었습니다. 몬스터들이 흉포해집니다.\n");
        else printf("낮이 되었습니다. 몬스터들이 약해집니다.\n");
    } else {
        printf("잘못된 선택.\n");
    }
}

void blacksmith(CHARACTER* character) {
    int choice;
    printf("1. 무기 강화\n2. 무기 상태 보기\n선택: ");
    scanf_s("%d",&choice);
    if (choice==1) upgrade_weapon(character);
    else if (choice==2) {
        printf("현재 무기 데미지: %d\n무기 강화 상태: +%d\n", character->weapondmg, character->weaponup);
    } else printf("잘못된 선택.\n");
}

void enterTown(CHARACTER* character, int* dun_lev) {
    int choice;
    printf("\n현재 진행 중인 던전 층: %d층\n", *dun_lev);
    while (1) {
        printf("1. 여관 (체력 회복)\n2. 대장간 (무기 강화)\n3. 던전 탐험\n4. 상태 보기\n5. 게임 종료\n6. 게임 저장\n선택: ");
        while (scanf_s("%d",&choice)!=1 || choice<1 || choice>6) {
            (void)getchar(); printf("잘못된 선택. 다시: ");
        }
        switch (choice) {
            case 1: inn(character); break;
            case 2: blacksmith(character); break;
            case 3: return;
            case 4: PrintCharacterStat(character); break;
            case 5: printf("게임 종료.\n"); SaveRanking(character, *dun_lev); exit(0);
            case 6: saveGame(character, *dun_lev); printf("저장 완료!\n"); break;
            default: printf("잘못된 선택.\n"); break;
        }
    }
}
