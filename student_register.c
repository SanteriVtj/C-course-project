#include "project.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void printStudent(struct student *reg) {
    for (int i = 0; reg[i].stud_num != 0; i++) {
        printf("%s %s\n", reg[i].first_name, reg[i].last_name);
        printf("Student number: %d\n", reg[i].stud_num);
        for (int j = 0; j < 6; j++) {
            printf("%d ", reg[i].points[j]);
        }
        printf("\n");
        printf("%d\n", reg[i].sum);
    }
}

struct student *addParser(char *input, struct student *reg) {
    struct student *s = malloc(sizeof(struct student));
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

struct student *addStudent(struct student *reg, struct student *s) {
    int last;
    for (last = 0; reg[last].stud_num != 0; last++);
    reg[last] = *s;
    reg = realloc(reg, (last + 2) * sizeof(struct student));
    reg[last + 1].stud_num = 0;
    free(s);
    return reg;
}

struct student *find_studentnr(int opnro, struct student *reg) {
    for (int i = 0; reg[i].stud_num != 0; i++) {
        if (reg[i].stud_num == opnro) {
            return &reg[i];
        }
    }
    return NULL;
}

void refresP(char *input, struct student *reg) {
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
