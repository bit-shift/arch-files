// Keeping a structure of data together
// Keegan Gyoery z5197058
// 2018-02-27

#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 64

typedef struct{
	int studentID;
	char name[MAX_NAME_LENGTH];
	int tutorial;
	int week01mark;
	int assign0mark;
} student;

void readStudent(student *s);
void printStudent(student s);

int main(int argc, char *argv[]){
	student s;
	readStudent(&s);
	printStudent(s);
	
	return EXIT_SUCCESS;
}

void readStudent(student *s){
	printf("Enter a student ID: ");
	scanf("%d", &(s->studentID));
	
	printf("Enter a tutorial: ");
	scanf("%d", &(s->tutorial));
	
	printf("Enter a week 1 mark: ");
	scanf("%d", &(s->week01mark));
	
	printf("Enter an assignment 0 mark: ");
	scanf("%d", &(s->assign0mark));
	
	//s->name = "Keegan Gyoery";
	
}

void printStudent(student s){
	printf("Student ID: %d\n", s.studentID);
	
	printf("Tutorial: %d\n", s.tutorial);
	
	printf("Week 1 Mark: %d\n", s.week01mark);
	
	printf("Assignment 0 Mark: %d\n", s.assign0mark);
	
	//s->name = "Keegan Gyoery";
	
}
