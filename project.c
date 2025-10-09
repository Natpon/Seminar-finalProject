#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "project.h"
#define CELENDER_ONSITE_FILE "celender_onsite.csv"
#define CELENDER_ONLINE_FILE "celender_online.csv"
#define NUM_ROOMS 5
const char *ROOMS[] = {"Room A", "Room B", "Room C", "Room D", "Room E"};
void show_celender_onsite()
{
    FILE *file = fopen(CELENDER_ONSITE_FILE, "r");
    if (!file)
    {
        perror("Error opening celender_onsite.csv");
        return;
    }

    char line[512];
    printf("\n======================================================================================================\n");
    printf("                                    SEMINAR SCHEDULE TABLE                                     \n");
    printf("======================================================================================================\n");
    printf("| %-6s | %-8s | %-8s | %-22s | %-12s | %-5s | %-20s\n",
           "Room", "Start", "End", "Seminar Name", "Date", "Participants", "Speaker");
    printf("------------------------------------------------------------------------------------------------------\n");

    // ข้าม header
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\r\n")] = 0;

        char *Onsite_Room = strtok(line, ",");
        char *Onsite_StartTime = strtok(NULL, ",");
        char *Onsite_EndTime = strtok(NULL, ",");
        char *Onsite_SeminarName = strtok(NULL, ",");
        char *Onsite_SeminarDate = strtok(NULL, ",");
        char *participants = strtok(NULL, ",");
        char *Onsite_Speaker = strtok(NULL, ",");

        if (Onsite_Room && Onsite_StartTime && Onsite_EndTime && Onsite_SeminarName && Onsite_SeminarDate && participants && Onsite_Speaker)
        {
            printf("| %-6s | %-8s | %-8s | %-22s | %-12s | %-12s | %-12s |\n",
                   Onsite_Room, Onsite_StartTime, Onsite_EndTime, Onsite_SeminarName, Onsite_SeminarDate, participants, Onsite_Speaker);
        }
    }

    printf("------------------------------------------------------------------------------------------------------\n");
    fclose(file);
}

