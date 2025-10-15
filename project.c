#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define CELENDER_ONSITE_FILE "celender_onsite.csv"
#define CELENDER_ONLINE_FILE "celender_online.csv"
#define USER_FILE "user.csv"
#define NUM_ROOMS 5

const char *ROOMS[NUM_ROOMS] = {"Room A", "Room B", "Room C", "Room D", "Room E"};

// ===== Utility Functions =====
void clearBuffer()
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;
}

char *readLine()
{
    char buf[1024];
    if (fgets(buf, sizeof(buf), stdin) == NULL)
        return NULL;
    buf[strcspn(buf, "\r\n")] = 0;
    char *res = malloc(strlen(buf) + 1);
    if (!res)
        return NULL;
    strcpy(res, buf);
    return res;
}

int isNumber(const char *str)
{
    if (!str || strlen(str) == 0)
        return 0;
    for (int i = 0; str[i]; i++)
        if (!isdigit(str[i]))
            return 0;
    return 1;
}

int is_leap_year(int y) { return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0); }

int isValidDateFormat(const char *date)
{
    if (!date || strlen(date) != 10)
        return 0;
    int y, m, d;
    if (sscanf(date, "%4d-%2d-%2d", &y, &m, &d) != 3)
        return 0;
    if (y < 1900 || y > 2100 || m < 1 || m > 12)
        return 0;
    int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (is_leap_year(y))
        days_in_month[2] = 29;
    return d >= 1 && d <= days_in_month[m];
}

int is_past_date(const char *date)
{
    int y, m, d;
    if (sscanf(date, "%4d-%2d-%2d", &y, &m, &d) != 3)
        return 1;
    time_t t = time(NULL);
    struct tm *now = localtime(&t);
    if (y < now->tm_year + 1900)
        return 1;
    if (y == now->tm_year + 1900 && m < now->tm_mon + 1)
        return 1;
    if (y == now->tm_year + 1900 && m == now->tm_mon + 1 && d < now->tm_mday)
        return 1;
    return 0;
}

int isValidTimeFormat(const char *timeStr)
{
    if (!timeStr || strlen(timeStr) != 5 || timeStr[2] != ':')
        return 0;
    int h, m;
    if (sscanf(timeStr, "%2d:%2d", &h, &m) != 2)
        return 0;
    return (h >= 0 && h <= 23 && m >= 0 && m <= 59);
}

int timeToMinutes(const char *timeStr)
{
    int h, m;
    if (sscanf(timeStr, "%d:%d", &h, &m) != 2)
        return -1;
    return h * 60 + m;
}

int isEndAfterStart(const char *startTime, const char *endTime)
{
    int s = timeToMinutes(startTime), e = timeToMinutes(endTime);
    if (s == -1 || e == -1)
        return 0;
    return e > s;
}

int checkRoomAvailability(const char *fileName, const char *room, const char *date, const char *start, const char *end)
{
    FILE *file = fopen(fileName, "r");
    if (!file)
        return 1; // available if file doesn't exist
    char line[512];
    while (fgets(line, sizeof(line), file))
    {
        char r[50], s[10], e[10], n[100], d[20], p[10], sp[50];
        sscanf(line, "%49[^,],%9[^,],%9[^,],%99[^,],%19[^,],%9[^,],%49[^\n]", r, s, e, n, d, p, sp);
        if (strcmp(r, room) == 0 && strcmp(d, date) == 0)
        {
            int s1 = timeToMinutes(s), e1 = timeToMinutes(e);
            int s2 = timeToMinutes(start), e2 = timeToMinutes(end);
            if (!(e2 <= s1 || s2 >= e1))
            {
                fclose(file);
                return 0; // not available
            }
        }
    }
    fclose(file);
    return 1; // available
}

// ===== Show Seminars =====
void show_seminars(const char *fileName)
{
    FILE *file = fopen(fileName, "r");
    if (!file)
    {
        printf("No data available.\n");
        return;
    }
    char line[512];
    printf("Room  | Start  | End    | Seminar Name           | Date       | Participants | Speaker\n");
    printf("-------------------------------------------------------------------------------\n");
    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\r\n")] = 0;
        char r[50], s[10], e[10], n[100], d[20], p[10], sp[50];
        if (sscanf(line, "%49[^,],%9[^,],%9[^,],%99[^,],%19[^,],%9[^,],%49[^\n]", r, s, e, n, d, p, sp) == 7)
        {
            printf("%-6s| %-6s | %-6s | %-22s | %-10s | %-12s | %-12s\n", r, s, e, n, d, p, sp);
        }
    }
    fclose(file);
}

