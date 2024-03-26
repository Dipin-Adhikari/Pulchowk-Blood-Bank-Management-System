#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct User {
    char email[100];
    char password[40];
    char name[100];
    char rollNO[9];
    int age;
    char gender[2];
    char address[100];
    char blood_type[3];
};


void signup();
void login();
void sendMail(char email[100], int otp);
void saveUser(struct User user);
int alreadySignupE(char email[100]);
int alreadySignupR(char rollNo[9]);

int main() {
    int choice;

    printf("Welcome to Pulchowk Blood Bank\n");
    printf("1. Login\n");
    printf("2. Sign Up\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            login();
            break;
        case 2:
            signup();
            break;
        case 3:
            printf("Thank you for using Pulchowk Blood Bank.\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n\n");
    }

    return 0;
}
void signup() {
    struct User user;
    printf("Enter your email: ");
    scanf("%s", user.email);
    if (alreadySignupE(user.email) == 1){
        printf("Enter your password: ");
        scanf("%s", user.password);
        printf("Enter your name: ");
        scanf(" %[^\n]", user.name);
        printf("Enter your roll number: ");
        scanf("%s", user.rollNO);
        if (alreadySignupR(user.rollNO) == 1){
            printf("Enter you2r age: ");
            scanf("%d", &user.age);
            printf("Enter your gender: ");
            scanf("%s", user.gender);
            printf("Enter your address: ");
            scanf("%s", user.address);
            printf("Enter your blood type: ");
            scanf("%s", user.blood_type);
            srand(time(NULL));
            int otp = rand() % 900000 + 100000; 
            sendMail(user.email, otp);
            printf("\nCheck your email for verification.");
            printf("\n\nEnter the verification code: ");
            int eCode=0;
            scanf("%d", &eCode);
            if (otp == eCode){
                saveUser(user);
                printf("Signup successful!\n\n");
            }
            else{
                printf("Invalid Verification Code!");
            }
        }
        else {
            printf("User already exist with the same Roll Number.");
        }
    }
    else{
        printf("User already exist with the same Email.");
    }


}

void login() {
    char email[50];
    char password[20];

    printf("Enter your email: ");
    scanf("%s", email);
    printf("Enter your password: ");
    scanf("%s", password);

    printf("Login successful!\n\n");
}

void sendMail(char email[100], int otp) {
    char command[100];
    sprintf(command, "python sendmail.py %s %d", email, otp);

    system(command);
}

void saveUser(struct User user) {
    FILE *file = fopen("users.txt", "a"); 
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    fprintf(file, "%s %s %s %s %d %s %s %s\n", user.email, user.password, user.name, user.rollNO, user.age, user.gender, user.address, user.blood_type);

    fclose(file);
}

int alreadySignupE(char email[100]){
    FILE *file;
    char line[256];

    file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        exit(1);
    }
    while (fgets(line, sizeof(line), file)) {
        char storedEmail[100];
        sscanf(line, "%s", storedEmail);
        if (strcmp(storedEmail, email) == 0) {
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}

int alreadySignupR(char rollNo[9]){
    FILE *file;
    char line[256];

    file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        exit(1);
    }
    while (fgets(line, sizeof(line), file)) {
        char storedRollNo[9];
        sscanf(line, "%*s%*s%*s%*s%s", storedRollNo);

        if (strcmp(storedRollNo, rollNo) == 0) {
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}