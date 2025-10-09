#ifndef PROJECT_H
#define PROJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// กำหนดค่าคงที่สำหรับไฟล์ CSV
#define CELENDER_ONSITE_FILE "celender_onsite.csv"
#define CELENDER_ONLINE_FILE "celender_online.csv"
#define NUM_ROOMS 5
extern const char *ROOMS[];
int checkRoomAvailability(const char *fileName, const char *room, const char *date, const char *start, const char *end);
int is_past_date(const char *date);
int isValidTimeFormat(const char *timeStr);
int isValidDateFormat(const char *date);
#endif // PROJECT_H