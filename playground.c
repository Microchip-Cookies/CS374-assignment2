#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_char(char *str, char target) {
    int count;
    int i;

    for (i=0; str[i]; i++) {
        if (str[i] == target) {
            count++;
        }
    }
    return count;
}


int main(void) {
    char *input_str;
    char *token;
    char *langs[5] = {0};
    int i;

    input_str = malloc(100 * sizeof(char));
    strcpy(input_str, "[English;French;Spanish]");

    i = count_char(input_str, ';');
    printf("There are %d semicolons.", i);
    i=0;

    token = strtok(input_str, "[];");
    do {
        langs[i] = token;
        i++;
    }
    while ((token = strtok(NULL, "[];")) != NULL);

    for (i=0; i<5 && langs[i]; i++) {
        puts(langs[i]);
    }

    return 0;
}

// int main(void) {
//     char *str;

//     strcpy(str, "abcd");
//     str[3] = 'e';
//     printf("Last index of str is %d\n", (int) strlen(str) - 1);
//     puts(str);    
//     return 0;
// }
