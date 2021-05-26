//
// Created by Yuu on 25/05/2021.
//

#ifndef A_TALE_OF_A_BOND_GAME_H
#define A_TALE_OF_A_BOND_GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
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

typedef struct {
    int finalHP;
    int finalATK;
    int finalDEF;
    int finalCrit;
    int finalEXP;
} finalMonster;

void mainGame(playerInfo, int);
void initialize();
int printMainGame(playerInfo);
void launchIntro();
void tutorial();
void getStory(int);
int diceRoller();
void saveGame(playerInfo, int);
void startFight(playerInfo*);
void heal(playerInfo*);
playerStats getPlayerStatsByLevel(playerInfo);
finalMonster getMonster(int);
int getTotalMonsterSpawnChance();
monster buffMonster(monster, int);
finalMonster calculateFinalMonster(monster);

#endif //A_TALE_OF_A_BOND_GAME_H
