// Students.c ... implementation of Students datatype

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "Students.h"

typedef struct _stu_rec {
	int   id;
	char  name[20];
	int   degree;
	float wam;
} sturec_t;

typedef struct _students {
	int	nstu;
	StuRec recs;
} students_t;

// build a collection of student records from a file descriptor
Students getStudents(int in)
{
	int ns;  // count of #students

	// Make a skeleton Students struct
	Students ss;
	if ((ss = malloc(sizeof (struct _students))) == NULL) {
		fprintf(stderr, "Can't allocate Students\n");
		return NULL;
	}

	// count how many student records
	int stu_size = sizeof(struct _stu_rec);
	sturec_t s;
	ns = 0;
	while (read(in, &s, stu_size) == stu_size) ns++;
	ss->nstu = ns;
	if ((ss->recs = malloc(ns*stu_size)) == NULL) {
		fprintf(stderr, "Can't allocate Students\n");
		free(ss);
		return NULL;
	}

	// read in the records
	lseek(in, 0L, SEEK_SET);
	for (int i = 0; i < ns; i++)
		read(in, &(ss->recs[i]), stu_size);

	close(in);
	return ss;
}

// show a list of student records pointed to by ss
void showStudents(Students ss)
{
	if (ss == NULL)
		printf("NULL\n");
	else if (ss->nstu == 0)
		printf("<no students>\n");
	else {
		for (int i = 0; i < ss->nstu; i++)
			showStuRec(&(ss->recs[i]));
	}
}

// show one student record pointed to by s
void showStuRec(StuRec s)
{
	printf("%7d %s %4d %0.1f\n", s->id, s->name, s->degree, s->wam);
}

// sort students records by WAM, then by name
void sortByWAM(Students ss)
{
    int nswaps;
    do{
        nswaps = 0;
        for(int i = 1; i < ss->nstu; i++){
            if(ss->recs[i].wam < ss->recs[i-1].wam){
                sturec_t hold = ss->recs[i];
                ss->recs[i] = ss->recs[i-1];
                ss->recs[i-1] = hold;
                nswaps++;
            }
            else if(ss->recs[i].wam == ss->recs[i-1].wam){
                char *name1 = ss->recs[i].name;
                char *name2 = ss->recs[i-1].name;
                for(int j = 0; name1[j] != '\0' && name2[j] != '\0'; j++){
                    int bcheck = 0, acheck= 0, scheck = 0;
                    if(name1[j] < name2[j]){
                        bcheck = 1;
                    }
                    else if(name1[j] == name2[j]){
                        scheck = 1;
                    }
                    else{
                        acheck = 1;
                    }
                    if(acheck){
                        break;
                    }
                    else if(bcheck){
                        struct _stu_rec hold = ss->recs[i];
                        ss->recs[i] = ss->recs[i-1];
                        ss->recs[i-1] = hold;
                        nswaps++;
                        break;
                    }
                }
            }
        }
    }while(nswaps > 0);
}
