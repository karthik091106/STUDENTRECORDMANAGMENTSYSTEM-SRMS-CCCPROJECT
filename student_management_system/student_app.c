#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUD_FILE "students.txt"
#define CRE_FILE  "credentials.txt"

char currentUser[50];
char currentRole[20];

// ------------------- LOGIN -------------------
int login() {
    char u[50], p[50], r[50];
    char inUser[50], inPass[50];

    printf("USERNAME: ");
    scanf("%s", inUser);
    printf("PASSWORD: ");
    scanf("%s", inPass);

    FILE *fp = fopen(CRE_FILE, "r");
    if (!fp) {
        printf("Credential file missing!\n");
        return 0;
    }

    while (fscanf(fp, "%s %s %s", u, p, r) == 3) {
        // Trim trailing \r and \n
        int len = strlen(r);
        while (len > 0 && (r[len - 1] == '\n' || r[len - 1] == '\r')) {
            r[len - 1] = '\0';
            len--;
        }

        if (strcmp(inUser, u) == 0 && strcmp(inPass, p) == 0) {
            strcpy(currentUser, u);
            strcpy(currentRole, r);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

// ------------------- STUDENT FUNCTIONS -------------------
void addStudent() {
    int roll;
    char name[50];
    float mark;

    printf("Roll: ");
    scanf("%d", &roll);
    printf("Name: ");
    scanf(" %[^\n]", name);
    printf("Mark: ");
    scanf("%f", &mark);

    // Replace spaces with _ for file storage
    for (int i = 0; name[i]; i++) if (name[i] == ' ') name[i] = '_';

    FILE *fp = fopen(STUD_FILE, "a");
    fprintf(fp, "%d %s %.2f\n", roll, name, mark);
    fclose(fp);

    printf("Student added!\n");
}

void displayStudents() {
    FILE *fp = fopen(STUD_FILE, "r");
    if (!fp) { printf("No student file!\n"); return; }

    int roll;
    char name[50];
    float mark;

    printf("Roll\tName\tMark\n");
    printf("----\t----\t----\n");
    while (fscanf(fp, "%d %s %f", &roll, name, &mark) == 3) {
        for (int i = 0; name[i]; i++) if (name[i] == '_') name[i] = ' ';
        printf("%d\t%s\t%.2f\n", roll, name, mark);
    }

    fclose(fp);
}

void searchStudent() {
    char findName[50];
    int roll;
    char name[50];
    float mark;

    printf("Enter name to search: ");
    scanf(" %[^\n]", findName);

    // Convert spaces to _ for comparison (because names are stored with _)
    for (int i = 0; findName[i]; i++)
        if (findName[i] == ' ') findName[i] = '_';

    FILE *fp = fopen(STUD_FILE, "r");
    if (!fp) { 
        printf("No student file!\n"); 
        return; 
    }

    int found = 0;
    while (fscanf(fp, "%d %s %f", &roll, name, &mark) == 3) {
        if (strcmp(findName, name) == 0) {
            // Convert underscores back to spaces for display
            for (int i = 0; name[i]; i++)
                if (name[i] == '_') name[i] = ' ';
            printf("Found: %d %s %.2f\n", roll, name, mark); // keep roll
            found = 1;
        }
    }

    fclose(fp);
    if (!found) printf("Student not found!\n");
}

void deleteStudent() {
    int delRoll;
    printf("Enter roll to delete: ");
    scanf("%d", &delRoll);

    FILE *fp = fopen(STUD_FILE, "r");
    if (!fp) { printf("No student file!\n"); return; }

    FILE *temp = fopen("temp.txt", "w");
    int roll;
    char name[50];
    float mark;
    int found = 0;

    while (fscanf(fp, "%d %s %f", &roll, name, &mark) == 3) {
        if (roll != delRoll) fprintf(temp, "%d %s %.2f\n", roll, name, mark);
        else found = 1;
    }

    fclose(fp);
    fclose(temp);

    remove(STUD_FILE);
    rename("temp.txt", STUD_FILE);

    if (found) printf("Student deleted!\n");
    else printf("Roll not found!\n");
}

void updateStudent() {
    int updateRoll;
    printf("Enter roll to update: ");
    scanf("%d", &updateRoll);

    FILE *fp = fopen(STUD_FILE, "r");
    if (!fp) { printf("No student file!\n"); return; }

    FILE *temp = fopen("temp.txt", "w");
    int roll;
    char name[50];
    float mark;
    int found = 0;

    while (fscanf(fp, "%d %s %f", &roll, name, &mark) == 3) {
        if (roll == updateRoll) {
            found = 1;
            char newName[50];
            float newMark;

            printf("New Name: ");
            scanf(" %[^\n]", newName);
            for (int i = 0; newName[i]; i++) if (newName[i] == ' ') newName[i] = '_';

            printf("New Mark: ");
            scanf("%f", &newMark);

            fprintf(temp, "%d %s %.2f\n", roll, newName, newMark);
        } else {
            fprintf(temp, "%d %s %.2f\n", roll, name, mark);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(STUD_FILE);
    rename("temp.txt", STUD_FILE);

    if (found) printf("Student updated!\n");
    else printf("Roll not found!\n");
}

// ------------------- MENUS -------------------
void adminMenu() {
    int c;
    while (1) {
        printf("\nADMIN MENU\n1.Add\n2.Display\n3.Search\n4.Update\n5.Delete\n6.Logout\n");
        scanf("%d", &c);
        if (c == 1) addStudent();
        else if (c == 2) displayStudents();
        else if (c == 3) searchStudent();
        else if (c == 4) updateStudent();
        else if (c == 5) deleteStudent();
        else return;
    }
}

void staffMenu() {
    int c;
    while (1) {
        printf("\nSTAFF MENU\n1.Add\n2.Display\n3.Search\n4.Update\n5.Logout\n");
        scanf("%d", &c);
        if (c == 1) addStudent();
        else if (c == 2) displayStudents();
        else if (c == 3) searchStudent();
        else if (c == 4) updateStudent();
        else return;
    }
}


void guestMenu() {
    int c;
    while (1) {
        printf("\nGUEST MENU\n1.Display\n2.Search\n3.Logout\n");
        scanf("%d", &c);
        if (c == 1) displayStudents();
        else if (c == 2) searchStudent();
        else return;
    }
}

// ------------------- MAIN -------------------
int main() {
    if (!login()) {
        printf("Invalid login!\n");
        return 0;
    }

    printf("Logged in as: %s\n", currentRole);

    if (strcmp(currentRole, "admin") == 0)
        adminMenu();
    else if (strcmp(currentRole, "staff") == 0)
        staffMenu();
    else
        guestMenu();

    return 0;
}
