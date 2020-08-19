#include "project.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void printStudent(struct student **reg) {
    for (int i = 0; reg[i] != NULL; i++) {
        printf("%s %s\n", reg[i]->first_name, reg[i]->last_name);
        printf("Student number: %d\n", reg[i]->stud_num);
        for (int j = 0; j < 6; j++) {
            printf("%d ", reg[i]->points[j]);
        }
        printf("\n");
        printf("%d\n", reg[i]->sum);
    }
}

struct student **addParser(char *input, struct student **reg) {
    struct student *s = malloc(sizeof(struct student));
    memset(s->first_name, 0, sizeof(s->first_name));
    memset(s->last_name, 0, sizeof(s->last_name));
    int loc = 0;
    int k = 0;
    while(loc < 4) {
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
            case 1:
                for (j = k; !isspace(input[j]); j++) {
                    stud_n[i++] = (int) input[j];
                }
                s->stud_num = atoi(stud_n);
                k = j;
                break;
            
            case 2:
                for (j = k; !isspace(input[j]); j++) {
                    if (i == 20) {
                        printf("Only including 20 first characters of last name\n");
                    }
                    if (i <= 20) {
                        s->last_name[i] = input[j];
                    }
                    i++;
                }
                k = j;
                break;
            
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
    memset(s->points, 0, sizeof(s->points));
    s->sum = 0;
    return addStudent(reg, s);
}

struct student **addStudent(struct student **reg, struct student *s) {
    int last;
    for (last = 0; reg[last] != NULL; last++);
    reg[last] = s;
    reg = realloc(reg, (last + 2) * sizeof(struct student *));
    reg[last + 1] = NULL;
    return reg;
}

struct student *find_studentnr(int opnro, struct student **reg) {
    for (int i = 0; reg[i] != NULL; i++) {
        if (reg[i]->stud_num == opnro) {
            return reg[i];
        }
    }
    return NULL;
}

void refresP(char *input, struct student **reg) {
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
            case 1:
                for (j = k; !isspace(input[j]); j++) {
                    stud_n[i++] = (int) input[j];
                }
                opnro = atoi(stud_n);
                k = j;
                break;
            
            case 2:
                for (j = k; !isspace(input[j]); j++) {
                    stud_n[i++] = (int) input[j];
                }
                idx = atoi(stud_n);
                k = j;
                break;
            
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
    struct student *s = find_studentnr(opnro, reg);
    if (s == NULL) {
        printf("Error: didn't find student with given student number.");
        return;
    }
    s->points[idx - 1] = p;
    s->sum = s->sum + p;
}

int writeFile(struct student **reg, char *input) {
    int loc = 0;
    int k = 0;
    char name[24];
    while(loc < 3) {
        if (isspace((unsigned char) input[k])) {
            while (isspace((unsigned char) input[k])) k++;
            loc++;
        }
        if (!isspace((unsigned char) input[k])) {
            int i = 0;
            int j;
            switch (loc)
            {
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
        printf("Error: Couldn't open the file");
        return -1;
    }
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

void del_register(struct student **r) {
    for (int i = 0; r[i] != NULL; i++) {
        free(r[i]);
    }
    free(r);
}