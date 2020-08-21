#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <ctype.h>
#include "projekti.h"

struct student **addStudent(struct student **reg, struct student *s) {
    /* Checks the length of register and reallocates memory so that it has free space
    for one more student and adds new student as the last of the array of pointers. */

    int last;
    for (last = 0; reg[last] != NULL; last++);
    reg[last] = s;
    reg = realloc(reg, (last + 2) * sizeof(struct student *));
    if (reg == NULL) {
        printf("Error: Reallocating memory for new student failed.\n");
        return NULL;
    }
    reg[last + 1] = NULL;
    printf("Student added to register!\n");
    return reg;
}

void delRegister(struct student **r) {
    /* Loops through register and frees memory for every studen structure
    and at the end frees the register. */

    // Frees the memory used for register
    for (int i = 0; r[i] != NULL; i++) {
        free(r[i]);
    }
    free(r);
    printf("Register freed!\n");
}

int *sorted(struct student **reg) {
    /* Makes new int array which have has the order for register.
    For example if register has [3, 1, 5] as a sums of points sorted
    return int array containing [1, 2, 0] which is the order in which the
    list is printed. */

    int n;
    // Checking lengt of register and making 
    for (n = 0; reg[n] != NULL; n++);
    int *order = malloc(sizeof(int) * n);
    if (order == NULL) {
        printf("Error: Failed to allocate memory.\n");
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        order[i] = i;
    }
    // Simple O(n)^2 sorting algorithm sorting register in ascending order
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (reg[j]->sum > reg[i]->sum) {
                int tmp = order[i];
                order[i] = order[j];
                order[j] = tmp;
            }
        }
    }
    return order;
}

void printStudent(struct student **reg) {
    /* Loops through "order" array which contains the order in which 
    register should be printed and every iteration prints student at
    the index that order array points. */

    int *order = sorted(reg);
    // Loops register until finds first nullpointer
    for (int i = 0; reg[i] != NULL; i++) {
        printf("\nName: %s %s\n", reg[order[i]]->first_name, reg[order[i]]->last_name);
        printf("Student number: %d\n", reg[order[i]]->stud_num);
        for (int j = 0; j < 6; j++) {
            printf("%d ", reg[order[i]]->points[j]);
        }
        printf("\n");
        printf("%d\n", reg[order[i]]->sum);
    }
    free(order);
}

struct student **addParser(char *input, struct student **reg) {
    /* Takes command as an argument and parses it if it is in correct 
    format ("A" "studen number" "last name" "first name") and passes it
    forwards to adding function which handels the memory management and adding
    it to the register. */

    struct student *s = malloc(sizeof(struct student));
    if (s == NULL) {
        printf("Error: Failed to allocate memory.\n");
    }
    // Initializing names to be able to use conditionals
    memset(s->first_name, 0, sizeof(s->first_name));
    memset(s->last_name, 0, sizeof(s->last_name));
    int loc = 0;
    int k = 0;
    while(loc < 4 && k < 80) {
        if (isspace((unsigned char) input[k])) {
            while (isspace((unsigned char) input[k])) k++;
            loc++;
        }
        if (!isspace((unsigned char) input[k])) {
            char stud_n[7];
            memset(stud_n, 0, sizeof(stud_n));
            int i = 0;
            int j;
            switch (loc)
            {
            // Parsing student number
            case 1:
                for (j = k; !isspace(input[j]); j++) {
                    stud_n[i++] = (int) input[j];
                }
                s->stud_num = atoi(stud_n);
                if (s->stud_num == 0) {
                    printf("Error: Student number was not accepted\n");
                    return reg;
                }
                k = j;
                break;

            // Parsing last name
            case 2:
                for (j = k; !isspace(input[j]); j++) {
                    if (i == 20 && strlen(s->last_name) != 0) {
                        printf("Only including 20 first characters of last name\n");
                    }
                    if (i <= 20) {
                        s->last_name[i] = input[j];
                    }
                    i++;
                }
                k = j;
                break;
            
            // Parsing first name
            case 3:
                for (j = k; !isspace(input[j]); j++) {
                    if (i == 20) {
                        printf("Only including 20 first characters of first name\n");
                    }
                    if (i <= 20) {
                        s->first_name[i] = input[j];
                    }
                    i++;
                }
                k = j;
                break;

            default:
                k++;
                break;
            }
        }
    }
    if (strlen(s->first_name) == 0 && strlen(s->last_name) == 0) {
        printf("Error: Names aren't in correct form.\n");
        return reg;
    }
    // Initialize all points to 0
    memset(s->points, 0, sizeof(s->points));
    s->sum = 0;
    return addStudent(reg, s);
}

struct student *findStudentByNro(int opnro, struct student **reg) {
    /* Loops through register and checks all student numbers until finds on 
    which match to given student number (opnro). */

    for (int i = 0; reg[i] != NULL; i++) {
        if (reg[i]->stud_num == opnro) {
            return reg[i];
        }
    }
    return NULL;
}

