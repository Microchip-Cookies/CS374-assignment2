#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **make_str_array(int n) {
    char **str_arr = NULL, **p = NULL, *str = NULL;
    int i = 0;

    str_arr = malloc(sizeof(str_arr) * n);
    if (str_arr == NULL) {
        printf("make_str_array failed to allocate memory for list\n");
        return NULL;
    }
    
    p = str_arr;
    for (i=0; i < n; i++) {
        str = calloc(100, sizeof(char));
        if (str == NULL) {
            printf("Unable to allocate memory for string.");
        }
        sprintf(str, "foobar %d", i);
        str_arr[i] = str;
    }

  
    return str_arr;

}

int *make_int_array(int n) {
    int *arr = (int *) malloc(sizeof(int) * n);
    int *p = arr;
    int i = 0;

    if (arr == NULL) {
        printf("make_int_array failed to allocate memory.\n");
    }
    for (i=0; i < n; i++) {
        *p = 3 + i;
        p++;
    }
    return arr;
}

int main(void) {
    int *my_arr = NULL;
    int *p = NULL;
    char **my_strings = NULL;
    char **q = NULL;
    int i = 0;
    int n = 5;

    // Create and print an integer array with n numbers
    my_arr = make_int_array(n);
    if (my_arr == NULL) {
        printf("Failed to create array.\n");
        return 1;
    }
    printf("Integer array created: [");
    p = my_arr;
    for (i=0; i < n; i++){
        printf("%d, ", *p);
        p++;
    }
    puts("]");

    // Create and print array of strings
    my_strings = make_str_array(n);
    if (my_strings == NULL) {
        printf("Failed to create string array.");
        return 1;
    }
    
    for (i=0; i < n; i++) {
        printf("str_array element %d contains %s\n", i, my_strings[i]);
    }

    return 0;
}




// int count_char(char *str, char target) {
//     int count;
//     int i;

//     for (i=0; str[i]; i++) {
//         if (str[i] == target) {
//             count++;
//         }
//     }
//     return count;
// }


// int main(void) {
//     char *input_str;
//     char *token;
//     char *langs[5] = {0};
//     int i;

//     input_str = malloc(100 * sizeof(char));
//     strcpy(input_str, "[English;French;Spanish]");

//     i = count_char(input_str, ';');
//     printf("There are %d semicolons.", i);
//     i=0;

//     token = strtok(input_str, "[];");
//     do {
//         langs[i] = token;
//         i++;
//     }
//     while ((token = strtok(NULL, "[];")) != NULL);

//     for (i=0; i<5 && langs[i]; i++) {
//         puts(langs[i]);
//     }

//     return 0;
// }

// int main(void) {
//     char *str;

//     strcpy(str, "abcd");
//     str[3] = 'e';
//     printf("Last index of str is %d\n", (int) strlen(str) - 1);
//     puts(str);    
//     return 0;
// }
