#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include "graph.h"

Person *createPerson(char *name, int length) {
	// Allocate memory and initalise struct variables
	Person *p = malloc(sizeof(struct Person));
	if (p == NULL) {
		fprintf(stderr, "Malloc failed.\n");
		exit(1);
	}
	p->name = strdup(name);
	p->no_of_followers = 0;
	p->following_index = 0;
	p->visited = 0;
	p->following = malloc(length*sizeof(struct Person *));
	if (p->following == NULL) {
		fprintf(stderr, "Malloc failed.\n");
		exit(1);
	}
	return p;
}


void setNumberOfFollowers(Person *p, int number_of_followers) {
	if (p == NULL) {
		fprintf(stderr, "Person is NULL.\n");
		exit(1);
	}
	p->no_of_followers = number_of_followers;
	return;
}

Graph *createGraph(const int num_names) {
	// Allocate memory and initalise struct variables
	Graph *g = malloc(sizeof(struct Graph));
	if (g == NULL) {
		fprintf(stderr, "Malloc failed.\n");
		exit(1);
	}
	g->length = 0;
	g->list_of_people = malloc(num_names*sizeof(struct Person *));
	if (g->list_of_people == NULL) {
		fprintf(stderr, "Malloc failed.\n");
		exit(1);
	}
	return g;
}

void addToGraph(Graph *g, Person *person) {
    // Add person to the following list of people in Graph* g.
	// The length is useful here
	if (g == NULL || person == NULL) {
		fprintf(stderr, "Person and/or Graph is NULL.\n");
		exit(1);
	}
	g->list_of_people[g->length] = person;
	g->length++;
	return;
}

void addPersonToFollowingList(Person *p, Person *following) {
	// Add following to the following list in Person p.
	// The following_index is useful here
	if (p == NULL || following == NULL) {
		fprintf(stderr, "Person is NULL.\n");
		exit(1);
	}
	p->following[p->following_index] = following;
	p->following_index++;
	return;
}

void printFriends(Person *p) {
	if (p == NULL) {
		fprintf(stderr, "Person is NULL.\n");
		exit(1);
	}
	if (p->no_of_followers == 0) {
		printf("%s follows no one!\n", p->name);
		return;
	}
	
	printf("%s follows:", p->name);
	for (int i = 0; i < p->following_index; i++) {
		printf(" %s", p->following[i]->name);
	}
	printf("\n");
	return;
}


Person* searchByName(Graph *g, const char *name) {
	// Seach the graph for a node with this name; strcmp() will be useful
	// Will return NULL if person is not found
	if (g == NULL) {
		fprintf(stderr, "Graph is NULL.\n");
		exit(1);
	}
	for (int i = 0; i < g->length; i++) {
		if (strcmp(name, g->list_of_people[i]->name) == 0) {
			return g->list_of_people[i];
		}
	}
	return NULL;
}	

int DFS(Graph *g, Person *current, Person *goal) {
    // Implement DFS
	if (g == NULL || current == NULL || goal == NULL) {
		fprintf(stderr, "An argument is NULL.\n");
		exit(1);
	}
	Person *check;
	printf(" %s", current->name);
	current->visited = 1;
	if (strcmp(current->name, goal->name) == 0) {
		return 1;
	}
	for (int i = 0; i < current->no_of_followers; i++) {
		check = current->following[i];
		if (!(check->visited)) {
			if (DFS(g, check, goal)) return 1;
		}
	}	
	return 0;
}

void freePerson(Person *p) {
	// Free p
	if (p == NULL) {
		fprintf(stderr, "Person is NULL.\n");
		exit(1);
	}
	free(p->name);
	free(p->following);
	free(p);
	return;
}

void freeGraph(Graph *g) {
	// Free graph structures and then the graph
	if (g == NULL) {
		fprintf(stderr, "Graph is NULL.\n");
		exit(1);
	}
	for (int i = 0; i < g->length; i++) {
		freePerson(g->list_of_people[i]);
	}
	free(g->list_of_people);
	free(g);
	return;
}

