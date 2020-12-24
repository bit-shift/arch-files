#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    char* name;
    int no_of_followers; 
	// The next person in the following array should be placed at this index
    int following_index;
    // This is used when implementing the DFS algorithm
    int visited;
    struct Person **following;
}typedef Person;

struct Graph {
    // How many people are in the graph
    int length;
	// A list of people pointers. 
	// These should be the original references to each node in the graph
    struct Person** list_of_people;
}typedef Graph;

Person *createPerson(char* name, const int length);
Graph  *createGraph(const int num_names);
void 	addToGraph(Graph* g, Person* person);
void 	setNumberOfFollowers(Person*p, int number_of_followers);
void 	addPersonToFollowingList(Person *p, Person *following);
void    freePerson(Person* p);
void    freeGraph(Graph *g);
void    printFriends(Person* p);
Person *searchByName(Graph* g, const char* name);       
int     DFS(Graph* g, Person* current, Person* goal);

