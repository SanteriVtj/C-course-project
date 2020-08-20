#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "project.h"

int main(void) {
    int loop = 1;
    char buffer[80];
    struct student **reg = malloc(sizeof(struct student *));
    reg[0] = NULL;
    while (loop) {
        memset(buffer, 0, sizeof(buffer));
        printf("Insert command: ");
        if (fgets(buffer, 80, stdin) == NULL) {
            printf("fget returned NULL");
            break;
        }
        
        switch (buffer[0])
        {
        case 'Q':
            loop = 0;
            del_register(reg);
            printf("Bye!\n");
            break;

        case 'U':
            refresP(buffer, reg);
            break;

        case 'A':
            // printf("%s\n", buffer);
            // printf("%lu\n", sizeof(buffer) / sizeof(char));
            reg = addParser(buffer, reg);
            break;
        
        case 'W':
            writeFile(reg, buffer);
            break;

        case 'O':
            reg = readFile(reg, buffer);
            break;

        case 'L':
            printStudent(reg);
            break;

        // If given command doesn't have any of the letters above as a first character defaults to error message
        default:
            printf("Error: Not a proper command!\n");
            break;
        }
    }
}