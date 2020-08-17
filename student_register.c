#include "project.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void printStudent(struct student *reg) {
    // printf("%s", reg[sizeof(*reg) / sizeof(struct student *)].first_name);
    for (int i = 0; i < sizeof(reg) / sizeof(struct student *); i++) {
        printf("%s %s\n", reg[i].first_name, reg[i].last_name);
        printf("Student number: %d\n", reg[i].stud_num);
        for (int j = 0; j < 6; j++) {
            printf("%d ", reg[i].points[j]);
        }
        printf("\n");
    }
}

void parser(char *input, struct student *reg) {
    struct student *s = malloc(sizeof(struct student *));
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
            char l_name[20];
            char f_name[20];
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
                    l_name[i++] = input[j];
                }
                strcpy(s->last_name, l_name);
                k = j;
                break;
            
            case 3:
                for (j = k; !isspace(input[j]); j++) {
                    f_name[i++] = input[j];
                }
                strcpy(s->first_name, f_name);
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
    addStudent(reg, s);
}

void addStudent(struct student *reg, struct student *s) {
    int last = sizeof(reg) / sizeof(struct student *);
    reg[last - 1] = *s;
    reg = realloc(reg, (last + 1) * sizeof(struct student *));
}

void refresP(int opnro) {
    
}

void del_register(struct student *r) {
    for (int i = 0; i < sizeof(r) / sizeof(struct student *); i++) {
        free(&r[i]);
    }
    free(r);
}