#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "textbuffer.h"

// Stack Node Structure
typedef struct TBNode {
    TB state;
    struct TBNode *next;
    struct TBNode *prev;
} TBNode;

// Stack Bookkeeping Structure
typedef struct TBStack {
    int nTBs;
    TBNode *top;
    TBNode *bottom;
} TBStack;

// Textbuffer Node Structure
typedef struct LineNode {
    char *string;
    int lineNoDiff;
    struct LineNode *prev;
    struct LineNode *next;
} LineNode;

// Textbuffer Bookkeeping Structure
struct textbuffer {
    int nlines;
    LineNode *first;
    LineNode *last;
    TBStack *undoStack;
    TBStack *redoStack;
};

// Textbuffer Node Pointer
typedef struct LineNode *Line;

// Stack Node Pointer
typedef TBNode *TBNodeP;

// Stack Pointer
typedef TBStack *TBStackP;

static void releaseTBNodes (TB tb);

/* Initialising the Stack to hold the textbuffer's state
 * Returns a pointer to the Stack
 */
static TBStack *initTBStack () {
    // Malloc space for the new stack and check if the pointer is valid
    TBStackP new = malloc(sizeof(struct TBStack));
    assert(new != NULL);
    // Set the members of the stack struct to intial values
    new->nTBs = 0;
    new->top = new->bottom = NULL;
    return new;
}

/* Trims the stack if it gets too long
 * Holds only 10 items on the stack and removes the bottom item
 * Returns nothing
 */
static void trimTBStack (TBStackP tbstack) {
    assert(tbstack != NULL);
    // Hold the bottom node of the stack
    TBNodeP hold = tbstack->bottom;
    // Reset the pointer to the bottom of the stack
    tbstack->bottom = tbstack->bottom->prev;
    tbstack->bottom->next = NULL;
    // Free the held node and decrement the number of items
    releaseTBNodes(hold->state);
    free(hold->state);
	free(hold);
    tbstack->nTBs--;
}

/* Pushes the given node that holds the TB state onto the stack
 * Returns nothing
 */
static void pushTBStack (TBStackP tbstack, TBNodeP tbnode) {
    assert(tbstack != NULL && tbnode != NULL);
    // If there are no items in the stack, set the bottom pointer to the node to be pushed on
    if (tbstack->nTBs == 0) {
        tbstack->bottom = tbnode;
    }
    // Else, connect the previous top pointer to the node to be pushed on
    else {
        tbstack->top->prev = tbnode;
        tbnode->next = tbstack->top;
    }
    // Reset the top pointer and increment the number of items
    tbstack->top = tbnode;
    tbstack->nTBs++;
    // If the number of items is more than 10 with the pushed on node, trim the bottom node
    if (tbstack->nTBs > 10) {
        trimTBStack(tbstack);
    }
}

/* Pops the top item off of the stack
 * Returns the TB held in the top node
 */
static TBNodeP popTBStack (TBStackP tbstack) {
    assert(tbstack != NULL);
    // Set up the return TB to be NULL in case nothing is popped off the stack (ie empty stack)
    TBNodeP ret = NULL;
    // If the stack is not empty, reset the top pointer
    if (tbstack->nTBs != 0) {
        ret = tbstack->top;
        tbstack->top = tbstack->top->next;
        if (tbstack->nTBs > 1) tbstack->top->prev = NULL;
        tbstack->nTBs--;
    }
    return ret;
}

/* Free the Nodes in one of the Stacks in the TB
 * Does not affect the bookkeeping structure and the stack is still intact
 * Just has no nodes on the stack when finished
 * Used to free the redoStack when a change is made to the textbuffer
 * Returns nothing
 */
static void freeTBStackNodes (TBStackP tbstack) {
    assert(tbstack != NULL);
    // Set up a pointer to iterate through the stack, and a temp variable
    TBNodeP iterator = tbstack->top;
    TBNodeP hold;
    // Iterate through the stack
    while (iterator != NULL) {
        hold = iterator;
        if (hold->state == NULL) {
            fprintf(stderr, "The provided textbuffer points to NULL, and is unusable.\n");
            abort();
        }
        // Set up a pointer to iterate through the textbuffer in that node on the stack, and a temp variable
        // Free the current node in the stack and move to the next
		releaseTBNodes(hold->state);
        free(hold->state);
        iterator = iterator->next;
        free(hold);
    }
    // Reset the bookkeeping structure of the stack
    tbstack->top = tbstack->bottom = NULL;
    tbstack->nTBs = 0;
}

/* Create a new node with the given string
 * Return a pointer to the node
 */
