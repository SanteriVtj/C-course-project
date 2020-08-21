#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "project.h"

int main(void) {
    /* Starts while loop which goes over until "Q" command is given. Loop
    takes commands which have to start with particular character (Q, U, A, W, O, L)
    to have any effect. If something else is given as comman it will just error and 
    ask for new command. If command is proper it will call functions from 
    student_register.c. Main function by itself doesn't do anything more than 
    create memory space for register and start loop to enable using the
    program mainly in student_register.c. */

    int loop = 1;
    char buffer[80];
    struct student **reg = malloc(sizeof(struct student *));
    reg[0] = NULL;
    while (loop) {
        // Fills buffer with 0 at every iteration to be sure there is no leftovers.
        memset(buffer, 0, sizeof(buffer));
        printf("Insert command: ");
        if (fgets(buffer, 80, stdin) == NULL) {
            printf("\nfget returned NULL");
            break;
        }
        
        // Actions are determined by the first character of command.
        switch (buffer[0])
        {
        case 'Q':
            loop = 0;
            delRegister(reg);
            printf("Bye!\n");
            break;

        case 'U':
            refresP(buffer, reg);
            break;

        case 'A':
            reg = addParser(buffer, reg);
            break;
        
        case 'W':
            writeToFile(reg, buffer);
            break;

        case 'O':
            reg = readFromFile(reg, buffer);
            break;

        case 'L':
            printStudent(reg);
            break;

        // If given command doesn't have any of the letters above as a first character defaults to error message
        default:
            printf("\nError: Not a proper command!\n");
            break;
        }
    }
}