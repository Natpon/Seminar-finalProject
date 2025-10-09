// File: test_deleted_history.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ===== ตัวฟังก์ชัน search_history แบบแก้ไข =====
void search_history_keyword(const char *keyword) {
    FILE *file = fopen("deleted_seminars.csv", "r");
    if (!file) {
        printf("No deleted history file.\n");
        return;
    }

    char line[512];
    int found = 0;
    // อ่าน header
    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        printf("No deleted history file.\n");
        return;
    }

    printf("Search result for '%s':\n", keyword);
    while (fgets(line, sizeof(line), file)) {
        if (!keyword || strlen(keyword) == 0 || strstr(line, keyword)) {
            printf("%s", line);
            found = 1;
        }
    }

    if (!found) printf("No matching history found.\n");

    fclose(file);
}

// ===== Helper: สร้าง mock CSV =====
void create_mock_deleted_csv() {
    FILE *file = fopen("deleted_seminars.csv", "w");
    if (!file) {
        printf("Cannot create mock CSV.\n");
        exit(1);
    }
    // Header
    fprintf(file, "Room,Start,End,Name,Date,Participants,Speaker\n");
    // Data
    fprintf(file, "Room A,09:00,10:00,Python Basics,2025-10-10,10,Mr. A\n");
    fprintf(file, "Room B,10:00,11:00,Java Advanced,2025-10-11,8,Ms. B\n");
    fprintf(file, "Room C,11:00,12:00,C Programming,2025-10-12,12,Dr. C\n");
    fclose(file);
}
#ifdef RUN_E2E
// ===== Main E2E Test =====
int main() {
    printf("=== E2E Test: Deleted History Search ===\n");

    // สร้าง mock CSV
    create_mock_deleted_csv();

    // Test 1: Search keyword that exists
    printf("\nTest 1: Search 'Python'\n");
    search_history_keyword("Python");

    // Test 2: Search keyword that does not exist
    printf("\nTest 2: Search 'Ruby'\n");
    search_history_keyword("Ruby");

    // Test 3: Search with empty keyword (show all)
    printf("\nTest 3: Show all\n");
    search_history_keyword("");

    // Clean up
    remove("deleted_seminars.csv");

    printf("\n=== E2E Test Completed ===\n");
    return 0;
}
#endif