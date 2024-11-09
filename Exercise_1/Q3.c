#include <stdio.h>
#define MAX_GRADES 100
float gradeList[MAX_GRADES];
int gradeCount = 0;
void addGrade(float grade) {
    if (gradeCount < MAX_GRADES) {
        gradeList[gradeCount++] = grade;
    } else {
        printf("Grade list is full!\n");
    }
}
float calculateAverage() {
    if (gradeCount == 0) return 0.0;
    
    float sum = 0.0;
    for (int i = 0; i < gradeCount; i++) {
        sum += gradeList[i];
    }
    return sum / gradeCount;
}
void displayGrades() {
    if (gradeCount == 0) {
        printf("No grades to display.\n");
        return;
    }

    printf("Grades:\n");
    for (int i = 0; i < gradeCount; i++) {
        printf("%.2f\n", gradeList[i]);
    }
}
int main() {
    addGrade(90.5);
    addGrade(78.2);
    addGrade(88.9);
    displayGrades();
    
    printf("Average Grade: %.2f\n", calculateAverage());
    
    return 0;
}
