#include<stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	char * argvv[ ]={"./shell",NULL};
	char * envp[ ]={NULL};
	if(argc!=3)
	{
		printf("expected 2 arguments,but got %d\n",argc-1);
	}
	else
	{		
		int num1=atoi(argv[1]);
		int num2=atoi(argv[2]);
		if(num1>=num2)
			printf("min number is %d\n",num2);
		else
		{
			printf("min number is %d\n",num1);			
		}
	}
	
	execve("./shell",argvv,envp);
	return 0;	
}
