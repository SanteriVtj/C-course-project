#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "project.h"

int main(void) {
    int loop = 1;
    char buffer[150];
    struct student **reg = malloc(sizeof(struct student *));
    reg[0] = NULL;
    while (loop) {
        printf("Insert command: ");
        if (fgets(buffer, 150, stdin) == NULL) {
            printf("fget returned NULL");
            break;
        }
        
        switch (buffer[0])
        {
        case 'Q':
            printf("Bye!\n");
            loop = 0;
            del_register(reg);
            break;

        case 'U':
            refresP(buffer, reg);
            break;

        case 'A':
            reg = addParser(buffer, reg);
            break;
        
        case 'L':
            printStudent(reg);
            break;

        case 'W':
            writeFile(reg, buffer);
            break;

        case 'O':
            reg = readFile(reg, buffer);
            break;

        default:
            printf("Error: Not a proper command!\n");
            break;
        }
    }
}