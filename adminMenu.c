//
// Created by Yuu on 25/05/2021.
//

#include <string.h>
#include <dirent.h>
#include <errno.h>
#include "adminMenu.h"

void initialize() {
    //We test to check if the necessary folders exists if not we create them
    DIR* dir;

    //Check if the savestates folder exists
    dir = opendir("savestates");
    if (dir) closedir(dir);
    else if (ENOENT == errno){ system("mkdir savestates"); closedir(dir); }

    //Check if monster folder exists
    dir = opendir("monsters");
    if (dir) closedir(dir);
    else if (ENOENT == errno){ system("mkdir monsters"); closedir(dir); }

    //Check if bosses folder exists
    dir = opendir("bosses");
    if (dir) closedir(dir);
    else if (ENOENT == errno){ system("mkdir bosses"); closedir(dir); }

    //Check if bosses folder exists
    dir = opendir("story");
    if (dir) closedir(dir);
    else if (ENOENT == errno){ system("mkdir story"); closedir(dir); }

    FILE *file;

    //We initialize the monsters file if it doesn't exist
    file = fopen(MONSTERFOLDER, "r+b");
    monster m1;
    monsterHeader reg0;

    if (file == NULL) {
        file = fopen(MONSTERFOLDER, "w+b");

        reg0.registerNumber = 0;
        memset(&m1, '*', sizeof(m1));

        fseek(file, 0, SEEK_SET);
        fwrite(&m1, sizeof(m1), 1, file);
        fseek(file, 0, SEEK_SET);
        fwrite(&reg0, sizeof(reg0), 1, file);
    }
    fclose(file);

    //We initialize the bosses file if it doesn't exist
    file = fopen(BOSSFOLDER, "r+b");
    boss b1;
    bossHeader bossReg0;

    if (file == NULL) {
        file = fopen(BOSSFOLDER, "w+b");

        bossReg0.registerNumber = 0;
        memset(&b1, '*', sizeof(b1));

        fseek(file, 0, SEEK_SET);
        fwrite(&b1, sizeof(b1), 1, file);
        fseek(file, 0, SEEK_SET);
        fwrite(&bossReg0, sizeof(bossReg0), 1, file);
    }
    fclose(file);

    //We initialize the bosses file if it doesn't exist
    file = fopen(STORYFOLDER, "r+b");
    story s1;
    storyHeader storyReg0;

    if (file == NULL) {
        file = fopen(STORYFOLDER, "w+b");

        storyReg0.registerNumber = 0;
        memset(&s1, '*', sizeof(s1));

        fseek(file, 0, SEEK_SET);
        fwrite(&s1, sizeof(s1), 1, file);
        fseek(file, 0, SEEK_SET);
        fwrite(&storyReg0, sizeof(storyReg0), 1, file);
    }
    fclose(file);

}

void mainSecretMenu() {
    int exit = 0, subOption;
    while (!exit) {
        subOption = 0;
        switch (printSecretMenu()) {
            case 1:
                while(!subOption) {
                    switch (printMonstersMenu()) {
                        case 1:
                            createNewMonster();
                            break;
                        case 2:
                            editMonster();
                            break;
                        case 3:
                            deleteMonster();
                            break;
                        case 0:
                            subOption = 1;
                    }
                }
                break;
            case 2:
                editBoss();
                break;
            case 3:
                editStory();
                break;
            case 4:
                break;
            case 0:
                exit = 1;
                break;
            default:
                puts("Invalid option");
                getch();
        }
    }

}

int printSecretMenu() {
    system("cls");
    puts("Secret Admin Menu\n");
    puts("1.- Manage Monsters");
    puts("2.- Manage Bosses");
    puts("3.- Manage Story");
    puts("4.- Manage Lore");
    puts("0.- Go back to main menu");
    return getch() - '0';
}

int printMonstersMenu() {
    system("cls");
    puts("Manage Monsters\n");
    puts("1.- Create a new monster");
    puts("2.- Edit an existing monster");
    puts("3.- Remove an existing monster");
    puts("0.- Go Back");
    return getch() - '0';
}

