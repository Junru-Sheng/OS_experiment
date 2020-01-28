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
		vector<string> cmdlist;//����string���� 
		string temp;
		while(ss>>temp)//��cmd��ѹ�������� 
		{
			cmdlist.push_back(temp);
		}
		if(cmdlist.empty())//cmdΪ��ʱ�� 
		{
			cout<<"JUNRU_CMD:";
			continue;
		}
		else if(cmdlist[0]=="max")//��Ϊmaxʱ 
		{
			if(cmdlist.size()>3)//�жϷǷ��� 
			{
				cout<<"expected 2 arguments,but got "<<cmdlist.size()-1<<endl;
				cout<<"JUNRU_CMD:";
				continue;
			}
			char arg1[50],arg2[50];
			strcpy(arg1, cmdlist[1].c_str());//cmdlist[1].c_str()���ָ�����������������Ϊarg1�������������Բ���ֱ������c_str���ص��ַ�����Ҫ����strcpy�Ⱥ������и��ƺ���ʹ��  
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
