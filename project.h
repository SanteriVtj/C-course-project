struct student {
    int stud_num;
    int points[6];
    int sum;
    char first_name[20];
    char last_name[20];
};

void parser(char *input, struct student *r);
void addStudent(struct student *reg, struct student *s);
struct student * initDB();
void refresP(int opnro);