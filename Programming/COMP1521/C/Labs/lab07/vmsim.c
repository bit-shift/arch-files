// COMP1521 18s1 Week 07 Lab
// Virtual Memory Simulation

#include <stdlib.h>
#include <stdio.h>

typedef unsigned int uint;

// Page Table Entries

#define NotLoaded 0
#define Loaded    1
#define Modified  2

#define PAGESIZE  4096
#define PAGEBITS  12

#define actionName(A) (((A) == 'R') ? "read from" : "write to")

typedef struct {
   int status;        // Loaded or Modified or NotLoaded
   int frameNo;       // -1 if page not loaded
   int lastAccessed;  // -1 if never accessed
} PTE;

// Globals

uint nPages;         // how many process pages
uint nFrames;        // how many memory frames

PTE *PageTable;      // process page table
int *MemFrames;      // memory (each frame holds page #, or -1 if empty)

uint nLoads = 0;     // how many page loads
uint nSaves = 0;     // how many page writes (after modification)
uint nReplaces = 0;  // how many Page replacements

uint clock = 0;      // clock ticks

// Functions

void initPageTable();
void initMemFrames();
void showState();
int  physicalAddress(uint vAddr, char action);

// main:
// read memory references
// maintain VM data structures
// argv[1] = nPages, argv[2] = nFrames
// stdin contains lines of form
//   lw  $t0, Address
//   sw  $t0, Address
// Address is mapped to a page reference
// as per examples in lectures
// Note: pAddr is signed, because -ve used for errors

int main (int argc, char **argv)
{
   char line[100]; // line buffer
   char action;    // read or write
   uint vAddr;     // virtual address (unsigned)
   int  pAddr;     // physical address (signed)

   if (argc < 3) {
      fprintf(stderr, "Usage: %s #pages #frames < refFile\n", argv[0]);
      exit(1);
   }

   nPages = atoi(argv[1]);
   nFrames = atoi(argv[2]);
   // Value 2 also picks up invalid argv[x]
   if (nPages < 1 || nFrames < 1) {
      fprintf(stderr, "Invalid page or frame count\n");
      exit(1);
   }

   initPageTable(); initMemFrames();

   // read from standard input
   while (fgets(line,100,stdin) != NULL) {
      // get next line; check valid (barely)
      if ((sscanf(line, "%c %d\n", &action, &vAddr) != 2)
                     || !(action == 'R' || action == 'W')) {
         printf("Ignoring invalid instruction %s\n", line);
         continue;
      }
      // do address mapping
      pAddr = physicalAddress(vAddr, action);
      if (pAddr < 0) {
         printf("\nInvalid address %d\n", vAddr);
         exit(1);
      }
      // debugging ...
      printf("\n@ t=%d, %s pA=%d (vA=%d)\n",
             clock, actionName(action), pAddr, vAddr);
      // tick clock and show state
      showState();
      clock++;
   }
   printf("\n#loads = %d, #saves = %d, #replacements = %d\n", nLoads, nSaves, nReplaces);
   return 0;
}

// map virtual address to physical address
// handles regular references, page faults and invalid addresses

