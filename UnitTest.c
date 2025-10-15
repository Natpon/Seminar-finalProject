#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "project.h"  // ไฟล์ main seminar functions ของคุณ

#define TEST_FILE "test_seminar.csv"

// ===== Helpers =====
void create_test_file() {
    FILE *f = fopen(TEST_FILE, "w");
    fprintf(f, "Room A,09:00,10:00,Seminar1,2030-10-10,10,Dr.A\n");
    fprintf(f, "Room B,11:00,12:00,Seminar2,2030-10-10,20,Dr.B\n");
    fclose(f);
}

void remove_test_file() {
    remove(TEST_FILE);
}

// ===== Unit Tests =====
void test_room_availability() {
    create_test_file();

    // ห้องว่าง: Room A, 10:00-11:00 => should be available
    assert(checkRoomAvailability(TEST_FILE, "Room A", "2030-10-10", "10:00", "11:00") == 1);

    // ห้องไม่ว่าง: Room A, 09:30-09:45 => overlaps Seminar1
    assert(checkRoomAvailability(TEST_FILE, "Room A", "2030-10-10", "09:30", "09:45") == 0);

    // ห้องไม่ว่าง: Room B, 11:30-12:30 => overlaps Seminar2
    assert(checkRoomAvailability(TEST_FILE, "Room B", "2030-10-10", "11:30", "12:30") == 0);

    remove_test_file();
    printf("test_room_availability passed\n");
}

void test_past_date() {
    // สมมติวันนี้เป็น 2025-10-09
    assert(is_past_date("2020-01-01") == 1); // อดีต
    assert(is_past_date("2030-01-01") == 0); // อนาคต
    assert(is_past_date("2025-10-08") == 1); // ก่อนวันนี้
    printf("test_past_date passed\n");
}

void test_time_validation() {
    assert(isValidTimeFormat("09:00") == 1);
    assert(isValidTimeFormat("23:59") == 1);
    assert(isValidTimeFormat("24:00") == 0); // invalid
    assert(isValidTimeFormat("12:60") == 0); // invalid
    assert(isValidTimeFormat("ab:cd") == 0); // invalid
    printf("test_time_validation passed\n");
}

void test_date_validation() {
    assert(isValidDateFormat("2025-02-28") == 1);
    assert(isValidDateFormat("2024-02-29") == 1); // leap year
    assert(isValidDateFormat("2023-02-29") == 0); // not leap year
    assert(isValidDateFormat("2025-13-01") == 0); // invalid month
    assert(isValidDateFormat("2025-00-10") == 0); // invalid month
    assert(isValidDateFormat("abcd-ef-gh") == 0); // invalid format
    printf("test_date_validation passed\n");
}

// ===== Main for Unit Test =====
#ifdef RUN_UNIT_TEST
int main() {
    test_room_availability();
    test_past_date();
    test_time_validation();
    test_date_validation();
    printf("All tests passed!\n");
    //system("gcc -D RUN_MAIN project.c -o seminar.exe && ./seminar.exe && Test && test1234");
    return 1;
}
#endif
