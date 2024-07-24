// Write a C program to assign values to each member of the following structure.
// Pass the populated structure to a function Using call-by-value and another
// function using call-by-address and print the value of each member of the
// structure.

#include <stdio.h>

struct dob
{
    int day;
    int month;
    int year;
};

struct student_info
{
    int roll_no;
    char name[50];
    float CGPA;
    struct dob age;
};

void printCallByValue(struct student_info student)
{
    printf("Roll Number: %d\n", student.roll_no);
    printf("Name: %s\n", student.name);
    printf("CGPA: %f\n", student.CGPA);
    printf("DOB: %d/%d/%d\n", student.age.day, student.age.month, student.age.year);
}

void printCallByAddress(struct student_info *student)
{
    printf("Roll Number: %d\n", student->roll_no);
    printf("Name: %s\n", student->name);
    printf("CGPA: %f\n", student->CGPA);
    printf("DOB: %d/%d/%d\n", student->age.day, student->age.month, student->age.year);
}

void main()
{
    printf("Enter the student's information:\n");
    struct student_info student;
    printf("Enter roll number: ");
    scanf("%d", &student.roll_no);
    printf("Enter name: ");
    scanf("%s", student.name);
    printf("Enter CGPA: ");
    scanf("%f", &student.CGPA);
    printf("Enter date of birth: ");
    printf("Day: ");
    scanf("%d", &student.age.day);
    printf("Month: ");
    scanf("%d", &student.age.month);
    printf("Year: ");
    scanf("%d", &student.age.year);

    printf("\n--------------------------\n\n");

    printf("Calling by value:\n");

    printCallByValue(student);

    printf("\n--------------------------\n\n");

    printf("Calling by address:\n");

    printCallByAddress(&student);
}