/*void show_celender_onsite(void)
{
    char line[1024];

    FILE *file = fopen(CELENDER_ONSITE_FILE, "r");
    if (!file)
    {
        printf("Can not open file\n");
        return;
    }

    printf("\033[1;33m==============================================\033[0m\n");
    printf("\033[1;32m%-25s %-12s %-10s %-15s\033[0m\n",
           "Seminar Name", "Date", "Participants", "Speaker");
    printf("\033[1;33m==============================================\033[0m\n");

    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = 0;
        char *SeminarName = strtok(line, ",");
        char *SeminarDate = strtok(NULL, ",");
        char *Participants = strtok(NULL, ",");
        char *Speaker = strtok(NULL, ",");

        if (SeminarName && SeminarDate && Participants && Speaker)
        {
            // แสดงข้อมูลปกติ
            printf("%-25s %-12s %-10s %-15s\n", SeminarName, SeminarDate, Participants, Speaker);
        }
    }

    fclose(file);
    printf("\033[1;33m==============================================\033[0m\n");
}*/

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
    printf("\033[1;36m1\033[0m. Add seminar\n\033[1;36m2\033[0m. Search seminar\n\033[1;36m3\033[0m. Update seminar\n\033[1;36m4\033[0m. Delete seminar\n\033[1;36m5\033[0m. Unit_Test\n\033[1;36m0\033[0m. Exit\n");
    printf("\033[1;33m********************************\033[0m\n");
}
int check_keyword_to_show(char result[100][1024], char *keyword)
{
    int Detected = 0;
    char line[1024];
    FILE *file = fopen(CELENDER_ONLINE_FILE, "r");
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
/*void update_seminar()
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
    remove(CELENDER_FILE);
    rename("temp.csv", CELENDER_FILE);

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
    FILE *file = fopen(CELENDER_ONLINE_FILE, "r");
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

    remove(CELENDER_ONLINE_FILE);
    rename("temp.csv", CELENDER_ONLINE_FILE);

    printf("Deleted %d seminar(s) successfully. Backup saved.\n", nChoices);
}

void Show_search()
{
    printf("\n*********PLEASE_SELECT**********\n");
    printf("\033[1;32m1\033[0m. Show all data\n\033[1;32m2\033[0m. Pin keyword to show\n");
    printf("********************************\n");
}
/*void search_seminar()
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
        printf("\033[3;31mIncorrect format\033[0m");
    }
}*/
void Format_Date()
{
    printf("\033[3;32mInput year is Christian Era (YYYY-MM-DD)\nExample:\033[3;33m2025-10-02\033[0m\n");
}
int timeToMinutes(const char *timeStr)
{
    int hours, minutes;
    if (sscanf(timeStr, "%d:%d", &hours, &minutes) != 2)
    {
        return -1; // รูปแบบไม่ถูกต้อง
    }
    return hours * 60 + minutes;
}

int checkRoomAvailability(const char *room, const char *seminarDate, const char *startTime, const char *endTime)
{
    FILE *file = fopen(CELENDER_ONSITE_FILE, "r");
    if (!file)
        return 1; // If file doesn't exist yet, the room is considered available

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        char existingRoom[50], existingStart[10], existingEnd[10], existingName[100];
        char existingDate[20], existingParticipants[10], existingSpeaker[50];

        // Read columns in correct order
        sscanf(line, "%49[^,],%9[^,],%9[^,],%99[^,],%19[^,],%9[^,],%49[^,\n]",
               existingRoom, existingStart, existingEnd, existingName,
               existingDate, existingParticipants, existingSpeaker);

        // Check same room and same date
        if (strcmp(existingRoom, room) == 0 && strcmp(existingDate, seminarDate) == 0)
        {
            int sStartMin = timeToMinutes(existingStart);
            int sEndMin = timeToMinutes(existingEnd);
            int newStartMin = timeToMinutes(startTime);
            int newEndMin = timeToMinutes(endTime);

            // Check for overlapping time
            if (!(newEndMin <= sStartMin || newStartMin >= sEndMin))
            {
                printf("This room is already booked between %s - %s.\n", existingStart, existingEnd);
                fclose(file);
                return 0; // Room not available
            }
        }
    }

    fclose(file);
    return 1; // Room available
}
void Onsite_update_seminar()
{
    char *keyword;
    printf("Input seminar name to update: ");
    keyword = Dynamic();
    if (!keyword) return;

    FILE *file = fopen(CELENDER_ONSITE_FILE, "r");
    FILE *temp = fopen("temp.csv", "w");
    if (!file || !temp)
    {
        printf("Error opening file\n");
        free(keyword);
        return;
    }

    char line[512];
    // copy header
    if (fgets(line, sizeof(line), file))
        fprintf(temp, "%s", line);

    int found = 0;
    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\r\n")] = 0;

        char existingRoom[50], existingStart[10], existingEnd[10], existingName[100], existingDate[20], existingParticipants[10], existingSpeaker[50];
        sscanf(line, "%49[^,], %9[^,], %9[^,], %99[^,], %19[^,], %9[^,], %49[^\n]",
               existingRoom, existingStart, existingEnd, existingName, existingDate, existingParticipants, existingSpeaker);

        if (strcmp(existingName, keyword) == 0)
        {
            found = 1;
            printf("Updating seminar: %s\n", existingName);

            char *newName = NULL, *newSpeaker = NULL, *newDate = NULL, *newStart = NULL, *newEnd = NULL, *newParticipants = NULL;

            printf("New Name (leave empty to keep current): ");
            newName = Dynamic();
            if (!newName || strlen(newName) == 0)
            {
                free(newName);
                newName = strdup(existingName);
            }

            printf("New Speaker (leave empty to keep current): ");
            newSpeaker = Dynamic();
            if (!newSpeaker || strlen(newSpeaker) == 0)
            {
                free(newSpeaker);
                newSpeaker = strdup(existingSpeaker);
            }
            printf("New Participants (leave empty to keep current): ");
            newParticipants = Dynamic();
            if (!newParticipants || strlen(newParticipants) == 0)
            {
                free(newParticipants);
                newParticipants = strdup(existingParticipants);
            }

            /*printf("New Date (leave empty to keep current): ");
            newDate = Dynamic();
            if (!newDate || strlen(newDate) == 0)
            {
                free(newDate);
                newDate = strdup(existingDate);
            }

            printf("New Start Time (leave empty to keep current): ");
            newStart = Dynamic();
            if (!newStart || strlen(newStart) == 0)
            {
                free(newStart);
                newStart = strdup(existingStart);
            }

            printf("New End Time (leave empty to keep current): ");
            newEnd = Dynamic();
            if (!newEnd || strlen(newEnd) == 0)
            {
                free(newEnd);
                newEnd = strdup(existingEnd);
            }*/

            fprintf(temp, "%s,%s,%s,%s,%s,%s,%s\n",
                    existingRoom, existingStart, existingEnd, newName, existingDate, newParticipants, newSpeaker);

            free(newName);
            free(newSpeaker);
            free(newDate);
            free(newStart);
            free(newEnd);
            free(newParticipants);
        }
        else
        {
            fprintf(temp, "%s\n", line);
        }
    }

    fclose(file);
    fclose(temp);

    remove(CELENDER_ONSITE_FILE);
    rename("temp.csv", CELENDER_ONSITE_FILE);

    if (!found) printf("Seminar not found.\n");
    else printf("Seminar updated successfully.\n");

    free(keyword);
}