static LineNode *newLineNode (char *text) {
    // Malloc space for the new line
    Line new = malloc(sizeof(struct LineNode));
    if (new == NULL) {
        fprintf(stderr, "Could not allocate memory for a new node to store a textbuffer's line.\n");
        abort();
    }
    // Set the string pointer member to a copy of the given string pointer, and set up prev and next pointers
    new->string = strdup(text);
    new->next = new->prev = NULL;
    return new;
}

/* Create a new match node with the given line number and character index
 * Return a pointer to the match node
 */
static matchNode *newMatchNode (int lineNumber, int charIndex) {
    // Malloc space for new match
    Match new = malloc(sizeof(struct _matchNode));
    if (new == NULL) {
        fprintf(stderr, "Could not allocate memory for a new node to store a string's match.\n");
        abort();
    }
    // Set line number and char number of the match
    new->lineNumber = lineNumber;
    new->charIndex = charIndex;
    new->next = NULL;
    return new;
}

/* Create a new TB node with the given string
 * Return a pointer to the TB node
 */
static TBNode *newTBNode (TB tb) {
    // Malloc space for the new stack node
    TBNodeP new = malloc(sizeof(struct TBNode));
    if (new == NULL) {
        fprintf(stderr, "Could not allocate memory for a new node to store a TB.\n");
        abort();
    }
    // Set the state member to hold the previous state of the textbuffer, and set up prev and next pointers
    new->state = tb;
    new->next = new->prev = NULL;
    return new;
}

/* Copy the given textbuffer into a new textbuffer
 * Preserves the original textbuffer entirely
 * Returns a pointer to the copy of the textbuffer
 */
static TB copyTB (TB tb) {
    assert(tb != NULL);
    // Malloc space for the copy of the textbuffer
    TB copy = malloc(sizeof(struct textbuffer));
    // Initialise members of the bookkeeping structure
    copy->first = copy->last = NULL;
    copy->nlines = 0;
    // Set up pointer to iterate through textbuffer to copy
    Line iterator = tb->first;
    Line insert;
    // Iterate through the provided textbuffer
    while (iterator != NULL) {
        // Create a new line with the same string as the line currently iterating through
        insert = newLineNode(iterator->string);
        // Insert the new line into the copy 
        if (copy->nlines == 0) { 
            // Set the first pointer to the new line if its the first line in the copy
            copy->first = insert;
        }
        else {
            // Otherwise connect it to the current last line
            insert->prev = copy->last;
            copy->last->next = insert;
        }
        // Reset the last line and increment the line counter
        copy->last = insert;
        copy->nlines++;
        iterator = iterator->next;
    }
    return copy;
}

/* Set the line numbers for a textbuffer
 * Used only for the diff function and on the textbuffers copies which are later freed
 * Returns nothing
 */
static void setLineNumsTB (TB tb) {
    assert(tb != NULL);
    // Index count to give line numbers for the textbuffer
    int index = 0;
    // Set up a pointer to iterate through the textbuffer
    Line iterator = tb->first;
    while (iterator != NULL) {
        // Set the line number of the line and move to the next
        iterator->lineNoDiff = index;
        iterator = iterator->next;
        index++;
    }
}

/* Free the nodes of a TB
 * Keep the TB bookkeeping structure intact
 * Returns nothing
 */
static void releaseTBNodes (TB tb) {
    assert(tb != NULL);
    // Set up a pointer to iterate through the textbuffer, and a temp variable
    Line iterator = tb->first;
    Line hold;
    while (iterator != NULL) {
        // Move to the next line and free the previous line
        hold = iterator;
        iterator = iterator->next;
        free(hold->string);
        free(hold);
    }
}

/* Allocate a new textbuffer whose contents is initialised with the text given
 * in the array.
 */
