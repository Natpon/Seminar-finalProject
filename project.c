#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "unit_test.c"
void show_all_seminars(void) {
    char line[1024];

    FILE *file = fopen("celender.csv", "r");
    if (!file) {
        printf("Can not open file\n");
        return;
    }

    printf("\033[1;33m==============================================\033[0m\n");
    printf("\033[1;32m%-25s %-12s %-10s %-15s\033[0m\n", "Seminar Name", "Date", "Participants", "Speaker");
    printf("\033[1;33m==============================================\033[0m\n");

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; 
        char *SeminarName   = strtok(line, ",");
        char *SeminarDate   = strtok(NULL, ",");
        char *Participants  = strtok(NULL, ",");
        char *Speaker       = strtok(NULL, ",");

        if (SeminarName && SeminarDate && Participants && Speaker) {
            // แสดงข้อมูลปกติ
            printf("%-25s %-12s %-10s %-15s\n", SeminarName, SeminarDate, Participants, Speaker);
        }
    }

    fclose(file);
    printf("\033[1;33m==============================================\033[0m\n");
}


int clearBuffer(void)
{
    int ch;
    do
    {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);
}

// เปลี่ยนเป็นการจองที่เหมาะสม
char *Dynamic()
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
void display_menu()
{
    printf("\n\033[1;33m=========\033[1;36mPLEASE_SELECT\033[1;33m==========\033[0m\n");
    printf("\033[1;36m1\033[0m. Add seminar\n\033[1;36m2\033[0m. Search seminar\n\033[1;36m3\033[0m. Update seminar\n\033[1;36m4\033[0m. Delete seminar\n\033[1;36m0\033[0m. Exit\n");
    printf("\033[1;33m********************************\033[0m\n");
}
int check_keyword_to_show(char result[100][1024], char *keyword)
{
    int Detected = 0;
    char line[1024];
    FILE *file = fopen("celender.csv", "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return -1;
    }

    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = 0;
        if (strstr(line, keyword))
        {
            strcpy(result[Detected], line);

            char temp[1024];
            strcpy(temp, line); // strtok จะทำลาย string เราใช้สำรอง
            char *SeminarName = strtok(temp, ",");
            char *SeminarDate = strtok(NULL, ",");
            char *Participants = strtok(NULL, ",");
            char *Speaker = strtok(NULL, ",");

            ++Detected;
            printf("Result \033[1;33m%d\033[0m:\n", Detected);
            printf("  Seminar Name : %s\n", SeminarName);
            printf("  Date         : %s\n", SeminarDate);
            printf("  Participants : %s\n", Participants);
            printf("  Speaker      : %s\n", Speaker);
            printf("\033[35m---------------------------------\n\033[0m");
        }
    }

    if (Detected == 0)
    {
        printf("\033[1;31mNot detected\033[0m\n");
    }
    fclose(file);
    return Detected;
}
void update_seminar()
{
    char result[100][1024];
    char *keyword;

    printf("Input your keyword: ");
    keyword = Dynamic();

    int found = check_keyword_to_show(result, keyword);
    if (found == 0)
    {
        printf("Nothing to update.\n");
        free(keyword);
        return;
    }

    int choice;
    printf("Enter result \033[1;33mnumber\033[0m to update (\033[1;33m0\033[0m = cancel): ");
    scanf("%d", &choice);
    clearBuffer();

    if (choice <= 0 || choice > found)
    {
        printf("Cancel update.\n");
        free(keyword);
        return;
    }

    // ให้กรอกข้อมูลใหม่
    char *SeminarName, *SeminarDate, *Participants, *Speaker;
    printf("New Seminar name: ");
    SeminarName = Dynamic();
    printf("New Date: ");
    SeminarDate = Dynamic();
    printf("New Participants: ");
    Participants = Dynamic();
    printf("New Speaker: ");
    Speaker = Dynamic();

    char newLine[1024];
    sprintf(newLine, "%s,%s,%s,%s", SeminarName, SeminarDate, Participants, Speaker);

    FILE *file = fopen("celender.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    char line[1024];

    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = 0;
        if (strcmp(line, result[choice - 1]) == 0)
        {
            fprintf(temp, "%s\n", newLine); // เขียนข้อมูลใหม่แทน
        }
        else
        {
            fprintf(temp, "%s\n", line);
        }
    }

    fclose(file);
    fclose(temp);
    remove("celender.csv");
    rename("temp.csv", "celender.csv");

    printf("Result %d updated successfully.\n", choice);

    free(SeminarName);
    free(SeminarDate);
    free(Participants);
    free(Speaker);
    free(keyword);
}

