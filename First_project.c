#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_TEXT 200
#define MAX_PASS 20

int main() {
    char password[MAX_PASS];
    char input[MAX_PASS];
    char diary[MAX_TEXT];
    char dateTime[100];
    int choice;

    FILE *pf;

    //  Load or set password
    pf = fopen("password.txt", "r");
    if (pf == NULL) {
        printf("Set your diary password: ");
        scanf("%19s", password);

        pf = fopen("password.txt", "w");
        fprintf(pf, "%s", password);
        fclose(pf);
    } else {
        fscanf(pf, "%s", password);
        fclose(pf);
    }

    //  LOGIN
    int attempts = 3;
    while (attempts > 0) {
        printf("\nEnter password to login: ");
        scanf("%19s", input);

        if (strcmp(password, input) == 0) {
            printf("Login successful!\n");
            break;
        } else {
            attempts--;
            printf("Wrong password! Attempts left: %d\n", attempts);
        }
    }

    if (attempts == 0) {
        printf("Access denied.\n");
        return 0;
    }

    //  MENU LOOP
    while (1) {
        printf("\n===== Digital Diary Menu =====\n");
        printf("1. Write Diary\n");
        printf("2. View Diary\n");
        printf("3. Search Entry\n");
        printf("4. Delete Entry\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        //  WRITE
        if (choice == 1) {
            FILE *file;

            time_t t;
            time(&t);
            strcpy(dateTime, ctime(&t));

            while (getchar() != '\n');

            printf("Write your diary entry:\n");
            fgets(diary, MAX_TEXT, stdin);

            file = fopen("diary.txt", "a");

            fprintf(file, "Date & Time: %s", dateTime);
            fprintf(file, "Message: %s\n", diary);
            fclose(file);

            printf("Diary entry saved!\n");
        }

        //  VIEW
        else if (choice == 2) {
            FILE *file = fopen("diary.txt", "r");

            if (file == NULL) {
                printf("No entries found!\n");
            } else {
                char line[300];
                printf("\n------ Diary ------\n");

                while (fgets(line, sizeof(line), file)) {
                    printf("%s", line);
                }
                fclose(file);
            }
        }

        //  SEARCH
        else if (choice == 3) {
            FILE *file = fopen("diary.txt", "r");
            char keyword[50];
            char line[300];
            int found = 0;

            if (file == NULL) {
                printf("No entries found!\n");
                continue;
            }

            printf("Enter keyword to search: ");
            scanf("%s", keyword);

            printf("\n--- Search Results ---\n");

            while (fgets(line, sizeof(line), file)) {
                if (strstr(line, keyword)) {
                    printf("%s", line);
                    found = 1;
                }
            }

            if (!found) {
                printf("No matching entries found.\n");
            }

            fclose(file);
        }

        //  DELETE
        else if (choice == 4) {
            FILE *file = fopen("diary.txt", "r");
            FILE *temp = fopen("temp.txt", "w");

            char keyword[50];
            char line[300];
            int deleted = 0;

            if (file == NULL) {
                printf("No entries to delete!\n");
                continue;
            }

            printf("Enter keyword to delete: ");
            scanf("%s", keyword);

            while (fgets(line, sizeof(line), file)) {
                if (strstr(line, keyword)) {
                    deleted = 1;   // skip (delete)
                } else {
                    fputs(line, temp);
                }
            }

            fclose(file);
            fclose(temp);

            remove("diary.txt");
            rename("temp.txt", "diary.txt");

            if (deleted)
                printf("Entries deleted successfully!\n");
            else
                printf("No matching entries found.\n");
        }

        //  EXIT
        else if (choice == 5) {
            printf("Thank you for using Digital Diary!\n");
             continue;
        }

        else {
            printf("Invalid choice!\n");
        }
    }
    return 0;
}
//password:1496
