
#include "types.h"
#include "stat.h"
#include "user.h" /* write(), read() atoi(), free(), printf()*/


char buf[512];

#define defaultLine 10

//Alg:first read specified number of line, then if another specified number of line 
//is read, replace the old lines. 
void tail(int fd, int line)
{
	int n, i, l = 0; int maxLineSize = 0;
	int lineSize = 0;
	// if line is given 0 by user or by (atoi(a) == 0), do nothing 
	while((l < line) && (n = read(fd, buf, sizeof(buf))) > 0)
	{
		if(n < 0){
			printf(1, "tail: read error\n");
			exit();
		}
		printf(1, "%d\n", sizeof(buf));
		//char* tail = malloc( l * maxLineSize );
		printf(1, "n = %d\n", n);
		for(i = 0; i < n; i++){
			printf(1, "buf[i] = %c", buf[i]);
			if(buf[i] == '\n'){
				l++;
				if(lineSize > maxLineSize){
					maxLineSize = lineSize;
				}
				lineSize = 0;
			} else {
				lineSize++;
			}
		}
		printf(1, "maxLineSize = %d", maxLineSize);
		char* tail = malloc( l * maxLineSize );
		//printf(1, "tail before memmove= %s\n", tail);
		memmove(tail, buf, n);
		//tail = "a";
		printf(1, "tail after = %s\n", tail);
		printf(1, "wtf");
		
	}

}



int errMess(char* file)
{
	int fd;	
	//can not open file
	if((fd = open(file, 0)) < 0){
		printf(1, "tail: cannot open %s\n",file);
		exit();
	}
	return fd;
}

int main(int argc, char *argv[])
{
	int fd, i, line;
	//tail
	if(argc == 1){
		tail(0, defaultLine);
		exit();
	}
	//tail -11, tail file
	if(argc == 2){
		if(argv[1][0] == '-'){
			tail(0, atoi(argv[1] + 1));
		} else {
			fd = errMess(argv[1]);
			tail(fd, defaultLine);
			close(fd);
		}
		exit();
	}
	// tail -11 file... 
	if(argv[1][0] == '-'){
		for(i = 2; i < argc; i++){
			line = atoi(argv[1] + 1);
			fd = errMess(argv[i]);
			tail(fd, line);
			close(fd);
		}
	} else {
		//tail file file...
		for(i = 1; i < argc ; i++){
			fd = errMess(argv[i]);
			tail(fd, defaultLine);
			close(fd);
		}
	}
	free(buf);
	exit();
}
