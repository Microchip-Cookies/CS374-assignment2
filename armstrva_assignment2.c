#include <stdio.h>
#include <stdlib.h> // for EXIT_SUCCESS and EXIT_FAILURE
#include <string.h>

#define MAX_NUM_LANGS 5
#define MAX_LEN_LANG 20


struct movie {
    char *title;
    int year;
    char *languages;
    double rating;
    struct movie *next;
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
 * Function: processMovieFile
 *   Opens a file, reads and prints each line
 *   filePath: path to the file
 * 
 *  
 *  This function was adapted from the sample provided to the class.
 */
 struct movie *processMovieFile(char* filePath){
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


/**
 * 
 */
int main ( int argc, char **argv ){
    struct movie *movies = NULL;
    struct movie *curr_node = NULL;
    if (argc < 2)
    {
        printf("You must provide the name of the file to process\n");
        printf("Example usage: ./movies movies.csv\n");
        return EXIT_FAILURE;
    }
    movies = processMovieFile(argv[1]);
    curr_node = movies;
    printf("The first movie is \"%s\"\n", curr_node->title);
    curr_node = curr_node->next;
    printf("The second movie is \"%s\"\n", curr_node->title);
    while (curr_node->next != NULL){
        curr_node = curr_node->next;
    }
    printf("The last movie is \"%s\"\n", curr_node->title);
    return EXIT_SUCCESS;
}