void Onsite_add_seminar()
{
    char *seminarDate, *startTime, *endTime, *seminarName, *speaker;
    int roomChoice;

    printf("=== Choose a Room ===\n");
    for (int i = 0; i < NUM_ROOMS; i++)
    {
        printf("%d. %s\n", i + 1, ROOMS[i]);
    }
    printf("Select room (1-%d): ", NUM_ROOMS);
    scanf("%d", &roomChoice);
    clearBuffer();

    if (roomChoice < 1 || roomChoice > NUM_ROOMS)
    {
        printf("Invalid room choice!\n");
        return;
    }

    const char *room = ROOMS[roomChoice - 1];

    printf("Seminar Name: ");
    seminarName = Dynamic();

    printf("Speaker: ");
    speaker = Dynamic();

    printf("Date (YYYY-MM-DD): ");
    seminarDate = Dynamic();

    printf("Start Time (HH:MM): ");
    startTime = Dynamic();

    printf("End Time (HH:MM): ");
    endTime = Dynamic();

    // Check room availability
    if (!checkRoomAvailability(room, seminarDate, startTime, endTime))
    {
        printf(" Cannot add seminar: this room is busy during that time.\n");
        free(seminarName);
        free(speaker);
        free(seminarDate);
        free(startTime);
        free(endTime);
        return;
    }

    // Room is available → save record
    FILE *file = fopen(CELENDER_ONSITE_FILE, "a");
    if (!file)
    {
        printf("Error: cannot open file for writing.\n");
        return;
    }

    fprintf(file, "%s,%s,%s,%s,%s,%s\n",
            room, startTime, endTime, seminarName, seminarDate, speaker);
    fclose(file);

    printf(" Record added successfully.\n");

    free(seminarName);
    free(speaker);
    free(seminarDate);
    free(startTime);
    free(endTime);
}


/*int add_seminar(FILE *input)
{
    char SeminarName[1024], SeminarDate[1024], Speaker[1024], Participants[1024];

    FILE *file = fopen(CELENDER_FILE, "a");
    if (file == NULL)
    {
        printf("Error opening file");
        return -1;
    }

    printf("Seminar name: ");
    if (fgets(SeminarName, sizeof(SeminarName), input) == NULL)
    {
        fclose(file);
        return -2;
    }
    SeminarName[strcspn(SeminarName, "\n")] = 0;
    Format_Date();
    printf("Date of saminar : ");
    if (fgets(SeminarDate, sizeof(SeminarDate), input) == NULL)
    {
        fclose(file);
        return -3;
    }
    SeminarDate[strcspn(SeminarDate, "\n")] = 0;
    printf("Who is speaker: ");
    if (fgets(Speaker, sizeof(Speaker), input) == NULL)
    {
        fclose(file);
        return -4;
    }
    Speaker[strcspn(Speaker, "\n")] = 0;
    printf("How many of participants: ");
    if (fgets(Participants, sizeof(Participants), input) == NULL)
    {
        fclose(file);
        return -5;
    }
    Participants[strcspn(Participants, "\n")] = 0;

    fprintf(file, "%s,%s,%s,%s\n", SeminarName, SeminarDate, Participants, Speaker);
    printf("\033[1;33m===========\033[1;32mRecorded data\033[1;33m===========\033[0m\nSeminar Name is \33[1;32m%s\033[0m\nDate of Seminar is \033[1;32m%s\033[0m\nSpeaker is \033[1;32m%s\033[0m\nParticipants is \033[1;32m%s\033[0m people\n\033[1;33m=============\033[1;32mDone\033[1;33m==============\033[0m\n", SeminarName, SeminarDate, Speaker, Participants);
    fclose(file);
    return 0;
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

/*int home_program()
{
    int choice;

    while (1)
    {
        display_menu();
        printf("Enter your choice(\033[1;36monly number\033[0m): ");
        scanf("%d", &choice);
        //clearBuffer();
        if (choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 0)
        {

            printf("\033[1;33m~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\033[0m\n");

            switch (choice)
            {
            case 1:
            clearBuffer();
                if (confirm())
                {
                    int pined;

                    do
                    {
                        add_seminar(stdin);
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
            case 5 :
                system("gcc test_project.c project.c -o test.exe && test.exe");
                break;

            case 0:
                printf("Exit\n");
                return 0;
            }
        }
        else
        {
            printf("\033[3;31mIncorrect format, Please try again.\033[0m\n");
            continue;
        }
    }
}*/

