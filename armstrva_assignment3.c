#include <stdio.h>
#include <stdlib.h> // for EXIT_SUCCESS and EXIT_FAILURE
#include <stdbool.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

struct movie {
    char *title;
    int year;
    char *languages;
    double rating;
    struct movie *next;
};

/* 
 * Function: create_movie
 * 
 * Receives a string with four tokens separated by commas: Title,Year,Languages,Rating Value
 *  Ex: The Princess Bride,1987,[English],8
 *  Ex: Monty Python and the Holy Grail,1975,[English,French],8.1
 * Creates a movie struct and returns a pointer to the newly created movie. Returns NULL if
 * unable to create movie.
 */
struct movie* create_movie(char *movie_str){
// struct movie* create_movie(char *movie_string){
    char **languages = NULL;
    char *token = NULL;
    struct movie *curr_movie = NULL;
    struct movie *next = NULL;

    // Allocate memory for the movie structure
    curr_movie = malloc(sizeof(struct movie));
    if (curr_movie == NULL) {
        printf("Could not allocate memory for new movie\n");
        return NULL;
    }

    // Allocate memory for the title; then assign it to the movie title member
    token = strtok(movie_str, ",");
    curr_movie->title = calloc(strlen(token) + 1, sizeof(char));
    strcpy(curr_movie->title, token);

    // Set movie year
    token = strtok(NULL, ",");
    curr_movie->year = strtol(token, NULL, 10);

    // Set movie languages
    token = strtok(NULL, ",");
    curr_movie->languages = calloc(strlen(token) + 1, sizeof(char));
    strcpy(curr_movie->languages, token);

    // Set movie rating
    token = strtok(NULL, ",");
    curr_movie->rating = strtod(token, NULL);

    // Set next node to NULL
    curr_movie->next = NULL;
    
    return curr_movie;
}

/*
 * Function: getMovies
 *   Opens a file, reads and prints each line
 *   filePath: path to the file
 * 
 *  
 *  This function was adapted from the sample provided to the class.
 */
 struct movie *getMovies(char* filePath){
    char *currLine = NULL;
    size_t len = 0;
    int num_read = 0;
    struct movie *new_movie = NULL;
    struct movie *first = NULL;
    struct movie *last = NULL;
    int i = 0;

    // Open the specified file for reading only
    FILE *movieFile = fopen(filePath, "r");

    // Read the headers and discard
    getline(&currLine, &len, movieFile);

    // Read the data line by line
    while(getline(&currLine, &len, movieFile) != -1)
    {
        // new_movie = *create_movie(currLine);
        new_movie = create_movie(currLine);
        if (first == NULL) {
            first = new_movie;
            last = new_movie;
        }
        last->next = new_movie;
        last = new_movie;
        // // QA output
        // printf("%-40s %d %-45s %g", new_movie->title, new_movie->year, new_movie->languages, new_movie->rating);
        // printf("\n");

        // Add to linked list

        num_read++;
    }

    // Free the memory allocated by getline for currLine
    free(currLine);
    // Close the file
    fclose(movieFile);
    printf("Processed file %s and parsed data for %d movies\n", filePath, num_read);
    return first;
}


bool isInCurrentDirectory(char *fileName);

/*
 * isMovieFile
 * 
 * Returns true if file name begins with "movie_" and has the .csv file extension at the end.
 * Returns false otherwise. 
 */
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


char *makeMovieDirectory(void) {
    char dirName[275];
    char *intAsStr;


}

// Information about using rand from W3 Schools "C stdlib rand() function" https://www.w3schools.com/c/ref_stdlib_rand.php
void processMovieFile(char *fileName) {
    char dirName[275];
    char *intAsStr;

    printf("Now processing the chosen file named %s.\n", fileName);

    // Make a new directory
    do {
        // Build the directory name
        srand(time(NULL));
        strcpy(dirName, "armstrva.movies.");
        sprintf(intAsStr, "%d", rand() % 100000);
        strcat(dirName, intAsStr);

        // ensure it is unique in this directory
    } while(isInCurrentDirectory(dirName) == true);

    mkdir(dirName, 0750);

    // Make new files

}

bool isInCurrentDirectory(char *fileName) {
    DIR *currDir = opendir(".");
    struct dirent *entry = NULL;
    struct stat entryStat;

    while((entry = readdir(currDir)) != NULL) {
        if(strcmp(entry->d_name, fileName) == 0) {
            return true;
        }
    }

    closedir(currDir);
    return false;
}

/*
 * processNamed
 * 
 * Gets file name from user. If file exists in current directory, calls processMovieFile and returns 1, otherwise returns -1
 */
int processNamed(void){
    char *fileName;

    // Get the file name from the user
    printf("Enter the complete file name: ");
    scanf("%s", fileName);
    scanf("%*[^\n]");
    if(isInCurrentDirectory(fileName)) {
        processMovieFile(fileName);
    } else {
        printf("The file %s was not found. Try again", fileName);
        return -1;
    }

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
        printf("Enter a choice from 1 to 3: ");

        scanf("%d", &choice);
        scanf("%*[^\n]");
        if (choice < 1 || choice > 3) {
            puts("You entered an incorrect choice. Try again.");
        } 

        switch(choice) {
            case 1: processLargest(); return 1;
            case 2: processSmallest(); return 1;
            case 3: if(processNamed() == 1) return 1;
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