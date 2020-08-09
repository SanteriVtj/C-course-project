#include "project.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct student * initDB() {
    return malloc(sizeof(struct student));
}

void parser(char *input, struct student *r) {
    struct student *s = malloc(sizeof(struct student *));
    while(*input) {
        while (isspace((unsigned char) *input)) input++;
    }
    // realloc(input, sizeof(r) + sizeof(struct student *));
}

void add_student(struct student *s) {

}

void del_register(struct student *r) {
    for (int i = 0; i < sizeof(r) / sizeof(struct student *); i++) {
        free(&r[i]);
    }
    free(r);
}