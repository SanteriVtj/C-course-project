#include <stdio.h>
#include "project.h"

int main(void) {
    int loop = 1;
    char buffer[51];
    while (loop) {
        printf("Insert student: ");
        char *ret = fgets(buffer, 20, stdin);
        if (ret == NULL) {
            printf("fget returned NULL");
            break;
        }



        switch (ret[0])
        {
        case 'Q':
            printf("Bye!\n");
            loop = 0;
            break;

        case 'A':
            
            break;
        
        default:
            printf("%s", buffer);
            break;
        }
    }
}