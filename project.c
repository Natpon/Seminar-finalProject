#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unit_test.c"


void show_all_seminars(void) {
    char line[1024];
    FILE *file = fopen("celender.csv","r");
    if (!file) {
        printf("ไม่สามารถเปิดไฟล์ได้\n");
        return;
    }

    // ข้าม header
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // ลบ \n ทิ้ง

        // แยก field ด้วย ,
        char *SeminarName   = strtok(line, ",");
        char *SeminarDate   = strtok(NULL, ",");
        char *Participants  = strtok(NULL, ",");
        char *Speaker       = strtok(NULL, ",");

        if (SeminarName && SeminarDate && Participants && Speaker) {
            printf("%-20s %-12s %-10s %-15s\n", 
                   SeminarName, SeminarDate, Participants, Speaker);
        }
    }

    fclose(file);
    printf("=============================================\n");
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
void Show_search(){
    printf("\n*********PLEASE_SELECT**********\n");
    printf("\033[1;32m1\033[0m. Show all data\n\033[1;32m2\033[0m. Pin keyword to show\n");
    printf("********************************\n");
}
void search_seminar()
{
    char line[1024];
    int Detected = 0;
    int select;
    char *keyword;
    Show_search();
    printf("Please select(\033[1;32monly number\033[0m):");
    scanf("%d",&select);
    if(select == 1){
        show_all_seminars();
    }
    else{
        printf("Input your keyword:");
        keyword = Dynamic();
        FILE *file = fopen("celender.csv", "r");
        if (file == NULL)
        {
            printf("Error opening file");
            return;
        }
        
        while (fgets(line, sizeof(line), file))
        {
            line[strcspn(line, "\n")] = 0;
            if (strstr(line, keyword) != NULL)
            {
                char *SeminarName = strtok(line, ",");
                char *SeminarDate = strtok(NULL, ",");
                char *Participants = strtok(NULL,",");
                char *Speaker = strtok(NULL, ",");
                printf("\nResult %d:\n", Detected);
                printf("Seminar Name : %s\n", SeminarName);
                printf("Date         : %s\n", SeminarDate);
                printf("Participants : %s\n", Participants);
                printf("Speaker      : %s\n", Speaker);
                printf("---------------------------------\n");
            }
        }
        if (Detected == 0)
        {
            printf("Keyword not found\n");
        }
        else
        {
            printf("Total detected : %d result.\n", Detected);
            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        }
    }
}
//000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
void add_seminar()
{
    char *SeminarName, *SeminarDate, *Speaker, *Participants;

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
    printf("Date of saminar: ");
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
    printf("\033[1;33m===========\033[1;32mRecorded data\033[1;33m===========\033[0m\nSeminar Name is \33[1;32m%s\033[0m\nDate of Seminar is \033[1;32m%s\033[0m\nSpeaker is \033[1;32m%s\033[0m\nParticipants is \033[1;32m%s\033[0m people\n\033[1;33m=============\033[1;32mDone\033[1;33m==============\033[0m\n", SeminarName, SeminarDate, Participants, Speaker);
    fclose(file);
    free(SeminarName);
    free(SeminarDate);
    free(Speaker);
    free(Participants);
}
int confirm() {
    int pin;
    printf("Pin \033[1;32m1\033[0m to confirm: ");
    scanf("%d", &pin);
    clearBuffer();
    if (pin == 1){
        return 1;  // ถูกต้อง
    }
    else{
        return 0;  // ผิด
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
            if (confirm()) {
                add_seminar();
            } else {
                printf("Pin incorrect. Returning to menu.\n");
            }
            break;

        case 2:
            search_seminar();
            break;
        /*case 3:
             update_seminar();
             break;
        case 4:
             delete_seminar();
             break;*/
        case 5 :
             test_unittest();
             break;     

        case 0:
            printf("Exit\n");
            return 0;
        default:
            printf("Invalid choice, try again.\n");
        }
    }
}

int main() {
    home_program();
    return 0;
}