void delete_seminar()
{
    char *keyword;
    char result[100][1024];

    printf("------------------\033[31mDelete Seminar\033[0m----------------------\n");
    printf("Input your keyword : ");
    keyword = Dynamic();

    int found = check_keyword_to_show(result, keyword);

    if (found == 0)
    {
        printf("No seminar found with keyword '%s'\n", keyword);
        return;
    }

    char input[200];
    int choices[50], nChoices = 0;

    printf("Enter result \033[1;33mnumbers\033[0m to delete\n\033[3;31mFormat\033[0m \n\033[1;35m||\033[0mIf select only one(ex:\033[1;33m1\033[0m)\n\033[1;35m||\033[0mIf select more than one(ex: \033[1;33m1 3 5\033[0m)\n\033[1;35m||\033[0mIf you do not want to delete pin : (\033[1;33m0\033[0m)\n\033[1;31m!!\033[0m!Pin accotding to the format mentioned:");
    fgets(input, sizeof(input), stdin);

    char *token = strtok(input, " ");
    while (token != NULL)
    {
        int num = atoi(token);
        if (num == 0)
        {
            printf("Cancel delete.\n");
            return;
        }
        if (num > 0 && num <= found)
        {
            choices[nChoices++] = num;
        }
        token = strtok(NULL, " ");
    }

    if (nChoices == 0)
    {
        printf("No valid numbers entered.\n");
        return;
    }

    // ลบจาก CSV
    char line[1024];
    FILE *file = fopen("celender.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    FILE *backup = fopen("backup.csv", "a");

    if (!file || !temp || !backup)
    {
        printf("Error opening file\n");
        return;
    }

    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = 0;

        int shouldDelete = 0;
        for (int i = 0; i < nChoices; i++)
        {
            if (strcmp(line, result[choices[i] - 1]) == 0)
            {
                shouldDelete = 1;
                break;
            }
        }

        if (!shouldDelete)
        {
            fprintf(temp, "%s\n", line); // เก็บที่ไม่ลบ
        }
        else
        {
            fprintf(backup, "%s\n", line); // เก็บเฉพาะที่ถูกลบไว้ backup
        }
    }

    fclose(file);
    fclose(temp);
    fclose(backup);

    remove("celender.csv");
    rename("temp.csv", "celender.csv");

    printf("Deleted %d seminar(s) successfully. Backup saved.\n", nChoices);
}

void Show_search()
{
    printf("\n*********PLEASE_SELECT**********\n");
    printf("\033[1;32m1\033[0m. Show all data\n\033[1;32m2\033[0m. Pin keyword to show\n");
    printf("********************************\n");
}
void search_seminar()
{
    char result[100][1024];
    int select;
    char *keyword;
    Show_search();
    printf("Please select(\033[1;32monly number\033[0m):");
    scanf("%d", &select);
    clearBuffer();
    if (select == 1)
    {
        show_all_seminars();
    }
    else if (select == 2)
    {
        printf("Input your keyword: ");
        keyword = Dynamic();
        int found = check_keyword_to_show(result, keyword);
        if (found == 0)
        {
            printf("No result found.\n");
        }
    }
    else
    {
        printf("Incorrect format");
    }
}
void Format_Date(){
    printf("\033[3;32mInput year is Christian Era (YYYY-MM-DD)\nExample:\033[3;33m2025-10-02\033[0m\n");
}
void add_seminar()
{
    char *SeminarName, *SeminarDate, *Speaker, *Participants;

    int choice;

    FILE *file = fopen("celender.csv", "a");

    if (file == NULL)
    {
        printf("Error opening file");
        return;
    }

    printf("Seminar name: ");
    SeminarName = Dynamic();
    if (SeminarName == NULL)
    {
        printf("Something went wrong");
        free(SeminarName);
        return;
    }
    Format_Date();
    printf("Date of saminar : ");
    SeminarDate = Dynamic();
    if (SeminarDate == NULL)
    {
        printf("Something went wrong");
        free(SeminarDate);
        return;
    }
    printf("Who is speaker: ");
    Speaker = Dynamic();
    if (Speaker == NULL)
    {
        printf("Something went wrong");
        free(Speaker);
        return;
    }
    printf("How many of participants: ");
    Participants = Dynamic();
    if (Participants == NULL)
    {
        printf("Something went wrong");
        free(Participants);
        return;
    }

    fprintf(file, "%s,%s,%s,%s\n", SeminarName, SeminarDate, Participants, Speaker);
    // fflush(file); ไม่จำเป็น
    printf("\033[1;33m===========\033[1;32mRecorded data\033[1;33m===========\033[0m\nSeminar Name is \33[1;32m%s\033[0m\nDate of Seminar is \033[1;32m%s\033[0m\nSpeaker is \033[1;32m%s\033[0m\nParticipants is \033[1;32m%s\033[0m people\n\033[1;33m=============\033[1;32mDone\033[1;33m==============\033[0m\n", SeminarName, SeminarDate, Speaker, Participants);
    fclose(file);
    free(SeminarName);
    free(SeminarDate);
    free(Speaker);
    free(Participants);
}
int confirm()
{
    int pin;
    printf("Pin \033[1;32m1\033[0m to confirm: ");
    scanf("%d", &pin);
    clearBuffer();
    if (pin == 1)
    {
        return 1; // ถูกต้อง
    }
    else
    {
        return 0; // ผิด
    }
}

int home_program()
{
    int choice;

    while (1)
    {
        display_menu();
        printf("Enter your choice(\033[1;36monly number\033[0m): ");
        scanf("%d", &choice);
        clearBuffer();
        printf("\033[1;33m~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\033[0m\n");

        switch (choice)
        {
        case 1:
            if (confirm())
            {
                int pined;

                do
                {
                    add_seminar();
                    printf("Add again? (Pin \033[1;36m1\033[0m = yes, other = no): ");
                    scanf("%d", &pined);
                    clearBuffer();

                } while (pined == 1);
            }
            else
            {
                printf("\033[3;31mPin incorrect.\033[3;36m Returning to menu.\033[0m\n");
            }
            printf("\033[3;34mBye,Go back to menu\033[0m");
            break;

        case 2:
            search_seminar();
            break;
        case 3:
            update_seminar();
            break;
        case 4:
            delete_seminar();
            break;
            /*case 5 :
                 test_unittest();
                 break;*/

        case 0:
            printf("Exit\n");
            return 0;
        default:
            printf("Invalid choice, try again.\n");
        }
    }
}

int main()
{
    home_program();
    return 0;
}
