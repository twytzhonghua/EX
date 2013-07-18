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
struct timeval ���ݽṹΪ��  
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
����֮�⣬���ǻ���ʹ������API�� 
FD_ZERO(fd_set *set)�D�D���һ���ļ�����������  
FD_SET(int fd,fd_set *set) �D�D��һ���ļ������������ļ����������У� 
FD_CLR(int fd,fd_set *set)�D�D��һ���ļ����������ļ����������������
FD_ISSET(int fd,fd_set *set) �D�D�ж��ļ��������Ƿ���λ�� 
*/



int main(void)
{
	int fd, ret;
	fd_set rfds; 
  struct timeval tv={3,0}; //��ʱ3��
		    
	int val=0;
	
	/*open device*/
	fd = open("/dev/chardrv_test",O_RDWR);
	if(fd != -1 )
	{
	  while(1)
	  {
	  		// �鿴globalvar �Ƿ������� 
		    FD_ZERO(&rfds); 
		    FD_SET(fd, &rfds); 
				printf("1111111\n");
				// ���ó�ʱʱ��Ϊ 5s 
      	tv.tv_sec = 5; 
      	tv.tv_usec = 0; 
		    
			  select(fd + 1, &rfds, NULL, NULL, &tv); 
			  printf("22222222222\n");
      	// �����Ƿ�ɻ�ã� 
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

