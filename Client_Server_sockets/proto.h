struct client_data
{
	int oprn1;
	int oprn2;
	char opr;
	pid_t pid;
};

struct request
{
	long int type;
	struct client_data data;
};

struct result
{
	long int type;
	int ans;
};

