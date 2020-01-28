#include <unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char *argv[]) 
{
	char * argvv[ ]={"./shell",NULL};
	char * envp[ ]={NULL};
	if(argc!=4)
	{
		printf("expected 3 arguments,but got %d\n",argc-1);
	}
	else
	{
		float num1=atof(argv[1]);
		float num2=atof(argv[2]);
		float num3=atof(argv[3]);
		printf("average is %.2f\n",(num1+num2+num3)/3.0);
	}	
	execve("./shell",argvv,envp);
	return 0;
}
