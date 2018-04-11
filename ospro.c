#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define min_pid 100
#define max_pid 1000
#define cb CHAR_BIT

int size = max_pid - min_pid + 1;

unsigned char *b;

int allocate_map();
int allocate_pid();
void release_pid(int pid);

int main() 
{
	int map = allocate_map();
	if (map == 1) 
	{
	        printf("\nData Structure initialized.\n");
	        int id = 0, i = 0;
	        while (i < 100) 
		{
	        	int val = allocate_pid();
            		printf("\nProcess %d: pid = %d", i+1, val);
            		i++;
        	}
        release_pid(103);
        printf("\nProcess 103 released.");
        release_pid(105); 
        printf("\nProcess 105 released.");
        int val = allocate_pid(); 
        printf("\nProcess %d : pid = %d\n", i+1, val);
    }
    else printf("\nFailed to initialize data structure.\n");
}

/* Creates and initializes a data structure for representing pids;
 returns —1 if unsuccessful, 1 if successful */

int allocate_map()
{
	b = (unsigned char*)malloc((size+cb-1)/cb * sizeof(char));
	if (b) return 1;
	return -1;
}

/* Allocates and returns a pid; returns -1
if unable to allocate a pid (all pids are in use) */

int allocate_pid() 
{
	int i = 0;
	int pid = b[i/cb] & (1 << (i & (cb-1)));
	while (pid != 0) 
    	{
		i++;
	        pid = b[i/cb] & (1 << (i & (cb-1)));
	}
	if (i+min_pid > max_pid) return -1;
	b[i/cb] |= 1 << (i & (cb-1));
return i+min_pid;
}

/* Releases a pid */

void release_pid(int pid)
{
	if (pid < 100) 
	{
		printf("\nInvalid PID: It should lie between 100 and 1000.");
		return;
        }
    	int i = pid - min_pid;
    	b[i/cb] &= ~(1 << (i & (cb-1)));
}
