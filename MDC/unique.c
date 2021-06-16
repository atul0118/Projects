#include"headers.h"
#include"prototypes.h"
int unique(char ch,int i,char* a)
{
	int j;
	if(i==0)
		return 1;	
	//printf("%c",s);
	for(j=0;j<i;j++)
	{
	if(ch == *(a+j) )
	{
		return 0;
	}
	}
	return 1;
	

}
