// myls.c ... my very own "ls" implementation
// Keegan Gyoery z5197058
// 2018-04-09
// Lab 6 Solution

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAXDIRNAME 100
#define MAXFNAME   200
#define MAXNAME    20

char *rwxmode(mode_t, char *);
char *username(uid_t, char *);
char *groupname(gid_t, char *);

int main(int argc, char *argv[]){
    // String buffers for various names
    char dirname[MAXDIRNAME]; // Buffer for name of directory
    char uname[MAXNAME+1]; // Buffer to hold the name of the user
    char gname[MAXNAME+1]; // Buffer to hold the name of the group
    char mode[MAXNAME+1]; // Buffer to hold the chmod string (rwx)

    // Collect the directory name, with "." as default
    if(argc < 2){
      strlcpy(dirname, ".", MAXDIRNAME);
    }
    else{
      strlcpy(dirname, argv[1], MAXDIRNAME);
    }

    // Check that the name really is a directory
    struct stat info;
    if(stat(dirname, &info) < 0){
       perror(argv[0]); exit(EXIT_FAILURE); 
    }
    if((info.st_mode & S_IFMT) != S_IFDIR){
       fprintf(stderr, "%s: Not a directory\n",argv[0]); exit(EXIT_FAILURE); 
    }

    struct stat sb; // Struct to store the directory entries metadata

    DIR *df; // Pointer to the directory
    df = opendir(dirname); // Open the directory and store the pointer to the stream in df
    struct dirent *entry; // Struct to point to the directory entry's metadata 

    // Loop through the directory entries and return specific metadata
    while((entry = readdir(df)) != NULL){
       if(entry->d_name[0] != '.'){ // Ignores hidden files
           char path[MAXFNAME] = {'\0'}; // Re-initialise the buffer to hold the path
           size_t n; // Stores the number of characters copied from dirname into path
           n = strlcpy(path, dirname, MAXFNAME);
           path[n] = '/'; // Add the / operator to reference a directory entry
           strlcat(path, entry->d_name, MAXFNAME); // Concatenate the name of the directory entry to the path
           lstat(path, &sb); // Set the metadata for the directory entry to the struct previously set up
           printf("%s %-15s %-8.8s %8lld %s\n", rwxmode(sb.st_mode, mode), username(sb.st_uid, uname), groupname(sb.st_gid, gname), sb.st_size, entry->d_name);
       }
    }

    closedir(df); // Close the directory stream pointed to by df
    return EXIT_SUCCESS;
}

// Converts octal mode to -rwxrwxrwx string
char *rwxmode(mode_t mode, char *str){
    char octalstr[7]; // Set up a buffer to hold the values of the octal mode
    unsigned mask; // Create a bit mask
    int last3bits; // Holds the value of the last 3 isolated bits to easily convert to octal
    int i = 6; // Increment to work backwards through buffer
    while(i >= 0){
        mask = (1 << 3) - 1; // Create the bit mask by shifting 1 by 3 bits right, then subtract 1
        last3bits = mode & mask; // Collect the last three bits via a bitwise &
        octalstr[i] = last3bits + '0'; // Place the octal value in the buffer at position i
        mode = mode >> 3; // Move the bit values left by 3 to discard already grabbed bits and get the next 3
        i--; // Move back a position in the buffer
    }

    // Decipher what type the directory entry is based on the octal values in positions 1 and 2 
    if(octalstr[1] == '1' && octalstr[2] == '0'){
        str[0] = '-'; // Regular
    }
    else if(octalstr[1] == '1' && octalstr[2] == '2'){
        str[0] = 'l'; // Symbolic Link
    }
    else if(octalstr[1] == '0' && octalstr[2] == '4'){
        str[0] = 'd'; // Directory
    }
    else{
        str[0] = '?'; // Other
    }
            
    int top = 1; // Start adding the permission flags to the buffer at position 1
    int j = 4; // Start reading the octal buffer at position 4 as this is where the values for permission flags begin
    int num; // Hold the value at octalstr[j] as an int
    
    // Add the 'r', 'w', 'x', '-' to the buffer passed to the function
    while(j < 7){
        num = octalstr[j] - '0';
        if(num >= 4){
            str[top] = 'r';
            num = num - 4;
        }
        else{
            str[top] = '-';
        }
        top++;
        if(num >= 2){
            str[top] = 'w';
            num = num - 2;
        }
        else{
            str[top] = '-';
        }
        top++;
        if(num >= 1){
            str[top] = 'x';
            num = num - 1;
        }
        else{
            str[top] = '-';
        }
        top++;
        j++;
    }

    str[top] = '\0'; // Add the null terminator
    return str;
}

// convert user id to user name
char *username(uid_t uid, char *name)
{
   struct passwd *uinfo = getpwuid(uid);
   if (uinfo == NULL)
      snprintf(name, MAXNAME, "%d?", (int)uid);
   else
      snprintf(name, MAXNAME, "%s", uinfo->pw_name);
   return name;
}

// convert group id to group name
char *groupname(gid_t gid, char *name)
{
   struct group *ginfo = getgrgid(gid);
   if (ginfo == NULL)
      snprintf(name, MAXNAME, "%d?", (int)gid);
   else
      snprintf(name, MAXNAME, "%s", ginfo->gr_name);
   return name;
}
