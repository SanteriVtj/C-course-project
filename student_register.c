#include "project.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


struct student * initDB() {
    return malloc(sizeof(struct student));
}

void printStudent(struct student *reg) {
    // while (reg) {
    printf("%s %s\n", reg->first_name, reg->last_name);
    printf("Student number: %d\n", reg->stud_num);
    printf("Points: %d\n", reg->points);
    //     reg++;
    // }
}

void parser(char *input, struct student *r) {
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
            s->points = 0;
        }
    }
    printStudent(s);
    free(s);
}

void add_student(struct student *reg, struct student *s) {

}

void del_register(struct student *r) {
    for (int i = 0; i < sizeof(r) / sizeof(struct student *); i++) {
        free(&r[i]);
    }
    free(r);
}