void createNewMonster() {
    monster m1;

    system("cls");

    //We read data from the monster
    printf("Monster name (up to 25 characters): ");
    fgets(m1.name, 26, stdin);
    printf("Monster's minimum HP: ");
    scanf("%d", &m1.minHP);
    printf("Monster's maximum HP: ");
    scanf("%d", &m1.maxHP);
    printf("Monster's minimum Attack: ");
    scanf("%d", &m1.minATK);
    printf("Monster's maximum Attack: ");
    scanf("%d", &m1.maxATK);
    printf("Monster's minimum Deffense: ");
    scanf("%d", &m1.minDEF);
    printf("Monster's maximum Deffense: ");
    scanf("%d", &m1.maxDEF);
    printf("Monster's crit chance: ");
    scanf("%d", &m1.critChance);
    printf("Monster EXP drop: ");
    scanf("%d", &m1.exp);
    printf("Monster's appear ratio: ");
    scanf("%d", &m1.appearRatio);

    puts("\n\n"); //Separator

    printf("Monster mutiplier Zone 1: ");
    scanf("%f", &m1.multiplier1);
    printf("Monster mutiplier Zone 2: ");
    scanf("%f", &m1.multiplier2);
    printf("Monster mutiplier Zone 3: ");
    scanf("%f", &m1.multiplier3);
    printf("Monster mutiplier Zone 4: ");
    scanf("%f", &m1.multiplier4);
    printf("Monster mutiplier Zone 5: ");
    scanf("%f", &m1.multiplier5);
    fflush(stdin);


    //We open the file to append the monsters info
    FILE *file = fopen(MONSTERFOLDER, "r+b");
    monsterHeader reg0;

    fseek(file, 0, SEEK_SET);
    fread(&reg0, sizeof(reg0), 1, file);

    int placement = (reg0.registerNumber + 1) * sizeof (m1);
    fseek(file, placement, SEEK_SET);
    fwrite(&m1, sizeof(m1), 1, file);

    reg0.registerNumber++;
    fseek(file, 0, SEEK_SET);
    fwrite(&reg0, sizeof(reg0), 1, file);

    fclose(file);

}


/*
 * Allows to modify one or all the values from the monster
 */
void editMonster() {
    system("cls");

    listMonsters();
    puts("0.- Cancel\n");

    //Select a monster from the list
    int selection;
    printf("Select the monster from the list you want to edit: ");
    scanf("%d", &selection);
    fflush(stdin);


    //We load the monster info
    FILE *file = fopen(MONSTERFOLDER, "r+b");
    monster m1;
    monsterHeader reg0;

    fseek(file, 0, SEEK_SET);
    fread(&reg0, sizeof(reg0), 1, file);

    int position = selection * sizeof(m1);
    fseek(file, position, SEEK_SET);
    fread(&m1, sizeof(m1), 1, file);

    if (!selection);
    else if (selection <= reg0.registerNumber && selection > 0) {
        int selectedOption = printEditMonsterOptions(m1.name);
        switch (selectedOption) {
            case 1:
                system("cls");
                printf("Introduce the new monster's name (up to 25 characters): ");
                fgets(m1.name, 26, stdin);
                break;
            case 2:
                system("cls");
                printf("Set the new MIN HP value: ");
                scanf("%d", &m1.minHP);
                printf("Set the new MAX HP value: ");
                scanf("%d", &m1.maxHP);
                break;
            case 3:
                system("cls");
                printf("Set the new MIN ATK value: ");
                scanf("%d", &m1.minATK);
                printf("Set the new MAX ATK value: ");
                scanf("%d", &m1.maxATK);
                break;
            case 4:
                system("cls");
                printf("Set the new MIN DEF value: ");
                scanf("%d", &m1.minDEF);
                printf("Set the new MAX DEF value: ");
                scanf("%d", &m1.maxDEF);
                break;
            case 5:
                system("cls");
                printf("Set the new CRIT chance value: ");
                scanf("%d", &m1.critChance);
                break;
            case 6:
                system("cls");
                printf("Set the new EXP drop value: ");
                scanf("%d", &m1.exp);
                break;
            case 7:
                system("cls");
                printf("Set the new appear ratio value: ");
                scanf("%d", &m1.appearRatio);
                break;
            case 8:
                system("cls");
                printf("Set up the multiplier for zone 1: ");
                scanf("%f", &m1.multiplier1);
                printf("Set up the multiplier for zone 2: ");
                scanf("%f", &m1.multiplier2);
                printf("Set up the multiplier for zone 3: ");
                scanf("%f", &m1.multiplier3);
                printf("Set up the multiplier for zone 4: ");
                scanf("%f", &m1.multiplier4);
                printf("Set up the multiplier for zone 5: ");
                scanf("%f", &m1.multiplier5);
                break;
            case 9:
                system("cls");
                printf("New monster name (up to 25 characters): ");
                fgets(m1.name, 26, stdin);
                printf("New monster's minimum HP: ");
                scanf("%d", &m1.minHP);
                printf("New monster's maximum HP: ");
                scanf("%d", &m1.maxHP);
                printf("New monster's minimum Attack: ");
                scanf("%d", &m1.minATK);
                printf("New monster's maximum Attack: ");
                scanf("%d", &m1.maxATK);
                printf("New monster's minimum Deffense: ");
                scanf("%d", &m1.minDEF);
                printf("New monster's maximum Deffense: ");
                scanf("%d", &m1.maxDEF);
                printf("New monster's crit chance: ");
                scanf("%d", &m1.critChance);
                printf("New monster EXP drop: ");
                scanf("%d", &m1.exp);
                printf("New monster's appear ratio: ");
                scanf("%d", &m1.appearRatio);

                puts("\n\n"); //Separator

                printf("New monster mutiplier Zone 1: ");
                scanf("%f", &m1.multiplier1);
                printf("New Monster mutiplier Zone 2: ");
                scanf("%f", &m1.multiplier2);
                printf("New monster mutiplier Zone 3: ");
                scanf("%f", &m1.multiplier3);
                printf("New Monster mutiplier Zone 4: ");
                scanf("%f", &m1.multiplier4);
                printf("New monster mutiplier Zone 5: ");
                scanf("%f", &m1.multiplier5);
                fflush(stdin);
                break;
            case 0:
                break;
            default:
                puts("Invalid option selected");
                break;
        }

        fflush(stdin);

        //We overwrite the previous data
        fseek(file, position, SEEK_SET);
        fwrite(&m1, sizeof(m1), 1, file);

        if (selectedOption >= 1 && selectedOption <= 9) { puts("\nThe values have been modified"); getch(); }

    } else { puts("There's not a monster in that register"); getch(); }
    fclose(file);

}