// ===== Add Seminar =====
void add_seminar(const char *fileName)
{
    printf("=== Choose Room ===\n");
    for (int i = 0; i < NUM_ROOMS; i++)
        printf("%d. %s\n", i + 1, ROOMS[i]);

    
    printf("Select room (1-%d): ", NUM_ROOMS);
    char *roomChoiceStr = readLine();
    int roomChoice = atoi(roomChoiceStr);
    free(roomChoiceStr);
    clearBuffer();

    if (roomChoice < 1 || roomChoice > NUM_ROOMS)
    {
        printf("Invalid room\n");
        return;
    }
    const char *room = ROOMS[roomChoice - 1];

    char *name = NULL, *speaker = NULL, *date = NULL, *start = NULL, *end = NULL, *participants = NULL;

    printf("Seminar Name: ");
    name = readLine();
    printf("Speaker: ");
    speaker = readLine();

    do
    {
        printf("Date (YYYY-MM-DD): ");
        date = readLine();
        if (!isValidDateFormat(date) || is_past_date(date))
        {
            printf("Invalid date\n");
            free(date);
            date = NULL;
        }
    } while (!date);

    do
    {
        printf("Start Time (HH:MM): ");
        start = readLine();
    } while (!start || !isValidTimeFormat(start));

    do
    {
        printf("End Time (HH:MM): ");
        end = readLine();
        if (!end || !isValidTimeFormat(end) || !isEndAfterStart(start, end))
        {
            free(end);
            end = NULL;
            printf("Invalid end time\n");
        }
    } while (!end);

    do
    {
        printf("Participants: ");
        participants = readLine();
        if (!participants || !isNumber(participants))
        {
            free(participants);
            participants = NULL;
            printf("Invalid number\n");
        }
    } while (!participants);

    if (!checkRoomAvailability(fileName, room, date, start, end))
    {
        printf("Room busy at this time.\n");
        goto cleanup;
    }

    FILE *file = fopen(fileName, "a");
    if (!file)
    {
        printf("Cannot open file.\n");
        goto cleanup;
    }
    fprintf(file, "%s,%s,%s,%s,%s,%s,%s\n", room, start, end, name, date, participants, speaker);
    fclose(file);
    printf("Seminar added successfully!\n");

cleanup:
    free(name);
    free(speaker);
    free(date);
    free(start);
    free(end);
    free(participants);
}

// ===== Delete Seminar =====
void delete_seminar(const char *fileName)
{
    char *target;
    printf("Enter seminar name to delete: ");
    target = readLine();
    if (!target) return;

    FILE *file = fopen(fileName, "r");
    FILE *temp = fopen("temp.csv", "w");
    FILE *history = fopen("deleted_seminar_real.csv", "a"); // เก็บ history
    if (!file || !temp || !history)
    {
        printf("Cannot open file.\n");
        free(target);
        if (file) fclose(file);
        if (temp) fclose(temp);
        if (history) fclose(history);
        return;
    }

    char line[512];
    int found = 0;
    while (fgets(line, sizeof(line), file))
    {
        char lineCopy[512];
        strcpy(lineCopy, line);
        char *nameField = strtok(lineCopy, ","); // Room
        nameField = strtok(NULL, ",");           // Start
        nameField = strtok(NULL, ",");           // End
        nameField = strtok(NULL, ",");           // Seminar Name
        if (nameField && strcmp(nameField, target) != 0)
            fputs(line, temp);
        else
        {
            found = 1;
            fputs(line, history); // บันทึกลง history ก่อนลบ
        }
    }

    fclose(file);
    fclose(temp);
    fclose(history);
    remove(fileName);
    rename("temp.csv", fileName);

    if (found)
        printf("Seminar deleted and saved to history.\n");
    else
        printf("Not found.\n");

    free(target);
}
void show_deleted_history()
{
    char *keyword;
    printf("Enter keyword to search in deleted seminars (leave empty to show all): ");
    keyword = readLine();

    FILE *file = fopen("deleted_seminar_real.csv", "r");
    if (!file)
    {
        printf("No deleted seminar history.\n");
        free(keyword);
        return;
    }

    char line[512];
    int found = 0;
    printf("Deleted Seminars:\n");
    printf("Room  | Start  | End    | Seminar Name | Date | Participants | Speaker\n");
    printf("-----------------------------------------------------------\n");

    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\r\n")] = 0; // ตัด \n ออก
        if (!keyword || strlen(keyword) == 0 || strstr(line, keyword))
        {
            printf("%s\n", line);
            found = 1;
        }
    }

    if (!found)
        printf("No matching deleted seminars found.\n");

    fclose(file);
    free(keyword);
}



