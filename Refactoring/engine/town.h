
#ifndef TOWN_H
#define TOWN_H

#include "character.h"

void enterTown(struct CHARACTER* character, int* dun_lev);
void inn(struct CHARACTER* character);
void blacksmith(struct CHARACTER* character);
void upgrade_weapon(struct CHARACTER* character);

#endif
