#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
typedef struct {
    char *username;
    char *password;
    char *role;
    char *time;

} User;
char *Dynamic_file()
{
    char Data[1024];

    if (fgets(Data, sizeof(Data), file_name) == NULL)
    {
        return NULL;
    }

    // เจอปุ้บตัด
    else
    {
        Data[strcspn(Data, "\n")] = 0;
        char *save = malloc(strlen(Data) + 1);
        if (save == NULL)
        {
            return NULL;
        }
        strcpy(save, Data);
        return save;
    }
}
char *Dynamic_stdin()
{
    char Data[1024];

    if (fgets(Data, sizeof(Data), stdin) == NULL)
    {
        return NULL;
    }

    // เจอปุ้บตัด
    else
    {
        Data[strcspn(Data, "\n")] = 0;
        char *save = malloc(strlen(Data) + 1);
        if (save == NULL)
        {
            return NULL;
        }
        strcpy(save, Data);
        return save;
    }
}
int clearBuffer(void)
{
    int ch;
    do
    {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);
}
int login(User *user){
    char *inputUser,*putPass;
    printf("Enter username : ");
    inputUser = Dynamic();
    printf("Enter password : ");
    inputPass =Dynamic();
    FILE *user_file = fopen("user.csv","r");
    if(!file){
        printf("Error: cannot open user_file");
    }
    char *line;
    file_name = user.csv;
    line = Dynamic_file();


}
int main()
{
    User currentUser;

    if (!login(&currentUser))
    {
        printf("Login failed. Exiting...\n");
        return 0;
    }

    int choice;
    while (1)
    {
        displayMenu(currentUser);
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearBuffer();

        if (choice == 0)
            break;
        else if (choice == 1)
        {
            if (strcmp(currentUser.role, "Admin") == 0)
                printf("Access granted to Add seminar.\n");
            else
                printf("Access denied.\n");
        }
        else if (choice == 2)
            printf("Search seminar function (to implement)\n");
        else
            printf("Invalid choice.\n");
    }

    // free memory ของ struct
    free(currentUser.username);
    free(currentUser.role);

    printf("Goodbye!\n");
    return 0;
}
