 #if DBUG
     printf("Inside");
 #endif
     Addr headA = (Addr)((char *)block - sizeof(Header));
     Header *check = (Header *)headA;
     if(check->status != ALLOC){
         fprintf(stderr, "Attempted to free unallocated chunk\n");
         exit(1);
     }   
     check->status = FREE;
     headA = memset(headA, 0, check->size);
     Addr curr = (Addr)((char *)headA + check->size);
     Addr hold = headA;
     Header *chunk;
     Addr endHeap = (Addr)((char *)heapMem + heapSize);
 #if DBUG
     printf("Just before loop in myFree");
 #endif
 
     while (curr < endHeap) {
         chunk = (Header *)curr;
         if(chunk->status == FREE){
             hold = curr;
             break;
         }   
         curr = (Addr)((char *)curr + chunk->size);
     }   
 #if DBUG
     printf("Finished loop");
 #endif
             
     int insertP = -1; 
     for(int i = 0; i < freeElems; i++){
         if(freeList[i] > hold){
             insertP = i;
             break;
         }   
     }   
     if(insertP == -1){
         int zeroP = 0;
         for(int k = 0; k < freeElems; k++){
             if(freeList[k] == 0){ 
                 zeroP = k;
                 break;
             }   
         }   
         freeList[zeroP] = hold;
     }
     else{
        for(int j = freeElems-2; j >= insertP; j--){
                     freeList[j+1] = freeList[j];
                 }
                 freeList[insertP] = hold;
             }
         
         }
















freeList[zeroP] = hold;
         Header *leftChunk = (Header *)(freeList[zeroP-1]);
         if(freeList[zeroP] - leftChunk->size == freeList[zeroP-1]){
             leftChunk->size = leftChunk->size + check->size;
             memset(headA, 0, sizeof(Header));
             freeList[zeroP] = 0;
         }










if(insertP >= 1 && insertP <= freeElems-2){
             Header *leftCChunk = (Header *)(freeList[insertP-1]);
             Header *rightCChunk = (Header *)(freeList[insertP+1]);
             if(freeList[insertP] + rightCChunk->size == freeList[insertP+1]){
                 check->size += rightCChunk->size;
                 memset(freeList[insertP+1], 0, sizeof(Header));
                 freeList[insertP+1] = 0;
                 for(int f = insertP+1; f < freeElems-1; f++){
                     freeList[f] = freeList[f+1];
                 }
                 freeList[freeElems-1] = 0;
             }
             if(freeList[insertP-1] + leftCChunk->size == freeList[insertP]){
                 leftCChunk->size += check->size;
                 memset(freeList[insertP], 0, sizeof(Header));
                 freeList[insertP] = 0;
                 for(int f = insertP; f < freeElems-1; f++){
                     freeList[f] = freeList[f+1];
                 }
                 freeList[freeElems-1] = 0;
             }

         }









heapMem = memset(heapMem, 0, heapSize);
     Header *chunk = (Header *)(heapMem);
     chunk->status = FREE;
     chunk->size = heapSize;
     nFree = 1;
     freeElems = size/MIN_CHUNK;
     freeList = malloc(freeElems*sizeof(Addr));
     if(freeList == NULL){
         return -1;
     }
     freeList = memset(freeList, 0, freeElems*sizeof(Addr));
     freeList[0] = heapMem;
