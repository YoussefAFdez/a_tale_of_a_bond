#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <dirent.h>
#include <errno.h>
#include "game.h"
#define OPCANCEL "Operation Cancelled. Press any key to return to main menu..."

int printMainMenu();
int printNewGameMenu();
int printContinueGameMenu();
int printManageGameFilesMenu();
void printLoreMenu();
void printCredits();
int readAllFiles(int);
void writeFileInfo(FILE*, int);
void checkSelectedFile(int, int);
int confirmNewGame();
int deleteConfirm();
void createNewGameFile(int);
void loadGame(int);

int main() {
    initialize();
    int exitRequest = 0;
    while (1) {
        system("cls");
        int filesFound = 0;

        switch (printMainMenu()){
            case 1:
                filesFound = printNewGameMenu();
                checkSelectedFile(filesFound, 1);
                break;
            case 2:
                filesFound = printContinueGameMenu();
                checkSelectedFile(filesFound, 2);
                break;
            case 3:
                filesFound = printManageGameFilesMenu();
                checkSelectedFile(filesFound, 3);
                break;
            case 4:
                printLoreMenu();
                break;
            case 5:
                printCredits();
                break;
            case 6:
                tutorial();
                break;
            case 7: //Just a quick way to return to the menu after using the secret admin menu
                break;
            case 0:
                exit(0);
            default:
                puts("\nInvalid Option");
                getch();
                break;
        }
    }
}

int printMainMenu() {
    puts("A Tale of a Bond - An interactive text Game\n");
    puts("1.- New Game");
    puts("2.- Continue Game");
    puts("3.- Manage Game Files");
    puts("4.- Lore");
    puts("5.- Credits");
    puts("6.- Tutorial");
    puts("0.- Exit\n");
    printf("Choose an option:");

    int option = getch();
    if (option >= '0' && option <= '9') return option - '0';
    if (option == 'j') {
        option = getch();
        if (option == 'a') {
            option = getch();
            if (option == 'v') {
                option = getch();
                if (option == 'a') mainSecretMenu();
            }
        }
    } else return 'a';

    return 7;
}

int printNewGameMenu() {
    int filesFound = 0;
    system("cls");
    puts("NEW GAME\n");
    filesFound = readAllFiles(1);
    puts("\n0.- Go Back\n");
    printf("Choose the save slot you wish to save your game into: ");
    //getch();
    return filesFound;
}

int printContinueGameMenu() {
    int filesFound = 0;
    system("cls");
    puts("CONTINUE GAME\n");
    filesFound = readAllFiles(1);
    puts("\n0.- Go Back\n");
    printf("Choose the save slot you want to load: ");
    //getch();
    return filesFound;
}

int printManageGameFilesMenu() {
    int filesFound = 0;
    system("cls");
    puts("MANAGE GAME FILES\n");
    filesFound = readAllFiles(2);
    puts("\n0.- Go Back\n");
    printf("Choose the save file you want to delete: ");
    //getch();
    return  filesFound;
}

//Allows for information to be displayed
void printLoreMenu() {
    system("cls");
    puts("LORE\n");
    puts("1.- Ally Characters");
    puts("2.- Monsters");
    puts("3.- Bosses");
    puts("4.- Others");
    puts("0.- Go Back to menu\n");
    printf("Choose an option from the list: ");
    getch();
}

//Writes some info by the creator
void printCredits() {
    system("cls");
    puts("Game developed and written by YoussefAFdez\n");
    puts("Date: 27th May 2021");
    getch();
}