void deleteMonster() {
    system("cls");
    listMonsters();
    puts("0.- Cancel\n");

    //Get the selected option from the list
    int selection;
    printf("Select the monster from the list you want to delete: ");
    scanf("%d", &selection);

    if (selection) {
        //Previsualize monster info and ask for confirmation
        system("cls");
        printMonsterInfo(selection);
        printf("\n\nAre you sure you want to delete this monster? [y/n]: ");

        int choice = getch();
        if (choice == 'y' || choice == 'Y') {
            FILE *file = fopen(MONSTERFOLDER, "r+b");
            monster m1;
            monsterHeader reg0;

            fseek(file, 0, SEEK_SET);
            fread(&reg0, sizeof(reg0), 1, file);

            int position = selection * sizeof(m1), i;
            for (i = selection; i < reg0.registerNumber; i++) {
                position = (i + 1) * sizeof(m1);
                fseek(file, position, SEEK_SET);
                fread(&m1, sizeof(m1), 1, file);

                position = i * sizeof(m1);
                fseek(file, position, SEEK_SET);
                fwrite(&m1, sizeof(m1), 1, file);
            }

            reg0.registerNumber--;
            fseek(file, 0, SEEK_SET);
            fwrite(&reg0, sizeof(reg0), 1, file);

            fclose(file);
            puts("\nThe monster has been deleted...");

        } else puts("\nOperation Cancelled");

        getch();
    }
}


/*
 * Lists all the monsters in a numbered list
 */
void listMonsters() {
    monster m1;
    monsterHeader reg0;

    FILE *file = fopen(MONSTERFOLDER, "rb");
    int i, placement;

    fseek(file, 0, SEEK_SET);
    fread(&reg0, sizeof(reg0), 1, file);

    for (i = 1; i <= reg0.registerNumber; i++) {
        placement = i * sizeof(m1);
        fseek(file, placement, SEEK_SET);
        fread(&m1, sizeof(m1), 1, file);

        printf("%d.- %s", i, m1.name);
    }
    puts(""); //Extra separator

    fclose(file);
}

