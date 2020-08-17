struct student {
    int stud_num;
    int points[6];
    int sum;
    char first_name[20];
    char last_name[20];
};

void printStudent(struct student *reg);
void parser(char *input, struct student *r);
void addStudent(struct student *reg, struct student *s);
void refresP(int opnro);