int readAllFiles(int mode) {

    int returnvalue = 0;
    /* Return values:
     * 0 -> No files found
     * 1 -> File1 found
     * 2 -> File2 found
     * 3 -> File1 and File2 found
     * 4 -> File3 found
     * 5 -> File1 and File3 found
     * 6 -> File2 and File3 found
     * 7 -> All files found
     */

    /*
     * We check if the savestates folder exists
     */
    DIR* dir = opendir("savestates");
    if (dir) closedir(dir);
    else if (ENOENT == errno){ system("mkdir savestates"); closedir(dir); }


    //We try to read from all 3 files
    FILE *file1 = fopen("savestates\\saveslot1.txt", "r");
    FILE *file2 = fopen("savestates\\saveslot2.txt", "r");
    FILE *file3 = fopen("savestates\\saveslot3.txt", "r");

    /*
     * We check if the files exists and display the information at the same time we set up the value to return
     * that will represent the number of files that are available
    */

    /*
     * Mode1 corresponds to the modes that will visualize all files even nonexistant
     * Mode2 will only show those file that do in fact exist
     */
    if (mode == 1) {
        if (file1 == NULL) puts("1.- Empty Save Slot");
        else { writeFileInfo(file1, 1); returnvalue++; }
        if (file2 == NULL) puts("2.- Empty Save Slot");
        else { writeFileInfo(file2, 2); returnvalue += 2; }
        if (file3 == NULL) puts("3.- Empty Save Slot");
        else { writeFileInfo(file3, 3); returnvalue += 4; }
    } else {
        if (file1 == NULL && file2 == NULL && file3 == NULL) puts("There are no existing files yet");
        else {
            if (file1 != NULL) { writeFileInfo(file1, 1); returnvalue++; }
            if (file2 != NULL) { writeFileInfo(file2, 2); returnvalue += 2; }
            if (file3 != NULL) { writeFileInfo(file3, 3); returnvalue += 4; }
        }
    }

    //We close the files after reading them
    fclose(file1);
    fclose(file2);
    fclose(file3);

    //We return the value of files found to later operate with them.
    return returnvalue;
}

void writeFileInfo(FILE* file, int fileNum) {
    playerInfo p1;
    switch (fileNum) {
        case 1:
            printf("1.- ");
            break;
        case 2:
            printf("2.- ");
            break;
        default:
            printf("3.- ");
    }
    fscanf(file, "%[^&]&%d & %d & %d & %d & %d", p1.playerName, &p1.playerLevel, &p1.currentZone, &p1.currentEXP, &p1.currentHP, &p1.monsterCount);
    printf("%s\tLvl: %d\tZone: %d\n", p1.playerName, p1.playerLevel, p1.currentZone);
}

/*
 * This Function allow to select one of the desired options and call a function according to it.
 *
 * Functions:
 * 1 -> New Game
 * 2 -> Continue Game
 * 3 -> Manage Files
*/
void checkSelectedFile(int filesRead, int function) {
    int option = getch() - '0';
    int menuStop = 0; //Will determine if there needs to be a getch() to stop the player from going to the menu

    //If the user tries to put an option of a file that can't be reached:
    if (option < 0 || option > 3) puts("\nYou haven't selected a valid option");

    //We check the file that the user is trying to load.
    else if (option)
    switch (option) {
        case 1:
            if (filesRead == 1 || filesRead == 3 || filesRead == 5 || filesRead == 7) {
                switch (function) {
                    case 1:
                        printf("\nA game save file already exists in that slot, do you want to overwrite it? [y/n]: ");
                        if (confirmNewGame()) createNewGameFile(option);
                        else { puts("\n" OPCANCEL); menuStop = 1; }
                        break;
                    case 2:
                        loadGame(option);
                        break;
                    default:
                        printf("\nAre you sure you want to delete the file? [y/n]: ");
                        if (deleteConfirm()) { remove("savestates\\saveslot1.txt"); puts("The file has been deleted..."); }
                        else puts(OPCANCEL);
                        menuStop = 1;
                }
            } else {
                switch (function) {
                    case 1:
                        createNewGameFile(option);
                        break;
                    case 2:
                        printf("\nThe save slot is empty, would you like to crete a new game instead? [y/n]: ");
                        if (confirmNewGame()) createNewGameFile(option);
                        else { puts("\n"OPCANCEL); menuStop = 1; }
                        break;
                    default:
                        puts("\nThe file that you're trying to select isn't created yet!");
                        menuStop = 1;
                }
            }
            break;
        case 2:
            if (filesRead == 2 || filesRead == 3 || filesRead == 6 || filesRead == 7) {
                switch (function) {
                    case 1:
                        printf("\nA game save file already exists in that slot, do you want to overwrite it? [y/n]: ");
                        if (confirmNewGame()) createNewGameFile(option);
                        else { puts("\n" OPCANCEL); menuStop = 1; }
                        break;
                    case 2:
                        loadGame(option);
                        break;
                    default:
                        printf("\nAre you sure you want to delete the file? [y/n]: ");
                        if (deleteConfirm()) { remove("savestates\\saveslot2.txt"); puts("The file has been deleted..."); }
                        else puts(OPCANCEL);
                        menuStop = 1;
                }
            } else {
                switch (function) {
                    case 1:
                        createNewGameFile(option);
                        break;
                    case 2:
                        printf("\nThe save slot is empty, would you like to crete a new game instead? [y/n]: ");
                        if (confirmNewGame()) createNewGameFile(option);
                        else { puts("\n"OPCANCEL); menuStop = 1; }
                        break;
                    default:
                        puts("\nThe file that you're trying to select isn't created yet!");
                        menuStop = 1;
                }
            }
            break;
        default:
            if (filesRead == 4 || filesRead == 5 || filesRead == 6 || filesRead == 7) {
                switch (function) {
                    case 1:
                        printf("\nA game save file already exists in that slot, do you want to overwrite it? [y/n]: ");
                        if (confirmNewGame()) createNewGameFile(option);
                        else { puts("\n"OPCANCEL); menuStop = 1; }
                        break;
                    case 2:
                        loadGame(option);
                        break;
                    default:
                        printf("\nAre you sure you want to delete the file? [y/n]: ");
                        if (deleteConfirm()) { remove("savestates\\saveslot3.txt"); puts("The file has been deleted..."); }
                        else puts(OPCANCEL);
                        menuStop = 1;
                }
            } else {
                switch (function) {
                    case 1:
                        createNewGameFile(option);
                        break;
                    case 2:
                        printf("\nThe save slot is empty, would you like to crete a new game instead? [y/n]: ");
                        if (confirmNewGame()) createNewGameFile(option);
                        else { puts("\n"OPCANCEL); menuStop = 1; }
                        break;
                    default:
                        puts("\nThe file that you're trying to select isn't created yet!");
                        menuStop = 1;
                }
            }
    }
    if (menuStop) getch();
}


