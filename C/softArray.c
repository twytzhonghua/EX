#include <stdio.h>
#include <stdlib.h>

typedef struct st_type
{
int i;
int a[20];
}type_a;


int main()
{
//	type_a *p = (type_a*)malloc(sizeof(type_a)+100*sizeof(int));
	struct st_type *p = (struct st_type*)malloc(sizeof(struct st_type));
	printf("sizeof(p)=%d\n",sizeof(p));
	printf("sizeof(struct st_type)=%d\n",sizeof(struct st_type));
}
