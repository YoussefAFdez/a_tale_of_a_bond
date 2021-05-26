//
// Created by Yuu on 25/05/2021.
//

#include "game.h"

void mainGame(playerInfo p1, int fileNumber) {
    srand(time(NULL));
    if (!p1.currentZone && !p1.currentEXP && p1.playerLevel == 1) { launchIntro(); p1.currentEXP++; saveGame(p1, fileNumber); }

    int exitSignal = 0;
    while (!exitSignal) {
        switch (printMainGame(p1)) {
            case 1:
                startFight(&p1);
                break;
            case 2:
                heal(&p1);
                break;
            case 3:

                break;
            case 0:
                exitSignal = 1;
            default:;
        }
    }
    saveGame(p1, fileNumber);
}

int printMainGame(playerInfo p1) {

    playerStats ps1 = getPlayerStatsByLevel(p1);

    system("cls");
    puts("MAIN GAME\n");
    puts("1.- Fight");
    puts("2.- Heal");
    if (p1.monsterCount >= 10) puts("3.-");
    puts("0.- Save and quit\n\n\n\n");
    printf("Level: %d\tZone: %d\t\tHP: %d/%d\t\tMonsters: %d/10\t\tEXP: %d/%d", p1.playerLevel, p1.currentZone, p1.currentHP, ps1.HP, p1.monsterCount, p1.currentEXP, ps1.expNecessary);

    return getch() - '0';
}

