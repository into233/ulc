
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
 
#define buflen 4096
#define COPYMODE 0644 
 
int main(int ac,char *av[])
{
	int source_fd,target_fd,char_num;
	char buf[buflen];
	if(ac != 3)
	{
		fprintf(stderr,"usage:%s source destination\n",*av);
		exit(-1);
	}
	
	//read the source
	if((source_fd = open(av[1],O_RDONLY)) == -1)	//false read
		oops("can not open",av[1]);		//oop is what??
	
	if((target_fd = creat(av[2],COPYMODE)) == -1)	//false creat
		oops("can not  creat",av[2]);
	
	//read the data to buf
	while((char_num = read(source_fd,buf,buflen))>0) //char_num is real length
	{
		if(write(target_fd,buf,char_num) != char_num)	//if yes show that reading and writing donot match
		{
			oops("write error to",av[2]);
		}
	}
	
	if(char_num == -1)
		oops("error closing files",av[1]);
	
	if(close(source_fd) == -1 || close(target_fd) == -1)
		oops("error closing files","");
}
 
void oops(char* s1,char* s2)
{
	fprintf(stderr,"Error:%s",s1);
	perror(s2);
	exit(1);
}