int home_program()
{

    int choice;
    show_celender_onsite();
    printf("1.onsite\n2.online\n"); // กลับมาจัด
    scanf("%d", &choice);
    clearBuffer();
    if (choice == 1)
    {
        printf("You select onsite\n");
        printf("1.add seminar (onsite)\n");
        printf("2.Update seminar (onsite)\n");
        printf("3.Delete seminar (onsite)\n");
        scanf("%d", &choice);
        clearBuffer();
        if (choice == 1)
        {
            Onsite_add_seminar();
            return 0;
        }
        else if (choice == 2)
        {
            Onsite_update_seminar();
        }
        else if (choice == 3)
        {
            // Delete_seminar_onsite();
        }
        
        else
        {
            printf("\033[3;31mIncorrect format, Please try again.\033[0m\n");
            return 0;
        }
    }
    /*else if(choice == 2){
        printf("You select online\n");
        printf("1.show seminar (online)\n");
        printf("2.add seminar (online)\n");
        printf("3.Update seminar (online)\n");
        printf("4.Delete seminar (online)\n");
        scanf("%d",&choice);
        clearBuffer();
        if(choice == 1){
            show_all_seminars();
            return 0;
        }
        else if(choice == 2){
            add_seminar(online);
            return 0;
        }
        else if(choice == 3){
            update_seminar();
            return 0;
        }
        else if(choice == 4){
            delete_seminar();
            return 0;
        }
        else{
            printf("\033[3;31mIncorrect format, Please try again.\033[0m\n");
            return 0;
        }*/
    else if(choice == 4){
        system("gcc test_project.c project.c -o test.exe && test.exe");
        return 0;        
    }
    else{
        printf("\033[3;31mIncorrect format, Please try again.\033[0m\n");
    }

    printf("\n\033[1;33m=========\033[1;36mPLEASE_SELECT\033[1;33m==========\033[0m\n");
}
int logIn()
{

    printf("**********\033[1;36mLog In\033[0m**********\n");
    char *username;
    char *password;
    printf("Username : ");
    username = Dynamic();
    printf("password : ");
    password = Dynamic();
    FILE *User_file = fopen("user.csv", "r");
    if (!User_file)
    {
        printf("Cannot open user.csv\n");
        free(username);
        free(password);
        exit(1);
    }
    char line[256];
    int success = 0;
    while (fgets(line, sizeof(line), User_file))
    {
        line[strcspn(line, "\n")] = 0;
        char *file_user = strtok(line, ",");
        char *file_pass = strtok(NULL, ",");
        if (file_user && file_pass &&
            strcmp(username, file_user) == 0 &&
            strcmp(password, file_pass) == 0)
        {
            success = 1;
            break;
        }
    }
    fclose(User_file);
    free(username);
    free(password);
    if (success)
    {
        printf("\033[1;32mLog In Successfully\033[0m\n");
        home_program();
        return 1;
    }
    else
    {
        printf("\033[1;31mLog In Failed\033[0m\n");
        return 0;
    }
}

// #ifdef UNIT_TEST
//  main จะถูกคอมไพล์เฉพาะเวลารันโปรแกรมหลัก
#ifdef RUN_MAIN
int main()
{
    logIn();
    return 0;
}
#endif
// #endif
