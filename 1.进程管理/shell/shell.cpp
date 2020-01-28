#include <iostream>
#include <unistd.h>
#include <sstream>
#include <vector>
using namespace std;
int main(int argc, char *argv[])
{
	string cmd;
	cout<<"JUNRU_CMD:";
	while(getline(cin, cmd))
	{
		stringstream ss(cmd);
		vector<string> cmdlist;//定义string数组 
		string temp;
		while(ss>>temp)//把cmd串压入数组中 
		{
			cmdlist.push_back(temp);
		}
		if(cmdlist.empty())//cmd为空时， 
		{
			cout<<"JUNRU_CMD:";
			continue;
		}
		else if(cmdlist[0]=="max")//当为max时 
		{
			if(cmdlist.size()>3)//判断非法性 
			{
				cout<<"expected 2 arguments,but got "<<cmdlist.size()-1<<endl;
				cout<<"JUNRU_CMD:";
				continue;
			}
			char arg1[50],arg2[50];
			strcpy(arg1, cmdlist[1].c_str());//cmdlist[1].c_str()最后指向的内容是垃圾，因为arg1对象被析构，所以不能直接利用c_str返回的字符串，要利用strcpy等函数进行复制后再使用  
			strcpy(arg2, cmdlist[2].c_str());
			char * argv[ ]={"./max",arg1,arg2,NULL};
			char * envp[ ]={NULL};
			execve("./max",argv,envp);////////////////////////////
		}
		else if(cmdlist[0]=="min")
		{
			if(cmdlist.size()>3)
			{
				cout<<"expected 2 arguments,but got "<<cmdlist.size()-1<<endl;
				cout<<"JUNRU_CMD:";
				continue;
			}
			char arg1[50],arg2[50];
			strcpy(arg1, cmdlist[1].c_str());
			strcpy(arg2, cmdlist[2].c_str());
			char * argv[ ]={"./min",arg1,arg2,NULL};
			char * envp[ ]={NULL};
			execve("./min",argv,envp);
		}
		else if(cmdlist[0]=="ave")
		{
			if(cmdlist.size()!=4)
			{
				cout<<"expected 3 arguments,but got "<<cmdlist.size()-1<<endl;
				cout<<"JUNRU_CMD:";
				continue;
			}
			char arg1[50],arg2[50],arg3[50];
			strcpy(arg1, cmdlist[1].c_str());
			strcpy(arg2, cmdlist[2].c_str());
			strcpy(arg3, cmdlist[3].c_str());
			char * argv[ ]={"./ave",arg1,arg2,arg3,NULL};
			char * envp[ ]={NULL};
			execve("./ave",argv,envp);
		}
		else if(cmdlist[0]=="quit"||cmdlist[0]=="q")
		{
			cout<<"See you!"<<endl;
			return 0;
		}
		else
		{
			cout<<"UNKNOW JUNRU_CMD:"<<cmdlist[0]<<endl;
		}
		cout<<"JUNRU_CMD:";
	}
}
