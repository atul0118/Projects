#include"headers.h"
#include"prototypes.h"

void main()
{
	int r;
	while(1)
	{
	printf("\n");
	//printf("asd");
	r=mainmenu();

	switch(r)
	{
		case 1:
			compression();
			printf("\n");
			printf("COMPRESSION COMPLETED!\n");
		//	sleep(1);
			break;
		case 2:
			decompression();
			break;
		case 0:
			exit(EXIT_SUCCESS);
		default:
			printf("Invalid choice\n");
			
	}
	}
}
