#include <stdio.h>

int main(void)
{

	void p;
	unsigned i ;
	for (i=9;i>=0;i--)
	{
		printf("i=%u\n",i);
	}


	unsigned j = 10;

	printf("i+j=%d,sizeof(void p)=%d\n",i+j, sizeof(p));

	return 0;

}
