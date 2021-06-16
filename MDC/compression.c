#include"headers.h"
#include"prototypes.h"
int compression()
{
	int fd;
	char* file;
        file=(char*)malloc(sizeof(char)*20);
        printf("Enter the name of file to compress: ");
        scanf(" %s",file);
        fd=openfile(file);
	char *ma;
	char read;
	int i,bl;
	printf("%s function started\n", __func__);
	sleep(1);

	ma=Masterarray(fd);
	bl=bitlength(ma);
	switch(bl)
	{
		case 2:
			printf("2-bit compression\n");
			break;
		case 3:
			printf("3-bit compression\n");
			comp3(ma,fd);
			break;
		case 4:
			printf("4-bit compression\n");
			comp4(ma,fd);
			break;
		case 5:
			printf("5-bit compression\n");
			break;
		case 6:
			printf("6-bit compression\n");
			break;
		case 7:
			printf("7-bit compression\n");
			break;
		default:
			printf("length greater than 128 characters\n");
	}
}
