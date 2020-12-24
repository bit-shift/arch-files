// Students.c ... implementation of Students datatype

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include "Students.h"

typedef struct _stu_rec {
	int   id;
	char  name[20];
	int   degree;
	float wam;
} sturec_t;

typedef struct _students {
    int    nstu;
    StuRec recs;
} students_t;

// build a collection of student records from a file descriptor
Students getStudents(int in)
{
    int ns;
    Students ret;
    if((ret = malloc(sizeof(struct _students))) == NULL){
        fprintf(stderr, "Can't allocate space for Students\n");
        return NULL;
    }
    int stu_size = sizeof(struct _stu_rec);
    sturec_t s;
    ns = 0;
    while(read(in, &s, stu_size) == stu_size){
        ns++;
    }
    ret->nstu = ns;
    if((ret->recs = malloc(ns*stu_size)) == NULL){
        fprintf(stderr, "Can't allocate space for Students\n");
        return NULL;
    }
    lseek(in, 0, SEEK_SET);
    for (int i = 0; i < ns; i++)
        read(in, &(ret->recs[i]), stu_size);
    close(in);
    return ret;
}

// show a list of student records pointed to by ss
void showStudents(Students ss)
{
	assert(ss != NULL);
	for (int i = 0; i < ss->nstu; i++)
		showStuRec(&(ss->recs[i]));
}

// show one student record pointed to by s
void showStuRec(StuRec s)
{
	printf("%7d %s %4d %0.1f\n", s->id, s->name, s->degree, s->wam);
}
