#ifndef PROJECT_H
#define PROJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// กำหนดค่าคงที่สำหรับไฟล์ CSV
#define CELENDER_ONSITE_FILE "celender_onsite.csv"
#define CELENDER_ONLINE_FILE "celender_online.csv"

// ประกาศฟังก์ชันทั้งหมดที่ใช้ใน project.c

void show_celender_onsite(void);
void show_celender_online(void);
void add_seminar(void);
void edit_seminar(void);
void delete_seminar(void);

// แก้ declaration ให้ตรงกับ implementation
int checkRoomAvailability(const char *room, const char *date, const char *startTime, const char *endTime);
void Onsite_add_seminar(void);

// ฟังก์ชันอื่น ๆ ที่คุณมีในโปรเจกต์
// int someOtherFunction(...);

#endif // PROJECT_H