int physicalAddress(uint vAddr, char action){
   int pAddr; // Initialise a signed integer variable to hold the physical address
   int pageNum = (int) vAddr/PAGESIZE; // Page Number of the virtual address
   int offset = vAddr - pageNum*PAGESIZE; // Offset into the page of the virtual address

   // If the Page Number is greater than the number of pages, it is an invalid address
   if(pageNum >= nPages){
       return -1;
   }

   // If the Page is already Loaded, update its status if it's a write action
   if(PageTable[pageNum].status >= Loaded){
       if(action == 'W'){
           PageTable[pageNum].status = Modified;
       }
   }

   // If the Page is not already loaded, find a Frame to load the Page into
   else{
       int unFrameNo = -1; // Unused Frame Number

       // Search for an unused Frame in Memory
       for(int i = 0; i < nFrames; i++){

           // If you find an unused Frame, set the Unused Frame Number to that Frame Number and break the loop
           if(MemFrames[i] == -1){
               unFrameNo = i;
               break;
           }
       }

       // If Unused Frame Number hasn't changed, we need to remove a currently loaded Frame
       if(unFrameNo == -1){
           nReplaces++; // Increment the replacement counter
           int lruPage = MemFrames[0]; // Set the LRU Page Number as the Page Number of the Page in the first Frame
           int lru = PageTable[MemFrames[0]].lastAccessed; // Set the LRU Time as the Last Accessed Time of the Page in the first Frame

           // Search for the LRU Page in the Frames in Memory. Compare the Last Time Accessed
           for(int i = 0; i < nFrames; i++){
               if(PageTable[MemFrames[i]].lastAccessed < lru){
                   lru = PageTable[MemFrames[i]].lastAccessed;
                   lruPage = MemFrames[i]; // Page Number of the LRU Page
               }
           }
           unFrameNo = PageTable[lruPage].frameNo; // Set the Unused Frame Number to the Frame Number of the LRU Page

           // If the LRU Page has been Modified, it will need to be saved to disk, so increment the save counter
           if(PageTable[lruPage].status == Modified){
               nSaves++;
           }

           // Reset the PageTable entry for the LRU Page
           PageTable[lruPage].status = NotLoaded;
           PageTable[lruPage].lastAccessed = -1;
           PageTable[lruPage].frameNo = -1;
       }

       nLoads++; // Increment the loads counter
       PageTable[pageNum].frameNo = unFrameNo; // Set the Page's Frame Number to the Unused Frame Number

       // If the action is a write, update the Page's Status to be Modified, else Loaded
       if(action == 'W'){
           PageTable[pageNum].status = Modified;
       }
       else{
           PageTable[pageNum].status = Loaded;
       }
       MemFrames[unFrameNo] = pageNum; // Store the Page in the Unused Frame
   }
   PageTable[pageNum].lastAccessed = clock; // Set the Last Time Accessed of the Page to the clock time
   pAddr = PageTable[pageNum].frameNo*PAGESIZE + offset; // Compute the physical address
   return pAddr;
}

// allocate and initialise Page Table

void initPageTable()
{
   PageTable = malloc(nPages * sizeof(PTE));
   if (PageTable == NULL) {
      fprintf(stderr, "Insufficient memory for Page Table\n");
      exit(1);
   }
   for (int i = 0; i < nPages; i++) {
      PageTable[i].status = NotLoaded;
      PageTable[i].frameNo = -1;
      PageTable[i].lastAccessed = -1;
   }
}

// allocate and initialise Memory Frames

void initMemFrames()
{
   MemFrames = malloc(nFrames * sizeof(int));
   if (MemFrames == NULL) {
      fprintf(stderr, "Insufficient memory for Memory Frames\n");
      exit(1);
   }
   for (int i = 0; i < nFrames; i++) {
      MemFrames[i] = -1;
   }
}

// dump contents of PageTable and MemFrames

void showState()
{
   printf("\nPageTable (Stat,Acc,Frame)\n");
   for (int pno = 0; pno < nPages; pno++) {
      uint s; char stat;
      s = PageTable[pno].status;
      if (s == NotLoaded)
         stat = '-';
      else if (s & Modified)
         stat = 'M';
      else
         stat = 'L';
      int f = PageTable[pno].frameNo;
      printf("[%2d] %2c, %2d, %2d",
             pno, stat, PageTable[pno].lastAccessed, PageTable[pno].frameNo);
      if (f >= 0) printf(" @ %d", f*PAGESIZE);
      printf("\n");
   }
   printf("MemFrames\n");
   for (int fno = 0; fno < nFrames; fno++) {
      printf("[%2d] %2d @ %d\n", fno, MemFrames[fno], fno*PAGESIZE);
   }
}
