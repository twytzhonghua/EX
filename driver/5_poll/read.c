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

/*
struct timeval 数据结构为：  
struct timeval   
{  
  int tv_sec; //* seconds   
  int tv_usec; //* microseconds    
}; 
*/



/*
int select(int numfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval 
*timeout); 
*/

/*
除此之外，我们还将使用下列API： 
FD_ZERO(fd_set *set)――清除一个文件描述符集；  
FD_SET(int fd,fd_set *set) ――将一个文件描述符加入文件描述符集中； 
FD_CLR(int fd,fd_set *set)――将一个文件描述符从文件描述符集中清除；
FD_ISSET(int fd,fd_set *set) ――判断文件描述符是否被置位。 
*/



int main(void)
{
	int fd, ret;
	fd_set rfds; 
  struct timeval tv={3,0}; //超时3秒
		    
	int val=0;
	
	/*open device*/
	fd = open("/dev/chardrv_test",O_RDWR);
	if(fd != -1 )
	{
	  while(1)
	  {
	  		// 查看globalvar 是否有输入 
		    FD_ZERO(&rfds); 
		    FD_SET(fd, &rfds); 
				printf("1111111\n");
				// 设置超时时间为 5s 
      	tv.tv_sec = 5; 
      	tv.tv_usec = 0; 
		    
			  select(fd + 1, &rfds, NULL, NULL, &tv); 
			  printf("22222222222\n");
      	// 数据是否可获得？ 
      	if (FD_ISSET(fd, &rfds)) 
      	{
	      		read(fd,&val,4);
						printf("buf is *%d\n",val);
						
						if(val == 0)
						{
						  close(fd);
						  break;
  
						}
      	}
      	else{
      		printf("No data input in 5 seconds\n");
      	}	
      	
      	
	  }

	}
	else
	{
	  printf("open failed\n");
	}


	return 0;

}

