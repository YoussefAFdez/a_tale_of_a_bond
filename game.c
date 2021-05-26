//
// Created by Yuu on 25/05/2021.
//

#include <string.h>
#include "game.h"

void mainGame(playerInfo p1) {
    initialize();
    if (!p1.currentZone && !p1.currentEXP && p1.playerLevel == 1) launchIntro();
    else printMainGame(p1);
}

void printMainGame(playerInfo p1) {

    system("cls");
    printf("Player: %s\t\tLevel: %d\tZone: %d\t\tHP: %d\t\tMonsters: %d/10", p1.playerName, p1.playerLevel, p1.currentZone, p1.currentHP, p1.monsterCount);

}

void launchIntro() {
    tutorial();
}

void tutorial() {
    system("cls");
    FILE *file = fopen("tutorial.txt", "r");
    char c;
    while ((c = fgetc(file)) != EOF) {
        printf("%c", c);
    }
    fclose(file);
    getch();
}
