#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>
#include <string>
using namespace std;


#define N1 50
#define N2 500
bool bitmap[N2]={0};//位示图初始为false，代表没有占位
int signal;//选择位示图
typedef struct filetable
{
	string filename;
	int indexed_block_node;//文件块索引号
}filetable;
vector<filetable> fat_Tab;//建立文件分配表数组

class Index_Block_Node
{
public:
	int Block[5];//5个块的存放快的序号
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
Index_Block_Node* M=new Index_Block_Node[N2];//定义500 个磁盘块序列
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
			if(bitmap[j]==false)//该块空闲
			{
				file_buff.indexed_block_node=j;
				bitmap[j]=true;
				//因为每块大小为2K，所以我们随机产生1—5个块，并放入其中
				int blocks=(rand()%5)+1;
				for(int k=1;k<=blocks;k++)
				{
					M[file_buff.indexed_block_node].Block[k-1]=k+file_buff.indexed_block_node;//注意《有修改，可能有错
					bitmap[k+file_buff.indexed_block_node]=true;
				}
				break;
			}
		}
		fat_Tab.push_back(file_buff);//把这次的新的分配表放入
	}
}

void Delete_Odd_File()//删除奇数的文件占位
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
		//删除对应的文件
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
			if(bitmap[j]==0)//表示未被占位
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
		fat_Tab.push_back(tmp);////把这次的新的分配表放入
	}
}

void Print()
{
	vector<filetable> ::iterator tmp=fat_Tab.begin();
	cout<<"                --------------------------------------------------------------------------------------------\n";
	cout<<"                ……………………………………………<电计1604班 盛君如>……………………………………………………\n";
	cout<<"                --------------------------------------------------------------------------------------------\n";
	cout<<'\t'<<'\t'<<'\t'<<"       "<<"===文件名=="<<"==文件块索引号===="<<"=======文件存放块号========="<<endl;
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
		printf("…………………………………………………………………………………………………<创建文件后的位示图>……………………………………………………………………………………………\n");
    else
		if(signal==2)
			printf("…………………………………………………………………………………………………<删除文件后的位示图>……………………………………………………………………………………………\n");
	else
		printf("…………………………………………………………………………………………………<添加文件后的位示图>……………………………………………………………………………………………\n");
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
