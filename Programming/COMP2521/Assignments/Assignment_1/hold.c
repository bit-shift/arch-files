/*
  40 static int isEqualTB (TB tb1, TB tb2) {
  39     if (tb1 == NULL || tb2 == NULL) {
  38         fprintf(stderr, "One or more of the provided textbuffers point to NULL, and is unusable.\n");
  37         abort();
  36     }
  35     int isEqual = 0;
  34     if (tb1->nlines != tb2->nlines) return isEqual;
  33     Line iterator1 = tb1->first;
  32     Line iterator2 = tb2->first;
  31     while (iterator1 != NULL && iterator2 != NULL) {
  30         if (strcmp(iterator1->string, iterator2->string) != 0) return isEqual;
  29         iterator1 = iterator1->next;
  28         iterator2 = iterator2->next;
  27     }
  26     return isEqual = 1;
  25 }       
  24 
  23 
  22 static void enterTBQueue (TBQueueP tbqueue, QueueNode *queuenode) {
  21     assert(tbqueue != NULL && queuenode != NULL);
  20     if (tbqueue->nitems == 0) {
  19         tbqueue->head = queuenode;
  18     }
  17     else {
  16         tbqueue->tail->next = queuenode;
  15         queuenode->prev = tbqueue->tail;
  14     }
  13     tbqueue->tail = queuenode;
  12     tbqueue->nitems++;
  11 }
  10 
   9 static QueueNode *leaveTBQueue (TBQueueP tbqueue) {
   8     assert(tbqueue != NULL);
   7     QueueNode *ret = NULL;
   6     if (tbqueue->nitems != 0) {
   5         ret = tbqueue->head;
   4         tbqueue->head = tbqueue->head->next;
   3         tbqueue->nitems--;
   2     }
   1     return ret;
 160 }
   1 */
 /* Create a new queue node with the given string
  14  * Return a pointer to the queue node
  13  */
  /*12 *//*
  11 static QueueNode *newQueueNode (char *text, int lineNo) {
  10     QueueNodeP new = malloc(sizeof(struct QueueNode));
   9     if (new == NULL) {
   8         fprintf(stderr, "Could not allocate memory for a new node to store a queue's item.\n");
   7         abort();
   6     }
   5     new->lineNo = lineNo;
   4     new->string = strdup(text);
   3     new->next = new->prev = NULL;
   2     return new;
   1 }*/
  /*
   1 static TBQueue *initTBQueue (TB tb) {
   2     assert(tb != NULL);
   3     TBQueueP new = malloc(sizeof(struct TBQueue));
   4     assert(new != NULL);
   5     new->nitems = 0;
   6     new->head = new->tail = NULL;
   7     Line iterator = tb->first;
   8     QueueNodeP insert;
   9     while (iterator != NULL) {
  10         insert = newQueueNode(iterator->string, new->nitems);
  11         enterTBQueue(new, insert);
  12         iterator = iterator->next;
  13     }
  14     return new;
  15 }*/