/*
 * Checks the option selected, and returns 1 if user selected y or Y and 0 otherwise
 */
int confirmNewGame() {
    int confirmation = 0;
    int select = getch();

    if (select == 'y' || select == 'Y') confirmation++;

    return confirmation;
}

int deleteConfirm() {
    int confirmation = 0;
    int select = getch();

    if (select == 'y' || select == 'Y') {
        printf("\nOne last time, once deleted you won't be able to recover it, are you sure? [y/n]: ");
        select = getch();
        if (select == 'y' || select == 'Y') confirmation++;
    }

    puts(""); //Just placing a newline for the resultmessage
    return confirmation;
}


/*
 * Creates a new file and runs the game
 */
void createNewGameFile(int fileNumber) {
    playerInfo p1;

    system("cls");

    //We read the name of the character, only info we need to get from the user
    printf("Choose the name of your character (up to 10 characters): ");
    fgets(p1.playerName, 11, stdin);
    p1.playerName[strcspn(p1.playerName, "\n")] = 0; //Takes the \n from the string
    fflush(stdin); //We clear buffer just in case name was longer than 10 characters

    //We load up the rest of the type playerInfo with default options
    p1.playerLevel = 1;
    p1.currentZone = 0;
    p1.currentEXP = 0;
    p1.currentHP = 100;
    p1.monsterCount = 0;

    /*
     * We create the new file, it doesn't matter if it existed cause we're overriding it if it were
     * Depending on the filesaveslot selected we will create one or other
     */

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
    mainGame(p1, fileNumber);
}



/*
 * Reads the data from the savefile and saves it into the playerInfo struct
 * Then sends it to the mainGame function
 */
void loadGame(int fileNumber) {
    playerInfo p1;

    FILE *file;

    //We open the selected file and extract the information
    switch (fileNumber) {
        case 1:
            file = fopen("savestates\\saveslot1.txt", "r");
            fscanf(file, "%[^&]&%d & %d & %d & %d", p1.playerName, &p1.playerLevel, &p1.currentZone, &p1.currentEXP, &p1.currentHP);
            break;
        case 2:
            file = fopen("savestates\\saveslot2.txt", "r");
            fscanf(file, "%[^&]&%d & %d & %d & %d", p1.playerName, &p1.playerLevel, &p1.currentZone, &p1.currentEXP, &p1.currentHP);
            break;
        default:
            file = fopen("savestates\\saveslot3.txt", "r");
            fscanf(file, "%[^&]&%d & %d & %d & %d", p1.playerName, &p1.playerLevel, &p1.currentZone, &p1.currentEXP, &p1.currentHP);
    }

    fclose(file);
    mainGame(p1, fileNumber);
}
