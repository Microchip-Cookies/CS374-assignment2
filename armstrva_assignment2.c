#include <stdio.h>
#include <stdlib.h> // for EXIT_SUCCESS and EXIT_FAILURE
#include <string.h>

#define MAX_NUM_LANGS 5
#define MAX_LEN_LANG 20


struct movie {
    char *title;
    int year;
    char **languages;
    double rating;
};

int count_char(char *str, char target) {
    int count = 0;
    int i = 0;

    for (i=0; str[i]; i++) {
        if (str[i] == target) {
            count++;
        }
    }
    return count;
}

/* 
 * Function: parse_list
 * 
 * Receives a string with one or more tokens separated by semicolons and enclosed in square brackets: 
 *  [token_1;token_2 ... token_n]
 * 
 * Returns a pointer to an array containing each token as a string pointer.
 */
// char **parse_list(char *input_str){
//     char **list = NULL, **p = NULL;
//     char *token = NULL;
//     char *str = NULL;
//     int num_tokens = 0;
//     int i = 0;

//     // Make an array with space for all tokens in list (or find simple way to count number of langs count ;?)
//     num_tokens = count_char(input_str, ';') + 1;
//     list = malloc(num_tokens * sizeof(list));
//     if (list == NULL) {
//         printf("parse_list could not allocate memory for list\n");
//         return NULL;
//     }

//     // While there are still more tokens in input, allocate memory, make string, add to array
//     token = strtok(input_str, "[;]");
//     i = 0;
//     do {
//         str = calloc(strlen(token) + 1, sizeof(char));
//         if (str == NULL) {
//             printf("parse_list unable to allocate memory for string\n");
//             return NULL;
//         }
//         printf("parse_list allocated memory for %d strings\n", i);
//         // strcpy(str, token);
//         // list[i] = str;
//         // i++;
//     } while (strtok(NULL, "[;]"));

//     return list;
// }


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

    token = strtok(NULL, ",");
    curr_movie->year = strtol(token, NULL, 10);

    token = strtok(NULL, ",");
    curr_movie->languages = NULL;
    // parse_list(token);
    printf("Languages: %s\n", token);
    // curr_movie->languages = parse_list(token);

    // Copy the value of state into the member state in the structure
    token = strtok(NULL, ",");
    curr_movie->rating = strtod(token, NULL);

    // Set the next node to NULL in the newly created movie entry
    return curr_movie;
}


/*
 * Function: processMovieFile
 *   Opens a file, reads and prints each line
 *   filePath: path to the file
 * 
 *  
 *  This function was adapted from the sample provided to the class.
 */
 void processMovieFile(char* filePath){
    char *currLine = NULL;
    size_t len = 0;
    int num_read = 0;
    struct movie *new_movie;
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
        printf("Title: %s ", new_movie->title);
        // for (i=0; new_movie.languages[i]; i++) {
        //     // printf("%s ", (char) new_movie.languages[i]);
        //     puts(new_movie.languages);
        // }
        printf("\n");
        num_read++;
    }

    // Free the memory allocated by getline for currLine
    free(currLine);
    // Close the file
    fclose(movieFile);
    printf("Processed file %s and parsed data for %d movies\n", filePath, num_read);
}


/**
 * 
 */
int main ( int argc, char **argv ){
    if (argc < 2)
    {
        printf("You must provide the name of the file to process\n");
        printf("Example usage: ./movies movies.csv\n");
        return EXIT_FAILURE;
    }
    processMovieFile(argv[1]);
    return EXIT_SUCCESS;
}