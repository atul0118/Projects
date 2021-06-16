#include"headers.h"
#include"prototypes.h"
int find_index(char* ma, char ch)
{
	int i,j;

	for(j=0;j<strlen(ma);j++)
	{
		if (ch==*(ma+j))
			return j; 
	}
}
