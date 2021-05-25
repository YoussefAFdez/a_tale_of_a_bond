//
// Created by Yuu on 25/05/2021.
//

#include "game.h"

void mainGame(playerInfo p1) {
    if (!p1.currentZone && !p1.currentEXP && p1.playerLevel == 1) launchIntro();
    else printMainGame(p1);
}

void printMainGame(playerInfo p1) {

    system("cls");
    printf("Player: %s\t\tLevel: %d\tZone: %d\t\tHP: %d", p1.playerName, p1.playerLevel, p1.currentZone, p1.currentHP);

}

void launchIntro() {
    tutorial();
}

void tutorial() {
    system("cls");
    puts("Quick tutorial about the game\n");

    puts("The game consists on combating monsters and healing up to get EXP and level up, gaining enough strength to fight the bosses and "
         "going up floors or zones, until you beat the final boss, called Onigumo the Demon Lord\n");
    puts("To combat you have to choose the 'Fight' option, it will face you with a random monster and a battle will be simulated.\n"
         "If your HP is high enough you may end up winning the fight and getting exp, which would lead you to level up.\n"
         "However, don't let your HP reach 0, if you do your character will die and you will be penalized going down 2 levels and back one zone\n");
    puts("To reach up a higher zone, you need to defeat at least 10 monsters, that number resets after you die, or after you get to a new Zone.\n"
         "Once you defeat that number of monsters, which you can check in the bottom of the game menu, you'll see an option appear called 'Ascend'.\n"
         "That ascend option will either trigger a boss fight or part of the story\n");
    puts("To heal up simply select the 'heal' option, it should get you up to your maximum hp depending on your level\n");
    puts("If you ever feel lost and need to check this help, just select tutorial from the main menu\n");
    puts("Last but not least, the game saves itsefl automatically when you select 'Save and quit'\n");
    puts("\nPress any key to continue...");
    getch();
}
