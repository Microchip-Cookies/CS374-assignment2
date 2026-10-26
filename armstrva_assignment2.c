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

int has_lang(struct movie *curr_movie, char *lang) {
    char *lang_str = NULL;
    char *token = NULL;

    lang_str = calloc(strlen(curr_movie->languages) + 1, sizeof(char));
    if (lang_str == NULL) {
        printf("Error allocating memory");
    }
    strcpy(lang_str, curr_movie->languages);
    token = malloc(strlen(lang_str) * sizeof(char));
    if (token == NULL) {
        printf("Error allocating memory");
    }

    token = strtok(lang_str, "[];");
    do {
        if (strcmp(token, lang) == 0) {
            return 1;
        }
    } while (token = strtok(NULL, "[];"));

    return 0;
}

void show_by_lang(struct movie *movies) {
    char lang[21] = {0};
    int num_movies = 0;
    struct movie *curr_movie = movies;

    // What lang?
    printf("Enter the language for which you want to see movies: ");
    scanf("%s", lang);
    ("%*[^\n]");
    // If the current movie has the specified language, print its year and title
    while (curr_movie != NULL) {
        if (has_lang(curr_movie, lang)) {
            printf("%d %s\n", curr_movie->year, curr_movie->title);
            num_movies++;
        }
        curr_movie = curr_movie->next;
    }
    if (num_movies == 0) {
        printf("No data about movies released in %s\n", lang);
    }
}


void show_best(struct movie *movies) {
    struct movie *best[2026-1900] = {NULL};
    struct movie *curr_movie = movies;
    int i = 0;

    while (curr_movie != NULL) {
        i = curr_movie->year - 1900;
        if (best[i] == NULL || best[i]->rating < curr_movie->rating) {
            best[i] = curr_movie;
        }
        curr_movie = curr_movie->next;
    }
    for (i=0; i<(2026-1900); i++) {
        if (best[i]) {
            printf("%d %.1f %s\n", best[i]->year, best[i]->rating, best[i]->title);
        }
    }
    
}

void show_by_year(struct movie *movies){
    int year = 0;
    int has_movies = 0;
    struct movie *curr_movie = movies;

    printf("Enter the year for which you want to see movies: ");
    scanf(" %d", &year);
    ("%*[^\n]");

    while (curr_movie != NULL){
        if (curr_movie->year == year) {
            printf("%s\n", curr_movie->title);
            has_movies = 1;
        }
        curr_movie = curr_movie->next;
    }
    if (!has_movies) {
        printf("No data about movies released in the year %d\n", year);
    }
}

/**
 * 
 */
int main ( int argc, char **argv ){
    struct movie *movies = NULL;
    struct movie *curr_node = NULL;
    int selection = 0;

    if (argc < 2)
    {
        printf("You must provide the name of the file to process\n");
        printf("Example usage: ./movies movies.csv\n");
        return EXIT_FAILURE;
    }
    movies = processMovieFile(argv[1]);
    curr_node = movies;

    while (selection != 4) {
        printf("%s", "\n1. Show movies released in the specified year\n");
        puts("2. Show highest rated movie for each year");
        puts("3. Show the title and year of release of all movies in a specific language");
        puts("4. Exit from the program");
        puts("");
        printf("Enter a choice from 1 to 4: ");
        scanf("%d", &selection);
        scanf("%*[^\n]");
        if (selection > 4 || selection < 1) {
            puts("You entered an incorrect choice. Try again.");
        }
        switch (selection) {
            case 1: show_by_year(movies); break;
            case 2: show_best(movies); break;
            case 3: show_by_lang(movies); break;
        }
    }
    
    return EXIT_SUCCESS;
}