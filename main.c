#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>

struct User {
    char email[100];
    char password[40];
    char name[100];
    char rollNo[9];
    int age;
    char gender[10];
    char address[100];
    char blood_type[3];
};

struct currentUser {
    char email[100];
};

struct User user;
struct currentUser cUser;

int signup();
int login();
void sendMail(char email[100], int otp);
void saveUser(struct User user);
int alreadySignupE(char email[100]);
int alreadySignupR(char rollNo[9]);
int checkEmailPassword(char email[100], char password[40]);
void acceptor();
int checkBlood(char bloodType[3]);
void sendBloodRequest(char bloodType[3], int pint, char date[20], char time[20]);
void saveRequestData(char bloodType[3], int pint, char date[20], char time[20]);


int main() {
    int choice, loginOutput, signUpOutput;

    printf("Welcome to Pulchowk Blood Bank\n");
    printf("1. Login\n");
    printf("2. Sign Up\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            loginOutput = login();
            break;
        case 2:
            signUpOutput = signup();
            loginOutput = login();

            break;
        case 3:
            printf("Thank you for using Pulchowk Blood Bank.\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n\n");
    }
    if (loginOutput==1){
        printf("1. Request Blood\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                acceptor();
                break;
            case 2:
                printf("Thank you for using Pulchowk Blood Bank.\n");
                exit(0);

            default:
                printf("\nInvalid choice. Please try again.\n\n");
        }
    }
    getch();
    return 0;
}


int signup() {
    printf("Enter your email: ");
    scanf("%s", user.email);
    if (alreadySignupE(user.email) == 1){
        printf("Enter your password: ");
        int i=0;
        while (1) {
            char ch = _getch();
            if (ch == 13) {
                user.password[i] = '\0';
                break;
            } else if (ch == 8) { 
                if (i > 0) {
                    printf("\b \b");
                    i--;
                }
            } else {
                user.password[i++] = ch;
                printf("*");
            }
        }
        printf("\nEnter your name: ");
        scanf(" %[^\n]", user.name);
        printf("Enter your roll number: ");
        scanf("%s", user.rollNo);
        if (alreadySignupR(user.rollNo) == 1){
            printf("Enter your age: ");
            scanf("%d", &user.age);
            printf("Enter your gender: ");
            scanf("%s", user.gender);
            printf("Enter your address(district): ");
            scanf("%s", user.address);
            printf("Enter your blood type: ");
            scanf("%s", user.blood_type);
            for(int i = 0; user.blood_type[i]; i++){
                user.blood_type[i] = toupper(user.blood_type[i]);
            }
            srand(time(NULL));
            int otp = rand() % 900000 + 100000;
            sendMail(user.email, otp);
            printf("\nCheck your email for verification.");
            printf("\n\nEnter the verification code: ");
            int enteredCode=0;
            scanf("%d", &enteredCode);
            if (otp == enteredCode){
                saveUser(user);
                printf("Signup successful!\n\n");
                return 1;
            }
            else{
                printf("Invalid Verification Code!");
                return 0;
            }
        }
        else {
            printf("User already exist with the same Roll Number.\n");
            return 0;
        }
    }
    else{
        printf("User already exist with the same Email.\n");
        return 0;
    }


}

int login() {
    char email[50];
    char password[20];

    printf("Enter your email: ");
    scanf("%s", email);
    printf("Enter your password: ");
    int i=0;
    while (1) {
        char ch = _getch();
        if (ch == 13) {
            password[i] = '\0';
            break;
        } else if (ch == 8) { 
            if (i > 0) {
                printf("\b \b");
                i--;
            }
        } else {
            password[i++] = ch;
            printf("*");
        }
    }
    if (checkEmailPassword(email, password) == 1){
        printf("\nLogin successful!\n\n");
        strcpy(cUser.email, email);
        return 1;
    }
    else{
        printf("Email or Password doesn't matched! ");
        return 0;
    }

    
}

void sendMail(char email[100], int otp) {
    char command[100];
    sprintf(command, "python sendOTP.py %s %d", email, otp);

    system(command);
}


void saveUser(struct User user) {
    FILE *file = fopen("users.txt", "a"); 
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    fprintf(file, "%s %s %s %s %d %s %s %s\n", user.email, user.password, user.name, user.rollNo, user.age, user.gender, user.address, user.blood_type);

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
        char storedrollNo[9];
        sscanf(line, "%*s%*s%*s%*s%s", storedrollNo);

        if (strcmp(storedrollNo, rollNo) == 0) {
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}

int checkEmailPassword(char email[100], char password[40]){
    FILE *file;
    char line[256];

    file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        exit(1);
    }
    while (fgets(line, sizeof(line), file)) {
        char storedEmail[100], storedPassword[40];
        sscanf(line, "%s", storedEmail);
        sscanf(line, "%*s%s", storedPassword);

        if (strcmp(storedEmail, email) == 0 && strcmp(storedPassword, password)) {
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}


void acceptor(){
    printf("Which blood type do you want? ");
    char bloodType[3], date[20], time[20];
    scanf("%s", bloodType);
    for(int i = 0; bloodType[i]; i++){
        bloodType[i] = toupper(bloodType[i]);
    }
    if (checkBlood(bloodType) == 1){

        printf("There is %s blood in our blood bank.\n");
        int pint=0;
        printf("How much pint (1 pint = 473 milliliters) do you want? ");
        scanf("%d", &pint);
        printf("When is the blood needed(date)? ");
        scanf(" %[^\n]", date);
        printf("When is the blood needed(time)? ");
        scanf(" %[^\n]", time);
        printf("We will contact you later.\n");
        for(int i = 0; date[i]; i++){
                date[i] = toupper(date[i]);
        }
        for(int i = 0; time[i]; i++){
                time[i] = toupper(time[i]);
        }
        sendBloodRequest(bloodType, pint, date, time);
        saveRequestData(bloodType, pint, date, time);
    }
    else{
        printf("There's no blood.");
    }
 
}


int checkBlood(char bloodType[3]){
    FILE *file;
    char line[256];

    file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        exit(1);
    }
    while (fgets(line, sizeof(line), file)) {
        char storedBloodType[3], cEmail[100];
        sscanf(line, "%s", cEmail);
        sscanf(line, "%*s%*s%*s%*s%*s%*s%*s%*s%s", storedBloodType);

        if (strcmp(storedBloodType, bloodType) == 0 && strcmp(cEmail, cUser.email) != 0) {
            
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void sendBloodRequest(char bloodType[3], int pint, char date[20], char time[20]) {
    FILE *file;
    char line[256];

    file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        exit(1);
    }
    while (fgets(line, sizeof(line), file)) {
        char storedBloodType[3], cEmail[100];
        sscanf(line, "%*s%*s%*s%*s%*s%*s%*s%*s%s", storedBloodType);
        sscanf(line, "%s", cEmail);
        if (strcmp(storedBloodType, bloodType) == 0 && strcmp(cEmail, cUser.email) != 0) {
            char command[100], email[100];
            sscanf(line, "%s", email);
            sprintf(command, "python sendRequest.py %s %s %d %s %s", email, bloodType, pint, date, time);

            system(command);
        }
    }

    fclose(file);
}


void saveRequestData(char bloodType[3], int pint, char date[20], char time[20]){
    FILE *file;
    char line[256];

    file = fopen("request.txt", "a");
    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        exit(1);
    }
    fprintf(file, "%s %s %d %s %s\n", cUser.email, bloodType, pint, date, time);

    fclose(file);
}