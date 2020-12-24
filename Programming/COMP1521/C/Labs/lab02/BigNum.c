/ BigNum.h ... LARGE positive integer values

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "BigNum.h"

// Initialise a BigNum to N bytes, all zero
void initBigNum(BigNum *n, int Nbytes){
    n->nbytes = Nbytes;
    n->bytes = malloc(Nbytes * sizeof(Byte));
    assert(n->bytes != NULL);
    int i = 0;
    while(i < Nbytes){
        n->bytes[i] = '0';
        i++;
    }
    return;
}

// Add two BigNums and store result in a third BigNum
void addBigNums(BigNum n, BigNum m, BigNum *res){
    if(res->nbytes < n.nbytes){
        res->bytes = realloc(res->bytes, n.nbytes);
	      int u = res->nbytes;
	      while(u < n.nbytes){
	         res->bytes[u] = '0';
	         u++;
	      }
	      res->nbytes = n.nbytes;
    }
    if(res->nbytes < m.nbytes){
        res->bytes = realloc(res->bytes, m.nbytes);
	      int k = res->nbytes;
	      while(k < m.nbytes){
	         res->bytes[k] = '0';
	         k++;
	      }
	      res->nbytes = m.nbytes;
    }
    char carry = '0';
    int i = 0;
    while(i < n.nbytes || i < m.nbytes){
        if(i < n.nbytes && i < m.nbytes){
            res->bytes[i] = (((n.bytes[i] + m.bytes[i] + carry) % 48) % 10) + 48;
            if((n.bytes[i] + m.bytes[i] + carry) % 48 > 9){
                carry = '1';
            }
            else{
                carry = '0';
            }
        }
        else if(i < n.nbytes && i >= m.nbytes){
            res->bytes[i] = n.bytes[i];
        }
        else{
            res->bytes[i] = m.bytes[i];
        }
        i++;
    }
    if(carry == '1'){
        res->bytes = realloc(res->bytes, 2 * res->nbytes);
        res->nbytes = 2 * res->nbytes;
	      int v = i;
	      while(v < res->nbytes){
	         res->bytes[v] = '0';
	         v++;
	      }
        res->bytes[i] = carry;
    }
    return;
}

// Set the value of a BigNum from a string of digits
// Returns 1 if it *was* a string of digits, 0 otherwise
int scanBigNum(char *s, BigNum *n){
    int checkD = 1;
    int j = 0;
    while(j < strlen(s)){
        if(isdigit(s[j])){
            checkD = 0;
        }
	      j++;
    }
    if(checkD){
        return 0;
    }
    if(n->nbytes < strlen(s)){
        n->bytes = realloc(n->bytes, 2 * strlen(s));
        n->nbytes = 2 * strlen(s);
		    int x = 0;
		    while(x < n->nbytes){
	    	    n->bytes[x] = '0';
	    	    x++;
		    }
    }
    int digitStart = 0;
    int digitEnd = 0;
    int z = 0;
    while(z < strlen(s)){
		    if(isdigit(s[z])){
	    	    digitStart = z;
	    	    while(isdigit(s[z])){
				          z++;
	    	    }
	    	digitEnd = z; // Note this is one greater than the position so less than needed
	    	break;
		}
		z++;
    }
    int i = digitEnd - 1;
    int top = 0;
    while(i >= digitStart){
        n->bytes[top] = (char) s[i];
        top++;
        i--;
    }
    return 1;
}

// Display a BigNum in decimal format
void showBigNum(BigNum n){
    int check = 0;
    int i = n.nbytes - 1;
    while(i >= 0){
        if(check){
            printf("%c", n.bytes[i]);
        }
        else{
            if(n.bytes[i] != '0'){
                check = 1;
                printf("%c", n.bytes[i]);
            }
        }
    i--;
    }
    return;
}
