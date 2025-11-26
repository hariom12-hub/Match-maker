#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char password[50];
    char gender[10];
    char preference[10];
    int age;
} User;

/* ==========================
        USER FUNCTIONS
   ========================== */

void registerUser() {
    User u;
    printf("\n=== Register ===\n");
    printf("Username: "); scanf("%s", u.username);
    printf("Password: "); scanf("%s", u.password);
    printf("Gender (M/F): "); scanf("%s", u.gender);
    printf("Interested in (M/F): "); scanf("%s", u.preference);
    printf("Age: "); scanf("%d", &u.age);

    FILE *fp = fopen("users.txt", "a");
    fprintf(fp, "%s %s %s %s %d\n", 
            u.username, u.password, u.gender, u.preference, u.age);
    fclose(fp);

    printf("Registered successfully!\n");
}

int loginUser(char username[]) {
    char pass[50];
    printf("\n=== Login ===\n");
    printf("Username: "); scanf("%s", username);
    printf("Password: "); scanf("%s", pass);

    FILE *fp = fopen("users.txt", "r");
    if (!fp) {
        printf("No users registered yet.\n");
        return 0;
    }

    User u;

    while (fscanf(fp, "%s %s %s %s %d", u.username, u.password, 
                  u.gender, u.preference, &u.age) != EOF) {
        if (strcmp(username, u.username) == 0 &&
            strcmp(pass, u.password) == 0) {
            fclose(fp);
            printf("Login successful!\n");
            return 1;
        }
    }

    fclose(fp);
    printf("Login failed.\n");
    return 0;
}

void listUsers(char currentUser[]) {
    FILE *fp = fopen("users.txt", "r");
    if (!fp) {
        printf("No users found.\n");
        return;
    }

    User u;

    printf("\n=== Available Profiles ===\n");

    while (fscanf(fp, "%s %s %s %s %d", u.username, u.password,
                  u.gender, u.preference, &u.age) != EOF) {
        if (strcmp(u.username, currentUser) != 0) {
            printf("User: %s (Age %d, Gender %s)\n",
                   u.username, u.age, u.gender);
        }
    }

    fclose(fp);
}

/* ==========================
        MATCH FUNCTIONS
   ========================== */

void likeUser(char liker[], char liked[]) {
    FILE *fp = fopen("likes.txt", "a");
    fprintf(fp, "%s %s\n", liker, liked);
    fclose(fp);
    printf("You liked %s!\n", liked);
}

void viewMatches(char username[]) {
    FILE *fp = fopen("likes.txt", "r");
    if (!fp) {
        printf("No likes yet.\n");
        return;
    }

    char a[50], b[50];
    int found = 0;

    printf("\n=== Your Matches ===\n");

    while (fscanf(fp, "%s %s", a, b) != EOF) {
        if (strcmp(a, username) == 0) {
            // Check for mutual like
            FILE *fp2 = fopen("likes.txt", "r");
            char x[50], y[50];

            while (fscanf(fp2, "%s %s", x, y) != EOF) {
                if (strcmp(x, b) == 0 && strcmp(y, username) == 0) {
                    printf("❤️ Match with %s!\n", b);
                    found = 1;
                }
            }

            fclose(fp2);
        }
    }

    if (!found)
        printf("No matches yet.\n");

    fclose(fp);
}

/* ==========================
          MAIN PROGRAM
   ========================== */

int main() {
    int choice;
    char currentUser[50];

    while (1) {
        printf("\n===== DATING APP =====\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        if (choice == 1) {
            registerUser();
        } 
        else if (choice == 2) {
            if (loginUser(currentUser)) {
                
                int opt;
                while (1) {
                    printf("\n=== Menu (%s) ===\n", currentUser);
                    printf("1. View Profiles\n");
                    printf("2. Like a User\n");
                    printf("3. View Matches\n");
                    printf("4. Logout\n");
                    printf("Choose: ");
                    scanf("%d", &opt);

                    if (opt == 1) {
                        listUsers(currentUser);
                    }
                    else if (opt == 2) {
                        char user[50];
                        printf("Enter username to like: ");
                        scanf("%s", user);
                        likeUser(currentUser, user);
                    }
                    else if (opt == 3) {
                        viewMatches(currentUser);
                    }
                    else if (opt == 4) {
                        break;
                    }
                }
            }
        }
        else if (choice == 3) {
            printf("Exiting app...\n");
            break;
        }
        else {
            printf("Invalid option.\n");
        }
    }

    return 0;
}