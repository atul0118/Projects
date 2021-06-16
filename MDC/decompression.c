#include"headers.h"
#include"prototypes.h"

int decompression()
{
	char* ma;
	char* key=(char*)malloc(20);
	printf("\n");
	printf("%s started\n", __func__);
	printf("Enter the file name which contains key for decryption: ");
	scanf(" %s",key);
	//ma=Masterarray()
	printf("before getMasterarray\n");
	ma=getMasterarray(key);
	printf("After getMasterarray\n");
	int b=bitlength(ma);
	switch(b)
	{
                case 2:
                        printf("2-bit decompression\n");
                        break;
                case 3:
                        printf("3-bit decompression\n");
			decomp3(ma);
                        break;
                case 4:
                        printf("4-bit decompression\n");
                        decomp4(ma);
                        break;
                case 5:
                        printf("5-bit decompression\n");
                        break;
                case 6:
                        printf("6-bit decompression\n");
                        break;
                case 7:
                        printf("7-bit decompression\n");
                        break;
                default:
                        printf("length greater than 128 characters\n");
        }

	printf("%s ended\n", __func__);
}
