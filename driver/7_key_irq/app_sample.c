#include <sys/types.h> 
#include <sys/stat.h> 
#include <stdio.h> 
#include <fcntl.h> 
#include <signal.h> 
#include <unistd.h> 
#define MAX_LEN 100 
void input_handler(int num) 
{ 
  char data[MAX_LEN]; 
  int len; 
 
  // ��ȡ����� STDIN_FILENO �ϵ����� 
    len = read(STDIN_FILENO, &data, MAX_LEN);
    data[len] = 0; 
    printf("input available:%s\n", data); 
    } 
 
main() 
{ 
  int oflags; 
 
  // �����ź��������� 
  signal(SIGIO, input_handler); 
  fcntl(STDIN_FILENO, F_SETOWN, getpid()); 
    oflags = fcntl(STDIN_FILENO, F_GETFL); 
    fcntl(STDIN_FILENO, F_SETFL, oflags | FASYNC); 
 
  // ������һ����ѭ��������ʲô�������ˣ�ֻ���ź��ܼ��� input_handler ������ 
  // ���������û�������ѭ����������ִ����� 
  while (1); 
} 