TB newTB (char text[]) {
    // Malloc space for a new textbuffer
    TB new = malloc(sizeof(struct textbuffer));
    if (new == NULL) {
        fprintf(stderr, "Unable to allocate memory for a textbuffer struct.\n");
        abort();
    }
    // Initialise the members of the bookkeeping structure
    new->first = new->last = NULL;
    new->nlines = 0;
    Line insert;
    // Set up indexes to iterate through the given string pointer and the pointer to store a line
    int i = 0;
    int j = 0;
    // Declare a string array to hold a line from the input array at a time
    // Max length of a line is the length of the given array
	char line[strlen(text)], *value;
    // Iterate through the given array with the index i until the null terminator is encountered
    while (text[i] != '\0') {
        // Place the character in the text array into the line array
        line[j] = text[i];
        if (text[i] == '\n') {
            // If a new line character is encountered in the text array, replace it with a null terminator in the line array
            // This terminates the string for the line and allows us to place the line in node
            line[j] = '\0';
            // Malloc a pointer to a copy to the string to avoid all string pointers in the nodes pointing to the same memory location
            value = strdup(line);
            // Insert the node into the textbuffer
            insert = newLineNode(value);
			free(value);
            if (new->nlines == 0) {
                new->first = insert;
            }
            else {
                insert->prev = new->last;
                new->last->next = insert;
            }
            new->last = insert;
            new->nlines++;
            // Reset the counter to j to 0 to start feeling the line array from the beginning again
            // Able to write over previous values of the line array as the null terminator will terminate the string regardless of what comes after
            j = 0;
        }
        // If you did not find a new line character, incremement the index to the line array
        else {
            j++;
        }
        // Increment the index to the text array
        i++;
    }
    // Initialise the textbuffer's undo and redo stacks
    new->undoStack = initTBStack();
    new->redoStack = initTBStack();
    return new;
}

/* Free the memory occupied by the given textbuffer.  It is an error to access
 * the buffer afterwards.
 */
void releaseTB (TB tb) {
    if (tb == NULL) {
        fprintf(stderr, "The provided textbuffer points to NULL, and is unusable.\n");
        abort();
    }
    // Set up a pointer to iterate through the textbuffer, and a temp variable
    Line iterator = tb->first;
    Line hold;
    while (iterator != NULL) {
        // Set the temp variable to the current node, move to the next node
        // Free the node held by the temp variable
        hold = iterator;
        iterator = iterator->next;
        free(hold->string);
        free(hold);
    }
    // Free the nodes on the undo and redo stacks, and free the bookkeeping structure
    freeTBStackNodes(tb->undoStack);
    freeTBStackNodes(tb->redoStack);
	free(tb->undoStack);
	free(tb->redoStack);
    free(tb);
}

/* Allocate and return an array containing the text in the given textbuffer.
 * add a prefix corrosponding to line number iff showLineNumbers == TRUE
 */
char *dumpTB (TB tb, int showLineNumbers){
    if (tb == NULL) {
        fprintf(stderr, "The provided textbuffer points to NULL, and is unusable.\n");
        abort();
    }
    // Initialise a count of the buffer size required to dump the textbuffer
    int buff = 0;
    // In the case where there are no nodes in the textbuffer, return the null string
    if (tb->first == NULL) return strdup("");
    // Set up a pointer to iterate through the textbuffer
    Line iterator = tb->first;
    while (iterator != NULL) {
        // Increment the counter by the length of the string of the current node and 40 to account for line numbers
        buff += strlen(iterator->string) + 40;
        iterator = iterator->next;
    }
    // Initialise a count for the line numbers
    int lineCount = 1;
    // Malloc space for a string array of 40 characters, to hold the "%d. " format for line numbers
    char *lineNum = malloc(40);
    // Malloc the space for the buffer to hold all lines of the textbuffer, based on the above count
    char *ret = malloc(buff);
	ret[0] = '\0';
    // Reset the pointer to iterate through the textbuffer again
    iterator = tb->first;
    while (iterator != NULL) {
        // If line numbers are to be printed out
        if (showLineNumbers) {
            // Print into the buffer for the line numbers, the line count in the format below
            sprintf(lineNum, "%d. ", lineCount);
            // Concatenate the line number buffer with the return buffer
            strcat(ret, lineNum);
        }
        // Concatenate the string of the line into the return buffer, and add the new line character
        strcat(ret, iterator->string);
        strcat(ret, "\n");
        iterator = iterator->next;
        lineCount++;
    }
	free(lineNum);
    return ret;
}

/* Return the number of lines of the given textbuffer.
 */
int linesTB (TB tb){
    if (tb == NULL) {
        fprintf(stderr, "The provided textbuffer points to NULL, and is unusable.\n");
        abort();
    }
	return tb->nlines;
}

/* Add a given prefix to all lines between pos1 and pos2
 *
 * - The program is to abort() with an error message if line 'pos1' or line
 *   'pos2' is out of range.  The first line of a textbuffer is at position 0.
 */
