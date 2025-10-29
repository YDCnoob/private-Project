#include "engine.h"
#include <direct.h>     // _mkdir() (Windows)
#include <sys/stat.h>   // struct stat (stat() 함수용)

#define SAVE_DIR "save"
#define RANK_DIR "ranking"

void ensureDirectory(const char* path) {
    struct stat st = {0};
    if (stat(path, &st) == -1) {
        _mkdir(path);
    }
}

void SaveRanking(const CHARACTER* character, int floor) {
    ensureDirectory(RANK_DIR);

    char path[128];
    sprintf(path, "%s/Ranking.txt", RANK_DIR);

    FILE* fp = NULL;
    errno_t err = fopen_s(&fp, path, "a");
    if (!fp) {
        printf("랭킹 저장 실패 (%s)\n", path);
        return;
    }

    char date[20];
    getCurrentDate(date, sizeof(date));
    fprintf(fp, "%s %s %d %s\n", character->name, character->job, floor, date);
    fclose(fp);
}

typedef struct {
    char name[50];
    char job[20];
    int floor;
    char date[20];
} RankEntry;

void printTopRanking() {
    ensureDirectory(RANK_DIR);

    char path[128];
    sprintf(path, "%s/Ranking.txt", RANK_DIR);

    FILE* fp = NULL;
    errno_t err = fopen_s(&fp, path, "r");
    if (!fp) {
        printf("랭킹 파일이 없습니다.\n");
        return;
    }

    RankEntry list[100];
    int count = 0;
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        RankEntry r = {0};
        if (sscanf(line, "%49s %19s %d %19s", r.name, r.job, &r.floor, r.date) == 4) {
            list[count++] = r;
            if (count >= 100) break;
        }
    }
    fclose(fp);

    for (int i = 0; i < count - 1; ++i) {
        for (int j = i + 1; j < count; ++j) {
            if (list[i].floor < list[j].floor) {
                RankEntry t = list[i];
                list[i] = list[j];
                list[j] = t;
            }
        }
    }

    printf("\n==== 랭킹 TOP 10 ====\n");
    for (int i = 0; i < count && i < 10; ++i) {
        printf("%d위: %s (%s) - %d층 - %s\n",
            i + 1, list[i].name, list[i].job, list[i].floor, list[i].date);
    }
}

void saveGame(const CHARACTER* character, int dun_lev) {
    ensureDirectory(SAVE_DIR);

    int slot;
    printf("\n저장할 슬롯 선택 (1~10): ");
    while (scanf_s("%d", &slot) != 1 || slot < 1 || slot > MAX_SLOT) {
        while (getchar() != '\n');
        printf("다시 입력: ");
    }

    char filename[128];
    sprintf(filename, "%s/save_slot%d.dat", SAVE_DIR, slot);

    FILE* fp;
    errno_t err = fopen_s(&fp, filename, "wb");
    if (err || !fp) {
        printf("슬롯 %d 저장 실패\n", slot);
        return;
    }

    fwrite(character, sizeof(CHARACTER), 1, fp);
    fwrite(&dun_lev, sizeof(int), 1, fp);
    fclose(fp);
    printf("슬롯 %d 저장 완료! (%s)\n", slot, filename);
}

void showSaveSlots() {
    ensureDirectory(SAVE_DIR);

    printf("\n==== 저장 슬롯 목록 ====\n");
    for (int i = 1; i <= MAX_SLOT; ++i) {
        char filename[128];
        sprintf(filename, "%s/save_slot%d.dat", SAVE_DIR, i);

        FILE* fp;
        errno_t err = fopen_s(&fp, filename, "rb");
        if (err || !fp) {
            printf("슬롯 %d: [빈 슬롯]\n", i);
            continue;
        }

        CHARACTER temp;
        int floor;
        fread(&temp, sizeof(CHARACTER), 1, fp);
        fread(&floor, sizeof(int), 1, fp);
        fclose(fp);
        printf("슬롯 %d: %s (%s) - %d층\n", i, temp.name, temp.job, floor);
    }
    printf("========================\n");
}

int loadGame(CHARACTER* character, int* dun_lev) {
    ensureDirectory(SAVE_DIR);

    showSaveSlots();
    int slot;
    printf("\n불러올 슬롯 선택 (1~10): ");
    while (scanf_s("%d", &slot) != 1 || slot < 1 || slot > MAX_SLOT) {
        while (getchar() != '\n');
        printf("다시 입력: ");
    }

    char filename[128];
    sprintf(filename, "%s/save_slot%d.dat", SAVE_DIR, slot);

    FILE* fp;
    errno_t err = fopen_s(&fp, filename, "rb");
    if (err || !fp) {
        printf("슬롯 %d 불러오기 실패\n", slot);
        return 0;
    }

    fread(character, sizeof(CHARACTER), 1, fp);
    fread(dun_lev, sizeof(int), 1, fp);
    fclose(fp);

    if (strcmp(character->job, "전사") == 0 || strcmp(character->job, "파이터") == 0 || strcmp(character->job, "페이지") == 0)
        SetWarrior(character);
    else if (strcmp(character->job, "궁수") == 0 || strcmp(character->job, "헌터") == 0 || strcmp(character->job, "사수") == 0)
        SetArcher(character);
    else if (strcmp(character->job, "마법사") == 0 || strcmp(character->job, "위자드") == 0 || strcmp(character->job, "클레릭") == 0)
        SetMage(character);
    else if (strcmp(character->job, "도적") == 0 || strcmp(character->job, "어쌔신") == 0 || strcmp(character->job, "시프") == 0)
        SetRogue(character);

    printf("슬롯 %d에서 게임 불러옴. (%s)\n", slot, filename);
    return 1;
}