void printMonsterInfo(int monsterRegister) {
    FILE *file = fopen(MONSTERFOLDER, "rb");
    monsterHeader reg0;
    monster m1;

    fseek(file, 0, SEEK_SET);
    fread(&reg0, sizeof(reg0), 1, file);

    int position = monsterRegister * sizeof(m1);
    fseek(file, position, SEEK_SET);
    fread(&m1, sizeof(m1), 1, file);

    printf("Name: %s", m1.name);
    printf("Min HP: %d", m1.minHP);
    printf("\nMax HP: %d", m1.maxHP);
    printf("\nMin ATK: %d", m1.minATK);
    printf("\nMax ATK: %d", m1.maxATK);
    printf("\nMin DEF: %d", m1.minDEF);
    printf("\nMax DEF: %d", m1.maxDEF);
    printf("\nCrit Chance: %d", m1.critChance);
    printf("\nEXP Drop: %d", m1.exp);
    printf("\nAppear Ratio: %d", m1.appearRatio);
    puts("");
    printf("\nZone 1 multiplier: %.2f", m1.multiplier1);
    printf("\nZone 2 multiplier: %.2f", m1.multiplier2);
    printf("\nZone 3 multiplier: %.2f", m1.multiplier3);
    printf("\nZone 4 multiplier: %.2f", m1.multiplier4);
    printf("\nZone 5 multiplier: %.2f", m1.multiplier5);
}

int printEditMonsterOptions(char name[]) {
    system("cls");
    printf("Monster Selected: %s", name);
    puts("\n1.- Change monster's name");
    puts("2.- Change monster's HP value");
    puts("3.- Change monster's ATK value");
    puts("4.- Change monster's DEF value");
    puts("5.- Change monster's CRIT chance");
    puts("6.- Change monster's EXP drop");
    puts("7.- Change monster's appear ratio");
    puts("8.- Change monster's zone multiplier");
    puts("9.- Change all values of the monster");
    puts("0.- Go back\n");

    printf("Select an option: ");

    return getch() - '0';
}

void editBoss() {
    FILE *file = fopen(BOSSFOLDER, "r+b");
    boss b1;
    bossHeader reg0;

    fseek(file, 0, SEEK_SET);
    fread(&reg0, sizeof(reg0), 1, file);

    int i, position;

    //We list all the bosses in order of Zone
    for (i = 1; i <= reg0.registerNumber; i++) {
        position = i * sizeof(b1);
        fseek(file, position, SEEK_SET);
        fread(&b1, sizeof(b1), 1, file);

        printf("%d.- %s", i, b1.name);
    }

    puts("0.- Go back");
    printf("\nSelect the boss you want to edit: ");
    int selection = getch() - '0';

    if (!selection);
    else if (selection >= 1 && selection <= 3) {
        system("cls");
        printf("New boss name (up to 50 characters): ");
        fgets(b1.name, 51, stdin);
        printf("New boss BASE HP: ");
        scanf("%d", &b1.baseHP);
        printf("New boss INFURIATED HP: ");
        scanf("%d", &b1.infuriatedHP);
        printf("New boss BASE ATK: ");
        scanf("%d", &b1.baseATK);
        printf("New boss INFURIATED ATK: ");
        scanf("%d", &b1.infuriatedATK);
        printf("New boss BASE DEF: ");
        scanf("%d", &b1.baseDEF);
        printf("New boss INFURIATED DEF: ");
        scanf("%d", &b1.infuriatedDEF);
        printf("New boss Crit Chance: ");
        scanf("%d", &b1.critchance);

        position = selection * sizeof(b1);
        fseek(file, position, SEEK_SET);
        fwrite(&b1, sizeof(b1), 1, file);

        puts("\nBoss values modified...");

    } else puts("\nThere's no monster with that number");

    fflush(stdin);
    fclose(file);
    getch();
}

void editStory() {
    puts("Edit Story\n");

    //Display the different segments of the story
    puts("1.- Intro");
    puts("2.- Zone 1 Entrance");
    puts("3.- Intro First boss");
    puts("4.- Zone 2 Entrance");
    puts("5.- Zone 3 Entrance");
    puts("6.- Intro Second boss");
    puts("7.- Zone 4 Entrance");
    puts("8.- Zone 5 Enrance");
    puts("9.- Intro Third boss");
    puts("10.- Final Dialog\n");
    puts("0.- Go back\n");

    printf("Choose an option: ");

    int selection;
    scanf("%d", &selection);
    fflush(stdin);

    if (!selection);
    else if (selection >= 1 && selection <= 10) {
        FILE *file = fopen(STORYFOLDER, "r+b");
        story s1;
        storyHeader reg0;

        fseek(file, 0, SEEK_SET);
        fread(&reg0, sizeof(reg0), 1, file);

        puts("Write the new segment of the story (up to 5.000 characters). Careful with pressing ENTER KEY...\n\n");
        fgets(s1.segment, 5001, stdin);

        int position = selection * sizeof(s1);
        fseek(file, position, SEEK_SET);
        fwrite(&s1, sizeof(s1), 1, file);

        fclose(file);

        puts("The segment has been modified");
    } else ("You haven't chosen an appropiate segment");

    getch();

}