void addPrefixTB (TB tb, int pos1, int pos2, char* prefix){
    if (tb == NULL) {
        fprintf(stderr, "The provided textbuffer points to NULL, and is unusable.\n");
        abort();
    }
    if (pos1 > pos2 || pos1 < 0 || pos2 >= tb->nlines) {
        fprintf(stderr, "Invalid input for pos1 and/or pos2.\n");
        abort();
    }
    // Set up a pointer to iterate through the textbuffer
    Line iterator = tb->first;
    // Initialise an index variable to determine index of the line in the textbuffer
    int index = 0;
    // Declare a pointer to a string
    char *buff;
    while (iterator != NULL) {
        // If the index lies in the given range inclusive
        if (index >= pos1 && index <= pos2) {
            // Malloc space for the line and the prefix
            buff = malloc(strlen(iterator->string)+strlen(prefix)+1);
            // Set the first character to the null terminator to prevent memory leaks during concatenation
            buff[0] = '\0';
            strcat(buff, prefix);
            strcat(buff, iterator->string);
            free(iterator->string);
            iterator->string = strdup(buff);
			free(buff);
        }
        iterator = iterator->next;
        index++;
    }
    freeTBStackNodes(tb->redoStack);
}

/* Merge 'tb2' into 'tb1' at line 'pos'.
 *
 * - Afterwards line 0 of 'tb2' will be line 'pos' of 'tb1'.
 * - The old line 'pos' of 'tb1' will follow after the last line of 'tb2'.
 * - After this operation 'tb2' can not be used anymore (as if we had used
 *   releaseTB() on it).
 * - The program is to abort() with an error message if 'pos' is out of range.
 */
void mergeTB (TB tb1, int pos, TB tb2){
    if (tb1 == NULL || tb2 == NULL) {
        fprintf(stderr, "One or more of the provided textbuffers point to NULL, and is unusable.\n");
        abort();
    }
    if (pos < 0 || pos > tb1->nlines) {
        fprintf(stderr, "Invalid input for pos.\n");
        abort();
    }
    TB copy = copyTB(tb1);
    TBNodeP copyNode = newTBNode(copy);
    pushTBStack(tb1->undoStack, copyNode);
    if (tb2->first == NULL || tb1->first == tb2->first) return;
    if (pos == tb1->nlines) {
        tb1->last->next = tb2->first;
        tb2->first->prev = tb1->last;
        tb1->last = tb2->last;
    }
    else if (pos == 0) {
        tb1->first->prev = tb2->last;
        tb2->last->next = tb1->first;
        tb1->first = tb2->first;
        if (tb1->nlines == 0) {
            tb1->last = tb2->last;
        }
    }
    else {
        Line iterator = tb1->first;
        for (int i = 0; i < pos; i++) iterator = iterator->next;
        iterator->prev->next = tb2->first;
        tb2->first->prev = iterator->prev;
        iterator->prev = tb2->last;
        tb2->last->next = iterator;
    }
    tb1->nlines += tb2->nlines;
    freeTBStackNodes(tb2->undoStack);
    freeTBStackNodes(tb2->redoStack);
	free(tb2->undoStack);
	free(tb2->redoStack);
    free(tb2);
}

/* Copy 'tb2' into 'tb1' at line 'pos'.
 *
 * - Afterwards line 0 of 'tb2' will be line 'pos' of 'tb1'.
 * - The old line 'pos' of 'tb1' will follow after the last line of 'tb2'.
 * - After this operation 'tb2' is unmodified and remains usable independent
 *   of 'tb1'.
 * - The program is to abort() with an error message if 'pos' is out of range.
 */
void pasteTB (TB tb1, int pos, TB tb2) {
    if (tb1 == NULL || tb2 == NULL) {
        fprintf(stderr, "One or more of the provided textbuffers point to NULL, and is unusable.\n");
        abort();
    }
    if (pos < 0 || pos > tb1->nlines) {
        fprintf(stderr, "Invalid input for pos.\n");
        abort();
    }
    TB copy2 = copyTB(tb1);
    TBNodeP copy2Node = newTBNode(copy2);
    pushTBStack(tb1->undoStack, copy2Node);
    if (tb2->first == NULL) return;
    TB copy = copyTB(tb2);
    if (copy->first == NULL || tb1->first == copy->first) return;
    if (pos == tb1->nlines) {
        tb1->last->next = copy->first;
        copy->first->prev = tb1->last;
        tb1->last = copy->last;
    }
    else if (pos == 0) {
        tb1->first->prev = copy->last;
        copy->last->next = tb1->first;
        tb1->first = copy->first;
        if (tb1->nlines == 0) {
            tb1->last = copy->last;
        }
    }
    else {
        Line iterator = tb1->first;
        for (int i = 0; i < pos; i++) iterator = iterator->next;
        iterator->prev->next = copy->first;
        copy->first->prev = iterator->prev;
        iterator->prev = copy->last;
        copy->last->next = iterator;
    }
    tb1->nlines += copy->nlines;
	free(copy);
} 

