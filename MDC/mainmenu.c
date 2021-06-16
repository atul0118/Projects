#include"headers.h"
#include"prototypes.h"
int mainmenu()
{
	int a;
	printf("Please enter your choice:\n");
	printf("1: compression\n");
	printf("2: decompression\n");
	printf("0: exit\n");
	scanf("%d",&a);
	return a;

}

