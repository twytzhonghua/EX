#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	DIR *dp;
	struct dirent *dirp;
	
	if(argc != 2)
		printf("usage: ls directory_name\n");
		
	if((dp = opendir(argc[1]==NULL)))
		printf("error directory\n");
		
	while(NULL != (dirp=read(dp)))
		printf("%s\n", dirp->d_name);
		
	closedir(dp);
	exit(0);
		
}