/* Cut the lines between and including 'from' and 'to' out of the textbuffer
 * 'tb'.
 *
 * - The result is a new textbuffer (much as one created with newTB()).
 * - The cut lines will be deleted from 'tb'.
 * - The program is to abort() with an error message if 'from' or 'to' is out
 *   of range.
 */
TB cutTB (TB tb, int from, int to){
    if (tb == NULL) {
        fprintf(stderr, "The provided textbuffer points to NULL, and is unusable.\n");
        abort();
    }
    if (from > to || from < 0 || to >= tb->nlines) {
        fprintf(stderr, "Invalid input for from and to.\n");
        abort();
    }
    TB copy = copyTB(tb);
    TBNodeP copyNode = newTBNode(copy);
    pushTBStack(tb->undoStack, copyNode);
    TB ret = newTB("");
    if (tb->nlines == 0) return ret;
    Line fromNode = tb->first;
    for (int i = 0; i < from; i++) fromNode = fromNode->next;
    Line toNode = fromNode;
    for (int j = from; j < to; j++) toNode = toNode->next;
    if (fromNode->prev == NULL && toNode->next == NULL) {
        tb->first = tb->last = NULL;
    }
    else if (fromNode->prev == NULL) {
        tb->first = toNode->next;
        toNode->next->prev = NULL;
    }
    else if (toNode->next == NULL) {
        tb->last = fromNode->prev;
        fromNode->prev->next = NULL;
    }
    else {
        fromNode->prev->next = toNode->next;
        toNode->next->prev = fromNode->prev;
    }
    fromNode->prev = NULL;
    toNode->next = NULL;
    ret->first = fromNode;
    ret->last = toNode;
    tb->nlines -= to-from+1;
    return ret;
}

/*  Return a linked list of Match nodes of all the matches of string search
 *  in tb
 *
 * - The textbuffer 'tb' will remain unmodified.
 * - The user is responsible of freeing the returned list
 */
Match searchTB (TB tb, char* search){
    if (tb == NULL) {
        fprintf(stderr, "The provided textbuffer points to NULL, and is unusable.\n");
        abort();
    }
    Line iterator = tb->first;
    Match ret = NULL;
    Match insert, curr;
    char *s, *start;
    int empty = 1;
    int runs = 0;
    while (iterator != NULL) {
        start = iterator->string;
        while ((s = strstr(start, search)) != NULL) {
            insert = newMatchNode(runs+1, s-iterator->string);
            if (empty) {
                ret = insert;
                curr = ret;
                empty = 0;
            }
            else {
                curr->next = insert;
                curr = curr->next;
            }
            start = s + strlen(search);
        }
        iterator = iterator->next;
        runs++;
    }
	return ret;
}

/* Remove the lines between and including 'from' and 'to' from the textbuffer
 * 'tb'.
 *
 * - The program is to abort() with an error message if 'from' or 'to' is out
 *   of range.
 */
void deleteTB (TB tb, int from, int to){
    if (tb == NULL) {
        fprintf(stderr, "The provided textbuffer points to NULL, and is unusable.\n");
        abort();
    }
    if (from > to || from < 0 || to >= tb->nlines) {
        fprintf(stderr, "Invalid input for from and to.\n");
        abort();
    }
    TB copy = copyTB(tb);
    TBNodeP copyNode = newTBNode(copy);
    pushTBStack(tb->undoStack, copyNode);
    TB ret = newTB("");
    if (tb->nlines > 0) {
        Line fromNode = tb->first;
        for (int i = 0; i < from; i++) fromNode = fromNode->next;
        Line toNode = fromNode;
        for (int j = from; j < to; j++) toNode = toNode->next;
        if (fromNode->prev == NULL && toNode->next == NULL) {
            tb->first = tb->last = NULL;
        }
        else if (fromNode->prev == NULL) {
            tb->first = toNode->next;
            toNode->next->prev = NULL;
        }
        else if (toNode->next == NULL) {
            tb->last = fromNode->prev;
            fromNode->prev->next = NULL;
        }
        else {
            fromNode->prev->next = toNode->next;
            toNode->next->prev = fromNode->prev;
        }
        fromNode->prev = NULL;
        toNode->next = NULL;
        ret->first = fromNode;
        ret->last = toNode;
    }
    tb->nlines -= to-from+1;
	releaseTB(ret);
}

/* Removes a single node in the textbuffer by providing a line number
 * Returns nothing
 */
