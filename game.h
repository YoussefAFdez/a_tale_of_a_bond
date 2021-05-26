//
// Created by Yuu on 25/05/2021.
//

#ifndef A_TALE_OF_A_BOND_GAME_H
#define A_TALE_OF_A_BOND_GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "adminMenu.h"

typedef struct {
    char playerName[11];
    int playerLevel;
    int currentZone;
    int currentEXP;
    int currentHP;
    int monsterCount;
} playerInfo;

void mainGame(playerInfo);
void initialize();
void printMainGame(playerInfo);
void launchIntro();
void tutorial();
void getStory(int);

#endif //A_TALE_OF_A_BOND_GAME_H
