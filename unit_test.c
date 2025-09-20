#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//==============================Unit test=====================================

 int Test_clearBuffer(){
    
    int ch ;
    do{
        ch = getchar();
    }while(ch != '\n' && ch != EOF){
        printf("Check,clearBuffer");
    }
    if(ch == EOF){
        printf("Check,clearBuffer");
    }
    else{
        printf("Error");
    }
}
//display_menu(){
    // this function only show the menu
    // printf("1. Add seminar\n2. Search seminar\n3. Update seminar\n4. Delete seminar\n0. Exit\n");
    // expain for easy to look
    // 1.Add seminar
    // 2.Search seminar
    // 3.Update seminar
    // 4.Delete seminar
    // 0.Exit
//}
int main()
{
    //display_menu()
        // this function only show the menu
        // expain for easy to look
    //scanf("%d",&choice);
    //clearBuffer()
    Test_clearBuffer("TestSystem");

   
    
}