void launchIntro() {
    tutorial();
    getStory(1);
    getch();
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

int diceRoller() {
    int num = rand() % 12 + 1;
    return num;
}

void getStory(int segment) {
    FILE *file = fopen(STORYFOLDER, "rb");
    story s1;
    storyHeader reg0;

    fseek(file, 0, SEEK_SET);
    fread(&reg0, sizeof(reg0), 1, file);

    int position = segment * sizeof(s1);
    fseek(file, position, SEEK_SET);
    fread(&s1, sizeof(s1), 1, file);

    system("cls");
    printf("%s", s1.segment);

}

void saveGame(playerInfo p1, int fileNumber) {
    FILE *file;

    switch (fileNumber) {
        case 1:
            file = fopen("savestates\\saveslot1.txt", "w");
            fprintf(file, "%s& %d & %d & %d & %d & %d", p1.playerName, p1.playerLevel, p1.currentZone, p1.currentEXP, p1.currentHP, p1.monsterCount);
            break;
        case 2:
            file = fopen("savestates\\saveslot2.txt", "w");
            fprintf(file, "%s& %d & %d & %d & %d & %d", p1.playerName, p1.playerLevel, p1.currentZone, p1.currentEXP, p1.currentHP, p1.monsterCount);
            break;
        default:
            file = fopen("savestates\\saveslot3.txt", "w");
            fprintf(file, "%s& %d & %d & %d & %d & %d", p1.playerName, p1.playerLevel, p1.currentZone, p1.currentEXP, p1.currentHP, p1.monsterCount);
    }

    fclose(file);
}

void startFight(playerInfo* p1) {
    int alive1 = 1, alive2 = 1; //alive1 represents the player while alive2 the enemy

    finalMonster fm1 = getMonster((*p1).currentZone);

    printf("\n%d, %d, %d, %d, %d", fm1.finalHP, fm1.finalATK, fm1.finalDEF, fm1.finalCrit, fm1.finalEXP);
    getch();
    getch();

    playerStats ps1 = getPlayerStatsByLevel(*p1);

}

void heal(playerInfo* p1) {
    playerStats ps1 = getPlayerStatsByLevel(*p1);
    p1->currentHP = ps1.HP;
}


playerStats getPlayerStatsByLevel(playerInfo p1) {
    FILE *file = fopen(PLAYERSTATSFOLDER, "rb");
    playerStats ps1;
    playerStatsHeader reg0;

    fseek(file, 0, SEEK_SET);
    fread(&reg0, sizeof(reg0), 1, file);

    int position = p1.playerLevel * sizeof(ps1);
    fseek(file, position, SEEK_SET);
    fread(&ps1, sizeof(ps1), 1, file);

    return ps1;
}


/*
 * Calculates a random number between all possible choices and then looks for the monster that fits in that range
 */
finalMonster getMonster(int zone) {

    int total = getTotalMonsterSpawnChance();

    int randomNumber = rand() % total + 1;

    FILE *file = fopen(MONSTERFOLDER, "rb");
    monster m1;
    monster m2;
    monsterHeader reg0;

    fseek(file, 0, SEEK_SET);
    fread((&reg0), sizeof(reg0), 1, file);

    int i, position, currMonster = 0;

    for (i = 1; i <= reg0.registerNumber; i++) {
        position = i * sizeof(m1);
        fseek(file, position, SEEK_SET);
        fread(&m1, sizeof(m1), 1, file);

        currMonster += m1.appearRatio;
        if (currMonster <= randomNumber) m2 = m1;
    }

    fclose(file);

    //Time to buff those stats by the multiplier
    m2 = buffMonster(m2, zone);

    //Lets create the final monster that we will be fighting
    finalMonster fm1 = calculateFinalMonster(m2);

    return fm1;
}


/*
 * Returns the total chance of the monsters
 */
int getTotalMonsterSpawnChance() {
    FILE *file = fopen(MONSTERFOLDER, "rb");
    monster m1;
    monsterHeader reg0;

    fseek(file, 0, SEEK_SET);
    fread(&reg0, sizeof(reg0), 1, file);

    int i, position, total = 0;

    for (i = 1; i <= reg0.registerNumber; i++) {
        position = i * sizeof(m1);
        fseek(file, position, SEEK_SET);
        fread(&m1, sizeof(m1), 1, file);

        total += m1.appearRatio;
    }

    fclose(file);

    return total;
}

monster buffMonster(monster m1, int zone) {

    switch (zone) {
        case 1:
            m1.minHP *= m1.multiplier1;
            m1.maxHP *= m1.multiplier1;
            m1.minATK *= m1.multiplier1;
            m1.maxATK *= m1.multiplier1;
            m1.minDEF *= m1.multiplier1;
            m1.maxDEF *= m1.multiplier1;
            m1.exp *= m1.multiplier1;
            break;
        case 2:
            m1.minHP *= m1.multiplier2;
            m1.maxHP *= m1.multiplier2;
            m1.minATK *= m1.multiplier2;
            m1.maxATK *= m1.multiplier2;
            m1.minDEF *= m1.multiplier2;
            m1.maxDEF *= m1.multiplier2;
            m1.exp *= m1.multiplier2;
            break;
        case 3:
            m1.minHP *= m1.multiplier3;
            m1.maxHP *= m1.multiplier3;
            m1.minATK *= m1.multiplier3;
            m1.maxATK *= m1.multiplier3;
            m1.minDEF *= m1.multiplier3;
            m1.maxDEF *= m1.multiplier3;
            m1.exp *= m1.multiplier3;
            break;
        case 4:
            m1.minHP *= m1.multiplier4;
            m1.maxHP *= m1.multiplier4;
            m1.minATK *= m1.multiplier4;
            m1.maxATK *= m1.multiplier4;
            m1.minDEF *= m1.multiplier4;
            m1.maxDEF *= m1.multiplier4;
            m1.exp *= m1.multiplier4;
            break;
        case 5:
            m1.minHP *= m1.multiplier5;
            m1.maxHP *= m1.multiplier5;
            m1.minATK *= m1.multiplier5;
            m1.maxATK *= m1.multiplier5;
            m1.minDEF *= m1.multiplier5;
            m1.maxDEF *= m1.multiplier5;
            m1.exp *= m1.multiplier5;
            break;
        default:
            break;
    }

    return m1;

}

finalMonster calculateFinalMonster(monster m1) {
    finalMonster fm1;

    fm1.finalHP = rand() % m1.maxHP + m1.minHP;
    fm1.finalATK = rand() % m1.maxATK + m1.minATK;
    fm1.finalDEF = rand() % m1.maxDEF + m1.minDEF;
    fm1.finalCrit = m1.critChance;
    fm1.finalEXP = m1.exp;
}


