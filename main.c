#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "project.h"

int main(void) {
    int loop = 1;
    char buffer[51];
    struct student *reg = malloc(sizeof(struct student));
    char *ret = malloc(51 * sizeof(char));
    reg[0].first_name = NULL;
    while (loop) {
        printf("Insert command: ");
        ret = fgets(buffer, 51, stdin);

        if (ret == NULL) {
            printf("fget returned NULL");
            break;
        }
        // printf("%s\n", ret);
        switch (ret[0])
        {
        case 'Q':
            printf("Bye!\n");
            loop = 0;
            free(reg);
            // del_register(reg);
            break;

        case 'U':
            refresP(buffer, reg);
            break;

        case 'A':
            reg = parser(buffer, reg);
            break;
        
        case 'L':
            printStudent(reg);
            break;

        default:
            // printf("%s", buffer);
            break;
        }
    }
}