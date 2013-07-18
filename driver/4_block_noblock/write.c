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




int main(void)
{
	int fd, ret;
	
	int val=0;

	/*open device*/
	fd = open("/dev/chardrv_test",O_RDWR);
	if(fd != -1 )
	{
	  while(1)
	  {
	  	printf("\nplease input num>>:");
			scanf("%d",&val);
			write(fd,&val,4);
	  	
	  	if(val == -1)
			{
			  close(fd);
			  break;
			  
			}
	  }

	}
	else
	{
	  printf("open failed\n");
	}


	return 0;

}

