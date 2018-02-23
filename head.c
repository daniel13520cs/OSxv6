#include "types.h"
#include "stat.h"
#include "user.h" /* write(), read() atoi()*/

char buf[1];

#define defaultLine 10

void head(int fd, int line)
{
	// if line is given 0 by user or by (atoi(a) == 0), do nothing 
	int n;
	int count = 0;
	while((count < line) && (n = read(fd, buf, sizeof(buf)) > 0))
	{
		//\r return key, \n next line
		if(strchr("\n", buf[0])){
			count++;
		}
		write(1, buf, n);
		if(n < 0){
			printf(1, "head: read error\n");
			exit();
		}
	}
	free(buf);
}


int errMess(char* file)
{
	int fd;	
	//can not open file
	if((fd = open(file, 0)) < 0){
		printf(1, "head: cannot open %s\n",file);
		exit();
	}
	return fd;
}

int main(int argc, char *argv[])
{
	int fd, i, line;
	//head
	if(argc == 1){
		head(0, defaultLine);
		exit();
	}
	//head -11, head file
	if(argc == 2){
		if(argv[1][0] == '-'){
			head(0, atoi(argv[1] + 1));
		} else {
			fd = errMess(argv[1]);
			head(fd, defaultLine);
			close(fd);
		}
		exit();
	}
	// head -11 file... 
	if(argv[1][0] == '-'){
		for(i = 2; i < argc; i++){
			line = atoi(argv[1] + 1);
			fd = errMess(argv[i]);
			head(fd, line);
			close(fd);
		}
	} else {
		//head file file...
		for(i = 1; i < argc ; i++){
			fd = errMess(argv[i]);
			head(fd, defaultLine);
			close(fd);
		}
	}
	exit();
}
