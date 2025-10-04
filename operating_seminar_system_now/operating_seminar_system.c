#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *username;
    char *role;
} User;

#define USER_FILE "user.csv"

// ฟังก์ชันช่วยอ่าน string จาก stdin แบบ dynamic
char *Dynamic_stdin()
{
    char Data[1024];
    if (fgets(Data, sizeof(Data), stdin) == NULL)
        return NULL;
    Data[strcspn(Data, "\n")] = 0;
    char *save = malloc(strlen(Data) + 1);
    strcpy(save, Data);
    return save;
}

int clearBuffer(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
    return 0;
}

// ฟังก์ชัน login แบบอ่านจาก user.csv
int login(User *user)
{
    char *inputUser, *inputPass;
    FILE *user_file = fopen(USER_FILE, "r");
    if (!user_file)
    {
        printf("Error: cannot open %s\n", USER_FILE);
        return 0;
    }

    printf("Enter username: ");
    inputUser = Dynamic_stdin();
    printf("Enter password: ");
    inputPass = Dynamic_stdin();

    char line[256];
    while (fgets(line, sizeof(line), user_file))
    {
        line[strcspn(line, "\n")] = 0;
        char *fileUser = strtok(line, ",");
        char *filePass = strtok(NULL, ",");
        char *fileRole = strtok(NULL, ",");
        if (fileUser && filePass && fileRole)
        {
            if (strcmp(inputUser, fileUser) == 0 && strcmp(inputPass, filePass) == 0)
            {
                user->username = malloc(strlen(fileUser) + 1);
                strcpy(user->username, fileUser);
                user->role = malloc(strlen(fileRole) + 1);
                strcpy(user->role, fileRole);
                fclose(user_file);
                free(inputUser);
                free(inputPass);
                return 1; // login สำเร็จ
            }
        }
    }

    fclose(user_file);
    free(inputUser);
    free(inputPass);
    return 0; // login ล้มเหลว
}

// ================== Dummy Functions ===================
void addSeminar() { printf("[Dummy] Add Seminar called\n"); }
void searchSeminar() { printf("[Dummy] Search Seminar called\n"); }
void updateSeminar() { printf("[Dummy] Update Seminar called\n"); }
void deleteSeminar() { printf("[Dummy] Delete Seminar called\n"); }
void manageSeminar() { printf("[Dummy] Manage Seminar called\n"); }
void approveParticipants() { printf("[Dummy] Approve Participants called\n"); }
void viewMySeminars() { printf("[Dummy] View My Seminars called\n"); }
void uploadSlides() { printf("[Dummy] Upload Slides called\n"); }
void viewFeedback() { printf("[Dummy] View Feedback called\n"); }
void viewSchedule() { printf("[Dummy] View Schedule called\n"); }
void giveFeedback() { printf("[Dummy] Give Feedback called\n"); }

// ================== Menu ตาม Role ======================
void showMenu(User *user)
{
    int choice;
    while (1)
    {
        printf("\nLogged in as %s (%s)\n", user->username, user->role);
        if (strcmp(user->role, "Admin") == 0)
        {
            printf("1. Add Seminar\n2. Search Seminar\n3. Update Seminar\n4. Delete Seminar\n0. Exit\nChoice: ");
            scanf("%d", &choice);
            clearBuffer();
            switch (choice)
            {
            case 1:
                addSeminar();
                break;
            case 2:
                searchSeminar();
                break;
            case 3:
                updateSeminar();
                break;
            case 4:
                deleteSeminar();
                break;
            case 0:
                return;
            default:
                printf("Invalid choice.\n");
                break;
            }
        }
        else if (strcmp(user->role, "Organizer") == 0)
        {
            printf("1. Manage Seminar\n2. Approve Participants\n3. Search Seminar\n0. Exit\nChoice: ");
            scanf("%d", &choice);
            clearBuffer();
            switch (choice)
            {
            case 1:
                manageSeminar();
                break;
            case 2:
                approveParticipants();
                break;
            case 3:
                searchSeminar();
                break;
            case 0:
                return;
            default:
                printf("Invalid choice.\n");
                break;
            }
        }
        else if (strcmp(user->role, "Speaker") == 0)
        {
            printf("1. View My Seminars\n2. Upload Slides\n3. View Feedback\n0. Exit\nChoice: ");
            scanf("%d", &choice);
            clearBuffer();
            switch (choice)
            {
            case 1:
                viewMySeminars();
                break;
            case 2:
                uploadSlides();
                break;
            case 3:
                viewFeedback();
                break;
            case 0:
                return;
            default:
                printf("Invalid choice.\n");
                break;
            }
        }
        else if (strcmp(user->role, "Participant") == 0)
        {
            printf("1. View Schedule\n2. Give Feedback\n0. Exit\nChoice: ");
            scanf("%d", &choice);
            clearBuffer();
            switch (choice)
            {
            case 1:
                viewSchedule();
                break;
            case 2:
                giveFeedback();
                break;
            case 0:
                return;
            default:
                printf("Invalid choice.\n");
                break;
            }
        }
        else if (strcmp(user->role, "Viewer") == 0)
        {
            printf("1. View Schedule\n0. Exit\nChoice: ");
            scanf("%d", &choice);
            clearBuffer();
            switch (choice)
            {
            case 1:
                viewSchedule();
                break;
            case 0:
                return;
            default:
                printf("Invalid choice.\n");
                break;
            }
        }
        else
        {
            printf("Unknown role. Exiting menu.\n");
            return;
        }
    }
}

// ================== Main =============================
int main()
{
    /*User currentUser;
    if (!login(&currentUser)) {
        printf("Login failed. Exiting...\n");
        return 0;
    }

    showMenu(&currentUser);

    // free memory
    free(currentUser.username);
    free(currentUser.role);

    printf("Goodbye!\n");
    return 0;*/
    while (1)
    {

        char *username, *role, *password;
        FILE *file = fopen("operating_seminar_system_now/user.csv", "a");
        if (file == NULL)
        {
            printf("Error opening file\n");
            return 1;
        }
        printf("Enter username: ");
        username = Dynamic_stdin();
        printf("Enter role (Admin, Organizer, Speaker, Participant, Viewer): ");
        role = Dynamic_stdin();
        printf("Enter password: ");
        password = Dynamic_stdin();
        fprintf(file, "%s,%s,%s \n", username, password, role);
        fclose(file);
        free(username);
        free(role);
        free(password);
    }
}
