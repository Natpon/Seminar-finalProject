#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int clearBuffer(void){
    int ch;
    do{
        ch = getchar();
    }while(ch != '\n' && ch != EOF);
}


//เปลี่ยนเป็นการจองที่เหมาะสม
char* Dynamic(){
    char Data[1024];
    
    fgets(Data,sizeof(Data),stdin);
    
    if (Data == NULL){
        return NULL;
    }
    //เจอปุ้บตัด
    else{
        Data[strcspn(Data,"\n")] = 0;
        char *save = malloc(strlen(Data)+1);
        if(save == NULL){
            return NULL;
        } 
        strcpy(save,Data);
        return save;
    }
}
void display_menu(){
    printf("*********PLEASE_SELECT**********\n");
    printf("1. Add seminar\n2. Search seminar\n3. Update seminar\n4. Delete seminar\n0. Exit\n");
    printf("********************************\n");
}
void add_seminar(){
    char *SeminarName ,*SeminarDate ,*Speaker ,*Participants ;
    
    FILE *file = fopen("celender.csv","a");
    if(file==NULL){
        printf("Can not open file.");
        }
    else{
        printf("Seminar name: ");
        SeminarName = Dynamic();
        if(SeminarName == NULL){
            printf("Something went wrong");
            free(SeminarName);
            return;
        }
        printf("Date of saminar: ");
        SeminarDate = Dynamic();
        if(SeminarDate == NULL){
            printf("Something went wrong");
            free(SeminarDate);
            return;
        }
        printf("Who is speaker: ");
        Speaker = Dynamic();
        if(Speaker == NULL){
            printf("Something went wrong");
            free(Speaker);
            return;
        } 
        printf("How many of participants: ");
        Participants = Dynamic();
        if(Participants == NULL){
            printf("Something went wrong");
            free(Participants);
            return;
        } 
   
        fprintf(file,"%s,%s,%s,%s\n", SeminarName, SeminarDate, Participants, Speaker);
        fflush(file);
        printf("%s %s %s %s",SeminarName, SeminarDate, Participants, Speaker);
        fclose(file);
        free(SeminarName);
        free(SeminarDate);
        free(Speaker);
        free(Participants);
        
    }    
}
   






int main(){
    int choice;
    while(1){
        display_menu();
        printf("Enter your choice(only number): ");
        scanf("%d", &choice);
        clearBuffer();
        
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