// Structure for for information about students which is used in register
struct student {
    int stud_num;
    int points[6];
    int sum;
    char first_name[21];
    char last_name[21];
};

int *sorted(struct student **reg);
void printStudent(struct student **reg);
struct student **addParser(char *input, struct student **r);
struct student **addStudent(struct student **reg, struct student *s);
struct student *findStudentByNro(int opnro, struct student **reg);
void refresP(char *input, struct student **reg);
int writeToFile(struct student **reg, char *input);
struct student **readFromFile(struct student **reg, char *input);
void delRegister(struct student **r);