// ===== Update Seminar =====
void update_seminar(const char *fileName)
{
    char *target;
    printf("Enter seminar name to update: ");
    target = readLine();
    if (!target)
        return;

    FILE *file = fopen(fileName, "r");
    FILE *temp = fopen("temp.csv", "w");
    if (!file || !temp)
    {
        free(target);
        return;
    }

    char line[512];
    int found = 0;
    while (fgets(line, sizeof(line), file))
    {
        char r[50], s[10], e[10], n[100], d[20], p[10], sp[50];
        sscanf(line, "%49[^,],%9[^,],%9[^,],%99[^,],%19[^,],%9[^,],%49[^\n]", r, s, e, n, d, p, sp);
        if (strcmp(n, target) == 0)
        {
            found = 1;
            printf("New name (leave empty to keep): ");
            char *newName = readLine();
            if (!newName || strlen(newName) == 0)
            {
                free(newName);
                newName = strdup(n);
            }

            printf("New speaker (leave empty to keep): ");
            char *newSpeaker = readLine();
            if (!newSpeaker || strlen(newSpeaker) == 0)
            {
                free(newSpeaker);
                newSpeaker = strdup(sp);
            }

            fprintf(temp, "%s,%s,%s,%s,%s,%s,%s\n", r, s, e, newName, d, p, newSpeaker);
            free(newName);
            free(newSpeaker);
        }
        else
            fputs(line, temp);
    }
    fclose(file);
    fclose(temp);
    remove(fileName);
    rename("temp.csv", fileName);
    if (found)
        printf("Seminar updated.\n");
    else
        printf("Not found.\n");
    free(target);
}

// ===== Login =====
int logIn()
{
    printf("Username: ");
    char *user = readLine();
    printf("Password: ");
    char *pass = readLine();

    FILE *f = fopen(USER_FILE, "r");
    if (!f)
    {
        printf("Cannot open user file.\n");
        free(user);
        free(pass);
        return 0;
    }

    char line[256];
    int success = 0;
    while (fgets(line, sizeof(line), f))
    {
        line[strcspn(line, "\n")] = 0;
        char *fileUser = strtok(line, ","), *filePass = strtok(NULL, ",");
        if (fileUser && filePass && strcmp(user, fileUser) == 0 && strcmp(pass, filePass) == 0)
        {
            success = 1;
            break;
        }
    }
    fclose(f);
    free(user);
    free(pass);
    if (success)
        printf("Login successful\n");
    else
        printf("Login failed\n");
    return success;
}

// ===== Home Menu =====
void home_program()
{
    int choice;
    while (1)
    {
        show_seminars(CELENDER_ONSITE_FILE);
        printf("1. Manage onsite seminar\n2. Unit_Test\n3. E2E_test\n0. Exit\nChoice(number only): ");
        scanf("%d", &choice);
        clearBuffer();
        if (choice == 1)
        {
            printf("1.Add \n2.Update \n3.Delete\n4.Search Deleted History\nChoice(number only): ");
            scanf("%d", &choice);
            clearBuffer();
            if (choice == 1)
                add_seminar(CELENDER_ONSITE_FILE);
            else if (choice == 2)
                update_seminar(CELENDER_ONSITE_FILE);
            else if (choice == 3)
                delete_seminar(CELENDER_ONSITE_FILE);
            else if (choice == 4)
                show_deleted_history();    
        }
        else if (choice == 2)
        {
            system("gcc -D RUN_UNIT_TEST UnitTest.c project.c -o UnitTest.exe && ./UnitTest.exe");
        }
        else if (choice == 3)
        {
            system("gcc -D RUN_E2E test_deleted_history.c -o test_deleted_history.exe && ./test_deleted_history.exe");
        }
        else if (choice == 0)
            break;
        else
        {
            printf("\033[3;31mIncorrect format, Please try again.\033[0m\n");
        }
    }
}

// ===== Main =====
#ifdef RUN_MAIN
int main()
{
    if (logIn())
        home_program();
    return 0;
}
#endif
