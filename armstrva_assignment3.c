#include <stdio.h>
#include <stdlib.h> // for EXIT_SUCCESS and EXIT_FAILURE
#include <stdbool.h>

void processNamed(void){
    puts("Process file named ____");
}

void processSmallest(void){
    puts("Process smallest");
}

void processLargest(void){
    puts("Process largest");
}

void processMovieFile(void) {
    int choice = 0;

    /* Process File Menu*/
    while(choice < 1 || choice > 3) {
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
    }

    switch(choice) {
        case 1: processLargest(); break;
        case 2: processSmallest(); break;
        case 3: processNamed(); break;
    }

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
            case 1: processMovieFile(); break;
            case 2: return EXIT_SUCCESS;
            default: puts("You entered an incorrect choice. Try again.");
        }
    }  
    return EXIT_SUCCESS;
}