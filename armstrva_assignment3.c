#include <stdio.h>
#include <stdlib.h> // for EXIT_SUCCESS and EXIT_FAILURE
#include <stdbool.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>


bool isMovieFile(const struct dirent *inputFile) {
    // char *fileName = inputFile->d_name;
    char prefix[] = "movies_";
    char fileExt[] = ".csv";
    int i = 0, j = 0;

    for(i=0; i<strlen(prefix); i++) {
        if(inputFile->d_name[i] == '\0' | prefix[i] != inputFile->d_name[i]) {
            return false;
        }
    }

    for(i=strlen(fileExt) -1, j=strlen(inputFile->d_name) - 1; i >= 0; i--, j--) {
        if(fileExt[i] != inputFile->d_name[j]) {
            return false;
        }
    }

    return true;
}

void processMovieFile(char *fileName) {
    printf("Now processing the chosen file named %s.\n", fileName);
}

/*
 * processNamed
 * 
 * Gets file name from user. If file exists, calls processMovieFile and returns 1, otherwise returns -1
 */
int processNamed(void){
    char fileName[256];

    // Get the file name from the user
    printf("Enter the complete file name: ");
    fgets(fileName, sizeof(fileName), stdin);
    printf("You entered %s.\n", fileName);
    // If the file is not in the current directory, closedir() return 0
    // Otherwise, process the file

    return 1;
}

void processSmallest(void){
    DIR *currDir = opendir(".");
    struct dirent *entry = NULL;
    struct stat entryStat;
    off_t smSize = 0;
    char *smName = NULL;


    // For each file in the current directory that starts with "movies_" w/ .csv, if file > largest, largest = file
    currDir = opendir(".");
    while((entry = readdir(currDir)) != NULL) {
        if(isMovieFile(entry)) {
            if (smName == NULL) {
                smName = entry->d_name;
                stat(smName, &entryStat);
                smSize = entryStat.st_size;
            } else {
                stat(entry->d_name, &entryStat);
                if(entryStat.st_size < smSize) {
                    smName = entry->d_name;
                    smSize = entryStat.st_size;
                }
            }
        }
    }
    processMovieFile(smName);
    closedir(currDir);
}

/*
 * processLargest
 * 
 * Identifies the largest movie file in the current directory and passes its file name (path) to a helper
 * function to process.
 */
void processLargest(void){
    DIR* currDir = NULL;
    struct dirent *entry = NULL;
    struct stat entryStat;
    off_t lgSize = 0;
    char *lgName = NULL;


    // For each file in the current directory that starts with "movies_" w/ .csv, if file > largest, largest = file
    currDir = opendir(".");
    while((entry = readdir(currDir)) != NULL) {
        if(isMovieFile(entry)) {
            if (lgName == NULL) {
                lgName = entry->d_name;
                stat(lgName, &entryStat);
                lgSize = entryStat.st_size;
            } else {
                stat(entry->d_name, &entryStat);
                if(entryStat.st_size > lgSize) {
                    lgName = entry->d_name;
                    lgSize = entryStat.st_size;
                }
            }
        }
    }
    processMovieFile(lgName);
    closedir(currDir);
}

/*
 * openProcessMenu
 *
 * Presents the user with menu options for file processing. Calls the appropriate helper depending
 * on user selection. Returns 1 on success, -1 on failure.
 */
int openProcessMenu(void) {
    int choice = 0;
    char input[2];

    while(true) {
        puts("\nWhich file you want to process?");
        puts("Enter 1 to pick the largest file");
        puts("Enter 2 to pick the smallest file");
        puts("Enter 3 to specify the name of a file\n");
        puts("Enter a choice from 1 to 3:");

        scanf("%d", &choice);
        scanf("%*[^\n]");
        if (choice < 1 || choice > 3) {
            puts("You entered an incorrect choice. Try again.");
        } 

        switch(choice) {
            case 1: processLargest(); return 1;
            case 2: processSmallest(); return 1;
            case 3: if(processNamed() == 1); return 1;
            // if successfully processed, return 1, otherwise break

        }
    }
    // /* Process File Menu*/
    // while(choice < 1 || choice > 3) {
    //     puts("\nWhich file you want to process?");
    //     puts("Enter 1 to pick the largest file");
    //     puts("Enter 2 to pick the smallest file");
    //     puts("Enter 3 to specify the name of a file\n");
    //     puts("Enter a choice from 1 to 3:");

    //     choice = atoi(fgets(input, sizeof(input), stdin));
    //     // scanf("%d", &choice);
    //     // scanf("%*[^\n]");
    //     if (choice < 1 || choice > 3) {
    //         puts("You entered an incorrect choice. Try again.");
    //     } 
    // }

    // switch(choice) {
    //     case 1: processLargest(); break;
    //     case 2: processSmallest(); break;
    //     case 3: processNamed(); break;
    //     // Get file name from user
    //     // If file name is valid, process file
    //     // Otherwise ?
    // }

}

/**
 * 
 */
int main (void){
    int choice = 0;
    char *fileName = "";

    /*Main Menu*/
    while(true) {
        puts("1. Select the file to process");
        puts("2. Exit the program\n");
        puts("Enter a choice 1 or 2: ");
        scanf("%d", &choice);
        scanf("%*[^\n]");

        switch(choice){
            case 1: openProcessMenu(); break;
            case 2: return EXIT_SUCCESS;
            default: puts("You entered an incorrect choice. Try again.");
        }
    }  
    return EXIT_SUCCESS;
}