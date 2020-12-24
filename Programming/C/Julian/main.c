#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#define MAX_BUF 2048


int main(int argc, char** argv) {
	
	// store the input arguments
	int number_of_people;
	char *name_of_person1;
	char *name_of_person2;
	
	// set the number of people, and person 1 and 2 names
	number_of_people = atoi(argv[1]);
	name_of_person1 = argv[2];
	name_of_person2 = argv[3];
	
	Graph *g = createGraph(number_of_people);
	
	// read from standard in 
	char input[MAX_BUF];
	int counter = 0, f_counter, n;
	char *line, *name, *follow_name;
	Person *new_person, *follow, *follower;

	line = fgets(input, MAX_BUF-1, stdin);
	
	while (line != NULL) {
		if (strcmp("\n", line) == 0) {
			line = fgets(input, MAX_BUF-1, stdin);
			continue;
		}

		if (counter < number_of_people) {
			n = strlen(line);
			line[n-1] = '\0';
			// printf("%s\n", line);
			new_person = createPerson(line, number_of_people);
			addToGraph(g, new_person);
		}
		else if (counter < 2*number_of_people) {
			f_counter = 0;
			n = strlen(line);
			line[n-1] = '\0';
			name = strtok(line, " ");
			follower = searchByName(g, name);
			
			follow_name = strtok(NULL, " ");
			while (follow_name != NULL) {
				follow = searchByName(g, follow_name);
				addPersonToFollowingList(follower, follow);
				f_counter++;
				follow_name = strtok(NULL, " ");
			}
			setNumberOfFollowers(follower, f_counter);
		}
	
		counter++;
		line = fgets(input, MAX_BUF-1, stdin);
	}

	Person *person1 = searchByName(g, name_of_person1);
	Person *person2 = searchByName(g, name_of_person2);

	printFriends(person1);
	printFriends(person2);

	printf("The path from %s to %s is:", person1->name, person2->name);
	if (!DFS(g, person1, person2)) {
		printf("\nThere is no path from %s to %s", person1->name, person2->name);
	}
	printf("\n");

	freeGraph(g);

	return 0;
}
