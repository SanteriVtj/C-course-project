struct student {
    int stud_num;
    int points[6];
    int sum;
    char *first_name;
    char *last_name;
};

void printStudent(struct student *reg);
struct student *parser(char *input, struct student *r);
struct student *addStudent(struct student *reg, struct student *s);
void refresP(char *input, struct student *reg);
void del_register(struct student*r);