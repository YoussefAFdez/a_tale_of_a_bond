//
// Created by Yuu on 25/05/2021.
//

#ifndef A_TALE_OF_A_BOND_ADMINMENU_H
#define A_TALE_OF_A_BOND_ADMINMENU_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define MONSTERFOLDER "monsters\\monsters.dat"
#define BOSSFOLDER "bosses\\bosses.dat"
#define STORYFOLDER "story\\story.dat"

typedef struct {
    char name[26];
    int minHP;
    int maxHP;
    int minATK;
    int maxATK;
    int minDEF;
    int maxDEF;
    int critChance;
    int exp;
    int appearRatio;
    float multiplier1;
    float multiplier2;
    float multiplier3;
    float multiplier4;
    float multiplier5;
} monster;

typedef struct {
    int registerNumber;
} monsterHeader;

typedef struct {
    char name[51];
    int baseHP;
    int infuriatedHP;
    int baseATK;
    int infuriatedATK;
    int baseDEF;
    int infuriatedDEF;
    int critchance;
} boss;

typedef struct {
    int registerNumber;
} bossHeader;

typedef struct {
    char segment[5001];
} story;

typedef struct {
    int registerNumber;
} storyHeader;

int printSecretMenu();
void mainSecretMenu();
int printMonstersMenu();
void createNewMonster();
void editMonster();
void deleteMonster();
void listMonsters();
int printEditMonsterOptions(char[]);
void printMonsterInfo(int);
void editBoss();
void editStory();

#endif //A_TALE_OF_A_BOND_ADMINMENU_H
