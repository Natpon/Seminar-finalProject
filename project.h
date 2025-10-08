#ifndef PROJECT_H
#define PROJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CELENDER_FILE "celender_oldVersion.csv"
#define UNIT_TEST_FILE "unit_test_oldVersion.c"

void show_all_seminars(void);
int clearBuffer(void);
char *Dynamic(void);
void display_menu(void);
int check_keyword_to_show(char result[100][1024], char *keyword);
void update_seminar(void);
void delete_seminar(void);
void Show_search(void);
void search_seminar(void);
void Format_Date(void);
int add_seminar(FILE *input);
void add_seminar_from_file(const char* input_filename);
int save_seminar(const char* SeminarName, const char* SeminarDate, const char* Participants, const char* Speaker);
int confirm(void);
int home_program(void);
int checkRoomAvailability(char *room, char *date, char *start, char *end);
void Onsite_add_seminar(void);
void show_celender_onsite(void);
int checkRoomAvailability(char *room, char *date, char *start, char *end);


#endif // PROJECT_H