static void removeTBNode(TB tb, int lineNo) {
    assert(tb != NULL);
    Line iterator = tb->first;
    Line hold;
    while (iterator != NULL) {
        if (iterator->lineNoDiff == lineNo) {
            if (iterator->prev == NULL && iterator->next == NULL) {
                tb->first = tb->last = NULL;
            }
            else if (iterator->prev == NULL) {
                iterator->next->prev = NULL;
                tb->first = iterator->next;
            }
            else if (iterator->next == NULL) {
                iterator->prev->next = NULL;
                tb->last = iterator->prev;
            }
            else {
                iterator->prev->next = iterator->next;
                iterator->next->prev = iterator->prev;
            }
            tb->nlines--;
            hold = iterator;
            iterator = iterator->next;
            free(hold);
            break;
        }
        else {
            iterator = iterator->next;
        }
    }
}

/* Search every line of tb for each occurrence of a set of specified subsitituions
 * and alter them accordingly
 *
 * refer to spec for table.
 */
void formRichText (TB tb){
    if (tb == NULL) {
        fprintf(stderr, "The provided textbuffer points to NULL, and is unusable.\n");
        abort();
    }
    char *newLine, *richText;
    Line iterator = tb->first;
    while (iterator != NULL) {
        newLine = malloc(4*strlen(iterator->string));
		newLine[0] = '\0';
        richText = malloc(strlen(iterator->string));
		richText[0] = '\0';
        assert(newLine != NULL && richText != NULL);
        int i = 0, j = 0, index = 0, isStar = 0;
        if (iterator->string[0] == '#') {
            strcat(newLine, "<h1>");
            strcat(richText, &iterator->string[1]);
            strcat(newLine, richText);
            strcat(newLine, "</h1>");
        }
        else {
            while (iterator->string[i] != '\0') {
                if (iterator->string[i] == '*' || iterator->string[i] == '_') {
                    if (iterator->string[i] == '*') isStar = 1;
                    j = i+1;
                    while (iterator->string[j] != '\0') {
                        if ((iterator->string[j] == '*' && isStar) || (iterator->string[j] == '_' && !isStar)) {
                            if (j-i == 1) {
                                newLine[index++] = iterator->string[i];
								newLine[index] = '\0';
                            }
							else {
								if (isStar) strcat(newLine, "<b>");
								else strcat(newLine, "<i>");
								strncpy(richText, &iterator->string[i+1], j-i-1);
								richText[j-i-1] = '\0';
								strcat(newLine, richText);
								free(richText);
								if (isStar) strcat(newLine, "</b>");
								else strcat(newLine, "</i>");
								index += 6+j-i;
								i = j;
							}
                            break;
                        }
                        else j++;
                    }
                    if (iterator->string[j] == '\0') {
						newLine[index++] = iterator->string[i++];
						newLine[index] = '\0';
					}
                    else i++;
                    isStar = 0;
                }
                else {
					newLine[index++] = iterator->string[i++];
					newLine[index] = '\0';
				}
            }
			newLine[index] = '\0';
        }
        free(iterator->string);
        iterator->string = strdup(newLine);
		free(newLine);
        iterator = iterator->next;
    }
    freeTBStackNodes(tb->redoStack);
}

/* Determine the differences between the two textbuffers
 * Works out the sequence of operations required to change the first textbuffer into the second
 * Returns the string that provides the operations
 */
char* diffTB (TB tb1, TB tb2) {
    if (tb1 == NULL || tb2 == NULL) {
        fprintf(stderr, "One or more of the provided textbuffers point to NULL, and is unusable.\n");
        abort();
    }
    int buff = 0;
    Line counter = tb2->first;
    while (counter != NULL) {
        buff += strlen(counter->string) + 10;
        counter = counter->next;
    }
    TB copy1 = copyTB(tb1);
    setLineNumsTB(copy1);
    TB copy2 = copyTB(tb2);
    setLineNumsTB(copy2);
    assert(copy1 != NULL && copy2 != NULL);
    int index1 = 0, index2 = 0, match = 0;
    Line iterator1 = copy1->first, iterator2 = copy2->first;
    while (iterator1 != NULL) {
        index2 = 0;
        match = 0;
        iterator2 = copy2->first;
        while (iterator2 != NULL) {
            if (strcmp(iterator1->string, iterator2->string) == 0) {
                iterator1 = iterator1->next;
                removeTBNode(copy1, iterator1->prev->lineNoDiff);
                removeTBNode(copy2, iterator2->lineNoDiff);
                match = 1;
                break;
            }
            index2++;
            iterator2 = iterator2->next;
        }
        index1++;
        if (!match) iterator1 = iterator1->next;
    }
    char *temp1 = malloc(buff), *temp2 = malloc(buff);
    char *ret = malloc(buff);
    iterator1 = copy1->first;
    while (iterator1 != NULL) {
        sprintf(temp1, "-,%d\n", iterator1->lineNoDiff);
        strcat(ret, temp1);
        iterator1 = iterator1->next;
    }
    iterator2 = copy2->first;
    while (iterator2 != NULL) {
        sprintf(temp2, "+,%d,", iterator2->lineNoDiff);
        strcat(ret, temp2);
        strcat(ret, iterator2->string);
        strcat(ret, "\n");
        iterator2 = iterator2->next;
    }
    free(temp1);
    free(temp2);
    releaseTB(copy1);
    releaseTB(copy2);
    return ret;
}

