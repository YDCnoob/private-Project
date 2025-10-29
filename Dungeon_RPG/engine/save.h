
#ifndef SAVE_H
#define SAVE_H

#include "character.h"

void saveGame(const struct CHARACTER* character, int dun_lev);
int loadGame(struct CHARACTER* character, int* dun_lev);
void showSaveSlots();
void SaveRanking(const struct CHARACTER* character, int floor);
void printTopRanking();

#endif
