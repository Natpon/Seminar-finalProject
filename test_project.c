#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "project.h"

// ใช้ไฟล์ test แยกจาก CSV จริง
#define TEST_CSV "celender_onsite_test.csv"

// เตรียมไฟล์ test CSV ว่าง
void prepare_test_csv() {
    FILE *f = fopen(TEST_CSV, "w");
    if (!f) { perror("Cannot create test CSV"); exit(1); }
    fprintf(f, "Room,Start,End,Name,Date,Speaker\n"); // header
    fclose(f);
}

// ฟังก์ชันช่วยอ่านบรรทัดล่าสุดจาก CSV
int count_lines_in_csv() {
    FILE *f = fopen(TEST_CSV, "r");
    if (!f) return 0;
    char line[256];
    int count = 0;
    while (fgets(line, sizeof(line), f)) count++;
    fclose(f);
    return count - 1; // ลบ header
}

// เวอร์ชัน test ของ Onsite_add_seminar
void Onsite_add_seminar_with_input(const char *roomChoiceStr,
                                   const char *seminarNameStr,
                                   const char *speakerStr,
                                   const char *dateStr,
                                   const char *startStr,
                                   const char *endStr) {
    int roomChoice = atoi(roomChoiceStr);
    if (roomChoice < 1 || roomChoice > NUM_ROOMS) return;

    const char *room = ROOMS[roomChoice - 1];

    // เช็ค room availability
    FILE *file = fopen(TEST_CSV, "r");
    if (!file) return; // file must exist (prepared)
    char line[256];
    int busy = 0;
    fgets(line, sizeof(line), file); // skip header
    while (fgets(line, sizeof(line), file)) {
        char existingRoom[50], existingStart[10], existingEnd[10], existingDate[20];
        sscanf(line, "%49[^,],%9[^,],%9[^,],%*[^,],%19[^,],%*s",
               existingRoom, existingStart, existingEnd, existingDate);
        if (strcmp(existingRoom, room) == 0 && strcmp(existingDate, dateStr) == 0) {
            int sStart = timeToMinutes(existingStart);
            int sEnd = timeToMinutes(existingEnd);
            int nStart = timeToMinutes(startStr);
            int nEnd = timeToMinutes(endStr);
            if (!(nEnd <= sStart || nStart >= sEnd)) {
                busy = 1;
                break;
            }
        }
    }
    fclose(file);
    if (busy) return;

    // เพิ่ม seminar
    file = fopen(TEST_CSV, "a");
    if (!file) return;
    fprintf(file, "%s,%s,%s,%s,%s,%s\n", room, startStr, endStr, seminarNameStr, dateStr, speakerStr);
    fclose(file);
}

// Unit test
void test_Onsite_add_seminar() {
    printf("==== Testing Onsite_add_seminar ====\n");
    prepare_test_csv();

    // Case 1: ห้องว่าง → เพิ่มได้
    Onsite_add_seminar_with_input("1", "Seminar1", "Speaker1", "2025-10-10", "09:00", "10:00");
    assert(count_lines_in_csv() == 1);
    printf("✅ Test Case 1 passed: Room empty, seminar added.\n");

    // Case 2: ห้องซ้ำเวลา → เพิ่มไม่ได้
    Onsite_add_seminar_with_input("1", "Seminar2", "Speaker2", "2025-10-10", "09:30", "10:30");
    assert(count_lines_in_csv() == 1);
    printf("✅ Test Case 2 passed: Room busy, seminar rejected.\n");

    // Case 3: เวลาไม่ทับ → เพิ่มได้
    Onsite_add_seminar_with_input("1", "Seminar3", "Speaker3", "2025-10-10", "10:30", "11:30");
    assert(count_lines_in_csv() == 2);
    printf("✅ Test Case 3 passed: Room free later, seminar added.\n");

    printf("==== All Onsite_add_seminar tests passed! ====\n");
}

int main() {
    test_Onsite_add_seminar();
    return 0;
}
