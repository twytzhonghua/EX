#include <stdio.h>

int a[100];
char pstr;

long long *p;
int main(void)
{
	printf("sizeof(a)=%d\n",sizeof(a));
	printf("sizeof(a[100])=%d\n",sizeof(a[100]));
	printf("sizeof(&a)=%d\n",sizeof(&a));
	printf("sizeof(&a[0])=%d\n",sizeof(&a[0]));
	printf("sizeof(&pstr)=%d\n",sizeof(&pstr));
	printf("long long *p=%d\n",sizeof(p));
}
