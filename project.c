#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//เปลี่ยนเป็นการจองที่เหมาะสม
char* clearOverData(){
    char Data[1024];
    fgets(Data,sizeof(Data),stdin);
    if (fgets(Data,sizeof(Data),stdin) == NULL){
        return NULL;
    }
    //เจอปุ้บตัด
    Data[strcspn(Data,"\n")] = 0;
    char *save = malloc(strlen(Data)+1);
    if(save == NULL){
        return NULL;
    } 
    strcpy(save,Data);
    return save;
}
void display_menu(){
    printf("*********PLEASE_SELECT**********\n");
    printf("1. Add seminar\n2. Search seminar\n3. Update seminar\n4. Delete seminar\n0. Exit\n");
    printf("********************************\n");
}
void add_seminar(){
    char SeminarName[100],SaminarDate[100],Speaker[100];
    int Participants;
    FILE *file = fopen("Table.csv","a");
    if(file==NULL){
        printf("Can not open file.");
        return NULL;
    }
    printf("Seminar name:");
    char* SeminarName = clearOverData();
    if(SeminarName == NULL){
        printf("Technical Error");
        free(SeminarName);
        
    }
    printf("Date of saminar: \n");
    char* SeminarDate = clearOverData();
    if(SeminarDate == NULL){
        printf("Technical Error");
        free(SaminarDate);
    }
    printf("Who is speaker: ");
    char* Speaker = clearOverData();
    if(Speaker == NULL){
        printf("Technical Error");
        free(Speaker);
    } 
    printf("How many of participants: \n");
    scanf("%d",&Participants);
   
    fprintf(file,"%s,%s,%d,%s",SeminarName,SaminarDate,Participants,Speaker);
    free(SeminarName);
    free(SaminarDate);
    free(Speaker);
    fclose(file);



    
    }









int main(){
    int choice;
    while(1){
        display_menu();
        printf("Enter your choice: ");
        scanf("%d",&choice);
        //choice = getchar();
        switch(choice){
            case 1: 
                 add_seminar();
                 break;
            /*case 2:
                 search_seminar();
                 break;
            case 3:
                 update_seminar();
                 break;
            case 4:
                 delete_seminar();
                 break;*/
            case 0:
                 printf("Exis \n");
                 return 0;
            default:
                 printf("Invalid choice,try again.\n");

        }
    }

}