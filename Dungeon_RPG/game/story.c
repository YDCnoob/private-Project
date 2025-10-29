
#include "../engine/engine.h"
#include "story.h"

void showIntro() {
    textcolor(YELLOW);
    printf("==== 던전의 시작 ====\n");
    printf("당신은 어둠 속의 모험을 시작합니다...\n");
    textcolor(WHITE);
    waitForKeyPress();
}

void showMainMenu(CHARACTER* character, MOP* mop, int* dun_lev) {
    int choice;
    while (1) {
        textcolor(YELLOW);
        printf("==== 텍스트 RPG ====\n");
        printf("1. New Game\n");
        printf("2. Load Game\n");
        printf("3. Ranking\n");
        printf("4. Exit\n");
        printf("====================\n");
        textcolor(WHITE);
        printf("선택: ");
        scanf_s("%d",&choice);

        switch (choice) {
            case 1:
                CreateCharacter(character);
                enterTown(character, dun_lev);
                gameLoop(character, mop, dun_lev);
                return;
            case 2:
                if (loadGame(character, dun_lev)) {
                    printf("게임을 불러왔습니다!\n");
                    PrintCharacterStat(character);
                    enterTown(character, dun_lev);
                    gameLoop(character, mop, dun_lev);
                } else {
                    printf("저장된 게임이 없습니다.\n");
                }
                break;
            case 3:
                printTopRanking();
                break;
            case 4:
                printf("게임 종료.\n");
                exit(0);
            default:
                printf("잘못된 선택입니다.\n");
        }
    }
}
