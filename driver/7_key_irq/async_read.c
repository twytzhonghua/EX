/*******************************************************************************
*** Filename:
***			app.c
***	Copyright (c) 2013 Wistron
***	All rights reserved.
***
***	Description:
***		a simple test app.
***
***	Author/Creat Date:
*** 		Albert Yang, Apri 29,13
***
***	Modification History:
***			Apr 30, 13
***	Note:
*** 	
****************************************************************************/

#include <stdio.h>   /*For the printf/scanf ...*/ 
#include <stdlib.h>    /*For exit()*/
#include <sys/types.h>/*For size_t/....*/
#include <sys/stat.h>/*For some documents related information*/
#include <fcntl.h>/*For open()/close()/read()....*/
#include <string.h>
#include <sys/time.h> 
#include <unistd.h> 
#include <signal.h>


int fd;
int val=0;

void my_signal_fun(int signum)
{
	read(fd,&val,4);
	printf("read value=%d\n", val);

	if(val == 0)
		close(fd);
}


int main(void)
{
	

	// 启动信号驱动机制 
	signal(SIGIO, my_signal_fun);

	fd = open("/dev/chardrv_test",O_RDWR);
	if(fd != -1 )
	{
		int oflags;
		
		fcntl(fd, F_SETOWN, getpid());//tell kernel driver pid

		oflags = fcntl(fd, F_GETFL);
		fcntl(fd, F_SETFL, oflags | FASYNC);

		while(1)
		{
		  sleep(1000);
			
		}

	}
	else
	{
	  printf("open failed\n");
	}


	return 0;

}