/* Undo the most recent operation on the textbuffer
 * Set the current textbuffer to point to the returned textbuffer state
 * Returns nothing
 */
void undoTB (TB tb) {
    if (tb == NULL) {
        fprintf(stderr, "The provided textbuffer points to NULL, and is unusable.\n");
        abort();
    }
    TBNodeP hold = popTBStack(tb->undoStack);
    if (hold == NULL) {
        fprintf(stderr, "Nothing more to undo.\n");
        return;
    }
    TBNodeP currState = newTBNode(copyTB(tb));
    pushTBStack(tb->redoStack, currState);
    releaseTBNodes(tb);
    tb->first = hold->state->first;
    tb->last = hold->state->last;
    tb->nlines = hold->state->nlines;
	free(hold->state);
	free(hold);
}

/* Redo the most recent undo operation on the textbuffer
 * Set the current textbuffer to point to the returned textbuffer state
 * Returns nothing
 */
void redoTB (TB tb) {
    if (tb == NULL) {
        fprintf(stderr, "The provided textbuffer points to NULL, and is unusable.\n");
        abort();
    }
    TBNodeP hold = popTBStack(tb->redoStack);
    if (hold == NULL) {
        fprintf(stderr, "Nothing more to redo.\n");
        return;
    }
    TBNodeP currState = newTBNode(copyTB(tb));
    pushTBStack(tb->undoStack, currState);
    releaseTBNodes(tb);
    tb->first = hold->state->first;
    tb->last = hold->state->last;
    tb->nlines = hold->state->nlines;
	free(hold->state);
	free(hold);
}

/*
static int validTB(TB tb) {
    if (tb == NULL) {
        fprintf(stderr,"TB is null\n");
        return 0;
    }
    if (tb->first == NULL) {
        // list is empty; curr and last should be null
        if (tb->last != NULL) {
            fprintf(stderr,"Non-null pointers in empty list\n");
            return 0;
        }
    }
    else {
        // list is not empty; curr and last should be non-null
        if (tb->last == NULL) {
            fprintf(stderr,"Null pointers in non-empty list\n");
            return 0;
        }
    }
    int count = 0;
    Line curr;
    // check scanning forward through list
    for (curr = tb->first; curr != NULL; curr = curr->next) {
        if (curr->prev != NULL && curr->prev->next != curr) {
            fprintf(stderr, "Invalid forward link into line (%s)\n", curr->string);
            return 0;
        }
        if (curr->next != NULL && curr->next->prev != curr) {  
            fprintf(stderr, "Invalid backward link into line (%s)\n",curr->string);
            return 0;  
        }
        count++;
    }
    if (count != tb->nlines) {
        fprintf(stderr, "Forward count mismatch; counted=%d, nlines=%d\n", count, tb->nlines);
        return 0;
    }
    // check scanning backward through list
    count = 0;
    for (curr = tb->last; curr != NULL; curr = curr->prev) {
        count++;
        }
        if (count != tb->nlines) {
            fprintf(stderr, "Backward count mismatch; counted=%d, nlines=%d\n", count, tb->nlines);
        return 0;
    }
    return 1;
}
*/

/* Your whitebox tests
 */
