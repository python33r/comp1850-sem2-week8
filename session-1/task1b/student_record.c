/**
 * Implementation of a student record management system using structures
 * 
 * This program demonstrates the use of structures in C to manage student data
 * including personal information and module marks.
 */

#include <stdio.h>
#include <string.h>
#include "student_record.h"

/**
 * Calculate the average mark for a student
 * 
 * @param student The student whose average mark is to be calculated
 * @return float The average mark
 */
float calculate_average(Student student) {
    return (student.marks[0] + student.marks[1] + student.marks[2]) / 3.0f;
}

/**
 * Display student information including name, ID, marks, and average
 * 
 * @param student The student whose information is to be displayed
 */
void display_student(Student student) {
    printf("    Name : %s\n", student.name);
    printf("      ID : %d\n", student.id);

    printf("   Marks : %.1f %.1f %.1f\n",
        student.marks[0],
        student.marks[1],
        student.marks[2]
    );

    printf("Avg mark : %.2f\n", calculate_average(student));
}

/*
 * Program entry point
 */
int main(void) {
    Student student;

    strcpy(student.name, "Jenny Jones");
    student.id = 12345;
    student.marks[0] = 75.0f;
    student.marks[1] = 68.5f;
    student.marks[2] = 81.0f;
    
    display_student(student);
    
    return 0;
}
