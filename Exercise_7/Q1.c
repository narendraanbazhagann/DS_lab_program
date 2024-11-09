#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    int studentID;
    char name[50];
    int age;
    char course[50];
} Student;
Student* searchStudentByID(Student* students, int n, int studentID) {
    for (int i = 0; i < n; i++) {
        if (students[i].studentID == studentID) {
            return &students[i]; 
        }
    }
    return NULL; // If student ID not found
}

int main() {
    int n;
    printf("Enter the number of students: ");
    scanf("%d", &n);
    Student* students = (Student*)malloc(n * sizeof(Student));
    if (students == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        printf("Enter details for student %d:\n", i + 1);
        printf("Student ID: ");
        scanf("%d", &students[i].studentID);
        printf("Name: ");
        getchar(); 
        fgets(students[i].name, 50, stdin);
        students[i].name[strcspn(students[i].name, "\n")] = '\0'; 
        printf("Age: ");
        scanf("%d", &students[i].age);
        printf("Course: ");
        getchar(); 
        fgets(students[i].course, 50, stdin);
        students[i].course[strcspn(students[i].course, "\n")] = '\0'; 
    }

    int searchID;
    printf("Enter student ID to search for: ");
    scanf("%d", &searchID);

    
    Student* student = searchStudentByID(students, n, searchID);
    if (student != NULL) {
        printf("Student found:\n");
        printf("ID: %d\n", student->studentID);
        printf("Name: %s\n", student->name);
        printf("Age: %d\n", student->age);
        printf("Course: %s\n", student->course);
    } else {
        printf("Student with ID %d not found.\n", searchID);
    }

   
    free(students);

    return 0;
}