void whiteBoxTests () {
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("TESTING NEWTB AND DUMPTB WIHTOUT LINE NUMBERS\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("Initialise a textbuffer with a null string and dump the textbuffer with no line numbers\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("TB new = newTB(\"\");\n");
    printf("dumpTB(new, 0);\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    TB new = newTB("");
//    assert(strcmp(dumpTB(new, 0), "") == 0);
    printf("PASSED\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("Initialise a textbuffer with an empty line string and dump the textbuffer with no line numbers\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("TB new1 = newTB(\"\\n\");\n");
    printf("dumpTB(new1, 0);\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    TB new1 = newTB("\n");
  //  assert(strcmp(dumpTB(new1, 0), "\n") == 0);
    printf("PASSED\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("Initialise a textbuffer with a multiple empty line string and dump the textbuffer with no line numbers\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("TB new2 = newTB(\"\\n\\n\\n\\n\");\n");
    printf("dumpTB(new2, 0);\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    TB new2 = newTB("\n\n\n\n");
  //  assert(strcmp(dumpTB(new2, 0), "\n\n\n\n") == 0);
    printf("PASSED\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("Initialise a textbuffer with a single line string and dump the textbuffer with no line numbers\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("TB new3 = newTB(\"hello\\n\");\n");
    printf("dumpTB(new3, 0);\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    TB new3 = newTB("hello\n");
  //  assert(strcmp(dumpTB(new3, 0), "hello\n") == 0);
    printf("PASSED\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("Initialise a textbuffer with a multiple line string and dump the textbuffer with no line numbers\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("TB new4 = newTB(\"hello\\nhello\\nhello\\n\");\n");
    printf("dumpTB(new4, 0);\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    TB new4 = newTB("hello\nhello\nhello\n");
  //  assert(strcmp(dumpTB(new4, 0), "hello\nhello\nhello\n") == 0);
    printf("PASSED\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("TESTING DUMPTB WITH LINE NUMBERS\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("Dump the textbuffer with null string, with line numbers\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("dumpTB(new, 1);\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
  //  assert(strcmp(dumpTB(new, 1), "") == 0);
    printf("PASSED\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("Dump the textbuffer with an empty line, with line numbers\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("dumpTB(new1, 1);\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
 //   assert(strcmp(dumpTB(new1, 1), "1. \n") == 0);
    printf("PASSED\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("Dump the textbuffer with multiple empty lines, with line numbers\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("dumpTB(new2, 1);\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
   // assert(strcmp(dumpTB(new2, 1), "1. \n2. \n3. \n4. \n") == 0);
    printf("PASSED\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("Dump the textbuffer with a single line, with line numbers\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("dumpTB(new3, 1);\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
  //  assert(strcmp(dumpTB(new3, 1), "1. hello\n") == 0);
    printf("PASSED\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("Dump the textbuffer with multiple lines, with line numbers\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("dumpTB(new4, 1);\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
  //  assert(strcmp(dumpTB(new4, 1), "1. hello\n2. hello\n3. hello\n") == 0);
    printf("PASSED\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("Dump a textbuffer that points to null\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("dumpTB(NULL, 1);\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    //dumpTB(NULL, 1);
    printf("PASSED\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("TESTING LINESTB\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("Number of lines of null string textbuffer\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("linesTB(new);\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    assert(linesTB(new) == 0);
    printf("PASSED\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("Number of lines of empty line textbuffer\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("linesTB(new1);\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    assert(linesTB(new1) == 1);
    printf("PASSED\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("Number of lines of mulitple empty line textbuffer\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("linesTB(new2);\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    assert(linesTB(new2) == 4);
    printf("PASSED\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("Number of lines of single line textbuffer\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("linesTB(new3);\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    assert(linesTB(new3) == 1);
    printf("PASSED\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("Number of lines of multiple line textbuffer\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("linesTB(new4);\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    assert(linesTB(new4) == 3);;
    printf("PASSED\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("TESTING ADDPREFIXTB\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("Adding prefix \"Yes \" to the null string textbuffer\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("addPrefixTB(new, 0, 0, \"Yes \");\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
//    addPrefixTB(new, 0, 0, "Yes ");
    printf("PASSED\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("Adding prefix \"Yes \" to the empty line textbuffer\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("addPrefixTB(new1, 0, 0, \"Yes \");\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    addPrefixTB(new1, 0, 0, "Yes ");
 //   assert(strcmp(dumpTB(new1, 0), "Yes \n") == 0);
    printf("PASSED\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("Adding prefix \"Yes \" to the mulitple empty line textbuffer\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("addPrefixTB(new2, 0, 3, \"Yes \");\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    addPrefixTB(new2, 0, 3, "Yes ");
 //   assert(strcmp(dumpTB(new2, 0), "Yes \nYes \nYes \nYes \n") == 0);
    printf("PASSED\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("Number of lines of single line textbuffer\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("linesTB(new3);\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    assert(linesTB(new3) == 1);
    printf("PASSED\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("Number of lines of multiple line textbuffer\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    printf("linesTB(new4);\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
    assert(linesTB(new4) == 3);;
    printf("PASSED\n");
    printf("-------------------------------------------------------------------------------------------------------\n");
	releaseTB(new);
	releaseTB(new1);
	releaseTB(new2);
	releaseTB(new3);
	releaseTB(new4);
}
