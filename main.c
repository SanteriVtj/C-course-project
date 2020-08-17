#include <stdio.h>
#include <stdlib.h>
#include "project.h"

int main(void) {
    int loop = 1;
    char buffer[51];
    struct student *reg = malloc(sizeof(struct student *));
    char *ret = malloc(51 * sizeof(char));
    while (loop) {
        printf("Insert command: ");
        ret = fgets(buffer, 51, stdin);
        if (ret == NULL) {
            printf("fget returned NULL");
            break;
        }

        switch (ret[0])
        {
        case 'Q':
            printf("Bye!\n");
            loop = 0;
            break;

        case 'U':
            break;

        case 'A':
            parser(buffer, reg);
            break;
        
        case 'L':
            printStudent(reg);
            break;

        default:
            // printf("%s", buffer);
            break;
        }
    }
    free(ret);
}