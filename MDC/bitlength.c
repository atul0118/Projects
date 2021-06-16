#include"headers.h"
#include"prototypes.h"

int bitlength(char* ma)
{
	int l;
	l=strlen(ma);
	printf("\n");
	printf("NUMBER OF UNIQUE ELEMENTS ARE = %d\n",l);
	if (l<4)
		return 2;
	else if(l<8)
		return 3;
	else if(l<16)
		return 4;
	else if(l<32)
		return 5;
	else if(l<64)
		return 6;
	else if(l<128)
		return 7;
	else
		printf("Characters greater than 128");



}
