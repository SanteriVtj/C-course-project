struct student {
    int stud_num;
    int points[6];
    int sum;
    char first_name[21];
    char last_name[21];
};

void printStudent(struct student **reg);
struct student **addParser(char *input, struct student **r);
struct student **addStudent(struct student **reg, struct student *s);
void refresP(char *input, struct student **reg);
void del_register(struct student **r);