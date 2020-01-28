#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>
#include <string>
using namespace std;


#define N1 50
#define N2 500
bool bitmap[N2]={0};//λʾͼ��ʼΪfalse������û��ռλ
int signal;//ѡ��λʾͼ
typedef struct filetable
{
	string filename;
	int indexed_block_node;//�ļ���������
}filetable;
vector<filetable> fat_Tab;//�����ļ����������

class Index_Block_Node
{
public:
	int Block[5];//5����Ĵ�ſ�����
	Index_Block_Node()
	{
		for(int i=0;i<5;i++)
		{
			Block[i]=0;
		}
	}
	Index_Block_Node(int* x) 
	{
		for (int i=0;i<5;i++) 
		{
			Block[i]=*(x+i);
		}
	}
};
Index_Block_Node* M=new Index_Block_Node[N2];//����500 �����̿�����
void Createfiles()
{
	srand((unsigned)time(NULL));
	for(int i=0;i<N1;i++)
	{
		filetable file_buff;
		stringstream st;
		st<<(i+1);
		string str=st.str();
		file_buff.filename=str+".txt";
		for(int j=0;j<N2;j++)
		{
			if(bitmap[j]==false)//�ÿ����
			{
				file_buff.indexed_block_node=j;
				bitmap[j]=true;
				//��Ϊÿ���СΪ2K�����������������1��5���飬����������
				int blocks=(rand()%5)+1;
				for(int k=1;k<=blocks;k++)
				{
					M[file_buff.indexed_block_node].Block[k-1]=k+file_buff.indexed_block_node;//ע�⡶���޸ģ������д�
					bitmap[k+file_buff.indexed_block_node]=true;
				}
				break;
			}
		}
		fat_Tab.push_back(file_buff);//����ε��µķ�������
	}
}

void Delete_Odd_File()//ɾ���������ļ�ռλ
{
	vector<filetable> ::iterator tmp=fat_Tab.begin();
	for(int i=0;i<N1;i+=2)
	{
		bitmap[tmp->indexed_block_node]=false;
		for(int j=0;j<5;j++)
		{
			int t=M[tmp->indexed_block_node].Block[j];
			if(t!=0)
			{
				bitmap[t]=false;
				M[tmp->indexed_block_node].Block[j]=0;
			}
			else
			{
				break;
			}
		}	
		//ɾ����Ӧ���ļ�
		tmp=fat_Tab.erase(tmp);
		tmp++;
	}
}

void New_File()
{
	string name[5]={"A.txt","B.txt","C.txt","D.txt","E.txt"};
	double size[5]={7,5,2,9,3.5};
	for(int i=0;i<5;i++)
	{
		filetable tmp;
		tmp.filename=name[i];
		for(int j=0;j<N2;j++)
		{
			if(bitmap[j]==0)//��ʾδ��ռλ
			{
				bitmap[j]=true;
				tmp.indexed_block_node=j;
				for(int k=0;k<size[i]/2.0;k++)
				{
					for(int t=j+1;t<N2;t++)
					{
						if(bitmap[t]==0)
						{
							bitmap[t]=true;
							M[tmp.indexed_block_node].Block[k]=t;
							break;
						}

					}

				}
				break;
			}
		}
		fat_Tab.push_back(tmp);////����ε��µķ�������
	}
}

void Print()
{
	vector<filetable> ::iterator tmp=fat_Tab.begin();
	cout<<"                --------------------------------------------------------------------------------------------\n";
	cout<<"                ����������������������������������<���1604�� ʢ����>����������������������������������������\n";
	cout<<"                --------------------------------------------------------------------------------------------\n";
	cout<<'\t'<<'\t'<<'\t'<<"       "<<"===�ļ���=="<<"==�ļ���������===="<<"=======�ļ���ſ��========="<<endl;
	for(;tmp!=fat_Tab.end();tmp++)
	{
		cout<<'\t'<<'\t'<<'\t'<<'\t'<<" "<<tmp->filename<<'\t'<<'\t';
		printf("% 3d\t\t",tmp->indexed_block_node);
		for(int i=0;i<5;i++) 
		{
			printf("%3d  ",M[tmp->indexed_block_node].Block[i]);
		}
		cout<<endl;
	}
	cout<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
	if(signal==1)
		printf("��������������������������������������������������������������������������<�����ļ����λʾͼ>����������������������������������������������������������������������\n");
    else
		if(signal==2)
			printf("��������������������������������������������������������������������������<ɾ���ļ����λʾͼ>����������������������������������������������������������������������\n");
	else
		printf("��������������������������������������������������������������������������<����ļ����λʾͼ>����������������������������������������������������������������������\n");
	cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
	cout<<"------";
	int u;
	for(u=0;u<10;u++)
	{
		cout<<"0"<<u<<" ";

	}
	for(;u<50;u++)
	{
		cout<<u<<" ";

	}
	cout<<"-------"<<endl;
	cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
	int j=0;
	for(int i=0;i<N2-1;i++) 
	{
		if(i==0)
		{
			cout<<"--"<<"0"<<j<<"-- ";
		
		}
		j++;
		cout<<bitmap[i]<<"  ";
		if((i+1)%50==0)
		{
			cout<<"------";
			cout<<endl;	
			cout<<"--0"<<j/50<<"-- ";
		}
	}
	cout<<bitmap[i]<<"  ";
	cout<<"------";
	cout<<endl;	
	cout<<"------";
	cout<<"-------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
	cout<<endl;
}

int main() 
{
	
	Createfiles();
	signal=1;

	Print();
	Delete_Odd_File();
	signal=2;
	
	Print();
	New_File();
	signal=3;
	
	Print();
	return 0;
}
