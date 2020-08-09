void parser(char *input, struct student *r);
void add_student(struct student *s);

struct student {
    int stud_num;
    int points;
    char first_name[20];
    char last_name[20];
};