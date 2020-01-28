
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
//	char * argvv[10];
	//char * envp[10];
	char * argvv[ ]={"./shell",NULL};
	char * envp[ ]={NULL};
	if(argc!=3)
		printf("expected 2 arguments,but got %d\n",argc-1);
	else
	{
		
		int num1=atoi(argv[1]);
		int num2=atoi(argv[2]);
		if(num1>=num2)
			printf("max number is %d\n",num1);
		else
		{
			printf("max number is %d\n",num2);			
		}
	}
	
	execve("./shell",argvv,envp);
	return 0;
}