void refresP(char *input, struct student **reg) {
    /* Takes command and parses it and updates points if the command container correct
    elements ("U" "student number" " course number" "new points") */

    int opnro;
    int idx;
    int p;
    int loc = 0;
    int k = 0;
    while(loc < 4) {
        if (isspace((unsigned char) input[k])) {
            while (isspace((unsigned char) input[k])) k++;
            loc++;
        }
        if (!isspace((unsigned char) input[k])) {
            int i = 0;
            int j;
            char stud_n[7];
            switch (loc)
            {
            // Parsing student number
            case 1:
                for (j = k; !isspace(input[j]); j++) {
                    stud_n[i++] = (int) input[j];
                }
                opnro = atoi(stud_n);
                k = j;
                break;
            
            // Parsing round number (index in points array)
            case 2:
                for (j = k; !isspace(input[j]); j++) {
                    stud_n[i++] = (int) input[j];
                }
                idx = atoi(stud_n);
                k = j;
                break;
            
            // Parsing amount of points
            case 3:
                for (j = k; !isspace(input[j]); j++) {
                    stud_n[i++] = (int) input[j];
                }
                p = atoi(stud_n);
                k = j;
                break;
            default:
                k++;
                break;
            }
            memset(stud_n, 0, 7);
        }
    }
    struct student *s = findStudentByNro(opnro, reg);
    if (s == NULL) {
        printf("Error: didn't find student with given student number.");
        return;
    }

    // Adding the difference in updated points to sum
    s->sum = s->sum - s->points[idx - 1] + p;
    s->points[idx - 1] = p;
    printf("Points added for %s %s\n", s->first_name, s->last_name);
}

int writeToFile(struct student **reg, char *input) {
    /* Takes command and parses it ("W" "filename") and adds file extension
    to the name. After that loops through register and writes the contet to
    file it created as a strings separated with whitespace one structure
    at a line. */

    int loc = 0;
    int k = 0;
    char name[24];
    while(loc < 3 && k < 80) {
        if (isspace((unsigned char) input[k])) {
            while (isspace((unsigned char) input[k])) k++;
            loc++;
        }
        if (!isspace((unsigned char) input[k])) {
            int i = 0;
            int j;
            switch (loc)
            {

            // Parsing filename and adding ".txt" type
            case 1:
                for (j = k; !isspace(input[j]); j++) {
                    if (i == 20) {
                        printf("Only including 20 first characters of last name\n");
                    }
                    if (i <= 20) {
                        name[i] = input[j];
                    }
                    i++;
                }
                char *type = ".txt";
                int c = 0; 
                for (int x = i; c < 5; x++) {
                    name[x] = type[c++];
                }
                k = j;
                break;
            
            default:
                k++;
                break;
            }
        }
    }
    FILE *f;
    f = fopen(name, "w");
    if (f == NULL) {
        printf("Error: Couldn't open the file.\n");
        return -1;
    }
    // Writing register to file which have name given as an argument
    for (int i = 0; reg[i] != NULL; i++) {
        fprintf(f, "%d ", reg[i]->stud_num);
        for (int j = 0; j < 6; j++) {
            fprintf(f, "%d ", reg[i]->points[j]);
        }
        fprintf(f, "%d ", reg[i]->sum);
        fprintf(f, "%s ", reg[i]->first_name);
        fprintf(f, "%s\n", reg[i]->last_name);
    }
    fclose(f);
    return 0;
}

struct student **readFromFile(struct student **reg, char *input) {
    /* Takes comman and parses it ("O" "file name") and tries to open file
    named as the command suggests plus the file extension (.txt). If directory
    contains the file it loops through it line by line and calls addStudent()
    at every line and tries to add the student wrote on line. */

    // Cleans register before filling it with information in file
    delRegister(reg);
    reg = malloc(sizeof(struct student *));
    reg[0] = NULL;
    int loc = 0;
    int k = 0;
    char file_name[24];
    while(loc < 2) {
        if (isspace((unsigned char) input[k])) {
            while (isspace((unsigned char) input[k])) k++;
            loc++;
        }
        if (!isspace((unsigned char) input[k])) {
            int i = 0;
            int j;
            switch (loc)
            {
            // Parsing filename
            case 1:
                for (j = k; !isspace(input[j]); j++) {
                    if (i == 20) {
                        printf("Only including 20 first characters of last name\n");
                    }
                    if (i <= 20) {
                        file_name[i] = input[j];
                    }
                    i++;
                }
                char *type = ".txt";
                int c = 0; 
                for (int x = i; c < 5; x++) {
                    file_name[x] = type[c++];
                }
                k = j;
                break;
            
            default:
                k++;
                break;
            }
        }
    }
    FILE *f;
    f = fopen(file_name, "r");
    if (!f) {
        printf("Error: Could not open file!\n");
    }
    int sn, p1, p2, p3, p4, p5, p6, su;
    char fname[21], lname[21];
    // Scans all necessary info to fill the student structure and fills register with new students
    while (fscanf(f, "%d %d %d %d %d %d %d %d %s %s", &sn, &p1, &p2, &p3, &p4, &p5, &p6, &su, fname, lname) > 0){
        if (sn == 0) {
            printf("Error: Student number was not accepted\n");
            return NULL;
        }
        struct student *s = malloc(sizeof(struct student));
        memset(s->first_name, 0, sizeof(s->first_name));
        memset(s->last_name, 0, sizeof(s->last_name));
        s->stud_num = sn;
        s->points[0] = p1;
        s->points[1] = p2;
        s->points[2] = p3;
        s->points[3] = p4;
        s->points[4] = p5;
        s->points[5] = p6;
        s->sum = su;
        for (int i = 0; fname[i] != '\0'; i++) {
            s->first_name[i] = fname[i];
        }
        for (int i = 0; lname[i] != '\0'; i++) {
            s->last_name[i] = lname[i];
        }
        // Uses same addStudent function as manual adding of students
        reg = addStudent(reg, s);
    }
    fclose(f);
    return reg;
}

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
            if (writeToFile(reg, buffer) == 0) {
                printf("Register succesfully saved!\n");
            }
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
        printf("\n");
    }
}
