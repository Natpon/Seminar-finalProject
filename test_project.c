#include <stdio.h>
#include <assert.h>
#include "project.h"

/*void test_Dynamic() {
    // ทดสอบรับข้อมูลจาก stdin (mock stdin ไม่ง่ายใน C ธรรมดา)
    // สามารถทดสอบ logic string ได้ถ้า refactor ฟังก์ชันให้รับ char* แทน stdin
    printf("Manual test: กรุณาพิมพ์ 'Hello' แล้ว Enter\n");
    char* result = Dynamic();
    assert(result != NULL);
    assert(strcmp(result, "Hello") == 0);
    printf("test_Dynamic passed\n");
}

// ตัวอย่าง unit test สำหรับ clearBuffer



/*
void test_save_seminar() {
    // ลบข้อมูลเดิม (optional)
    // remove(CELENDER_FILE);
    int result = save_seminar("สัมมนาทดสอบ", "2025-10-08", "100", "ดร.สมชาย");
    assert(result == 0);

    // ตรวจสอบว่าไฟล์มีข้อมูลที่เพิ่มเข้าไป
    FILE* file = fopen(CELENDER_FILE, "r");
    char line[1024];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "สัมมนาทดสอบ")) {
            found = 1;
            break;
        }
    }
    fclose(file);
    assert(found == 1);
    printf("test_save_seminar passed\n");
}
*/

void test_add_seminar_with_freopen() {
    // สร้างไฟล์ input สำหรับ mock stdin
    FILE *f = fopen("input.txt", "w");
    fprintf(f, "TEst\n2025-10-08\nTEst\n100\n");
    fclose(f);

    // เปิดไฟล์ input.txt เพื่อใช้เป็น input
    f = fopen("input.txt", "r");
    add_seminar(f);
    fclose(f);

    // ตรวจสอบผลลัพธ์ในไฟล์ CSV
    FILE *csv = fopen(CELENDER_FILE, "r");
    char line[1024];
    int found = 0;
    while (fgets(line, sizeof(line), csv)) {
        if (strstr(line, "สัมมนาทดสอบ")) found = 1;
    }
    fclose(csv);
    assert(found == 1);
    printf("test_add_seminar_with_freopen passed\n");
}

int main() {
    // ทดสอบฟังก์ชันที่ไม่ต้องการ mock stdin ก่อน
    
    test_add_seminar_with_freopen();
    printf("All manual tests passed!\n");
    return 0;
}
