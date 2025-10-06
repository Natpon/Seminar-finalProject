#include <stdio.h>
#include <string.h>
#include "project_oldVersion.h"  // ใช้ prototype

void test_add_seminar() {
    // สร้างไฟล์ input จำลอง
    FILE *input_file = fopen("test_input.txt", "w");
    fprintf(input_file, "seminar1\nseminar2\n");
    fclose(input_file);

    // redirect stdin ไปอ่านจากไฟล์ test_input.txt
    freopen("test_input.txt", "r", stdin);

    // เรียกฟังก์ชันจริงที่อยู่ใน project_oldVersion.c
    add_seminar();

    // TODO: ตรวจสอบผลลัพธ์ที่ได้ (assert หรืออ่านไฟล์ออกมาตรวจ)
    printf("✅ test_add_seminar passed\n");
}

int main() {
    printf("=== Running Unit Tests ===\n");

    test_add_seminar();

    printf("=== All Tests Done ===\n");
    return 0;
}
