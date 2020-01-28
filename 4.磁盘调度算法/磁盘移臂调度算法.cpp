#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define N 30
int len;//���̷������г���
int begin;//��дͷ��ʼλ��
int disk_queue[N];//���̷������еĶ���
int flag[N];//��Ǹôŵ��Ƿ񱻷��ʣ�1��ʾ�����ʣ�0��ʾδ������
int sum;//�Ʊ�����

FILE* P_SSTF,* P_SCAN;
////////////
void SSTF()
{
//	FILE *stream;
    P_SSTF=fopen("C:\\Users\\����\\Desktop\\����ϵͳʵ��\\4.���̵����㷨\\SSTF.txt","w+");
	int i,tmp,min_distance;
	int begin_SSTF=begin;
	fprintf(P_SSTF,"%d\n",begin_SSTF);
	sum=0;
	for(i=0;i<len;i++)
	{
		min_distance=INT_MAX;//������С���벢�趨��ʼֵ
		for(int j=0;j<len;j++)//Ѱ����С����
		{
			if(min_distance>abs(disk_queue[j]-begin_SSTF) && flag[j]==0)
			{
				min_distance=abs(disk_queue[j]-begin_SSTF);
				tmp=j;
			}
		}
		flag[tmp]=1;//tmpΪѰ�ҵ�������
		sum+=min_distance;
		fprintf(P_SSTF,"%d\n",disk_queue[tmp]);
		printf("\t\t%d\t   %d\n",disk_queue[tmp],min_distance);
		begin_SSTF=disk_queue[tmp];//�����ŵ���ʼλ��
	}
	fclose(P_SSTF);
}

////////////
void SCAN()
{
	P_SCAN=fopen("C:\\Users\\����\\Desktop\\����ϵͳʵ��\\4.���̵����㷨\\SCAN.txt","w+");
	int i,tmp,min_distance;
	int begin_SCAN=begin;
	fprintf(P_SCAN,"%d\n",begin_SCAN);
//	int l_r;//�жϷ���Ϊ1��ʾ���ұ߽��У�Ϊ0��ʾ����߷������
	int len_l,len_r;//���ڴ��̿�ʼλ�õ����ұߵĴŵ���Ŀ
	sum=0;
	len_r=len_l=0;
	//���㴦�ڴ��̿�ʼλ�õ����ұߵĴŵ���Ŀ
	for(i=0;i<len;i++)
	{
		if(begin_SCAN<=disk_queue[i])
			len_r++;
	}
	len_l=len-len_r;
	for(i=0;i<len_r;i++)
	{
		min_distance=INT_MAX;//������С���벢�趨��ʼֵ
		for(int j=0;j<len;j++)//Ѱ����С����
		{
			if((disk_queue[j]-begin_SCAN)>=0 && min_distance>(disk_queue[j]-begin_SCAN) && flag[j]==0)
			{
				min_distance=disk_queue[j]-begin_SCAN;
				tmp=j;
			}
		}
		flag[tmp]=1;
		sum+=min_distance;
		fprintf(P_SCAN,"%d\n",disk_queue[tmp]);///
		printf("\t\t%d\t   %d\n",disk_queue[tmp],min_distance);
		begin_SCAN=disk_queue[tmp];//�����ŵ���ʼλ��
	}
	for(i=0;i<len_l;i++)
	{
		min_distance=INT_MAX;//������С���벢�趨��ʼֵ
		for(int j=0;j<len;j++)//Ѱ����С����
		{
			if((disk_queue[j]-begin_SCAN)<0 && min_distance>(begin_SCAN-disk_queue[j]) && flag[j]==0)
			{
				min_distance=begin_SCAN-disk_queue[j];
				tmp=j;
			}
		}
		flag[tmp]=1;
		sum+=min_distance;
		fprintf(P_SCAN,"%d\n",disk_queue[tmp]);//
		printf("\t\t%d\t   %d\n",disk_queue[tmp],min_distance);
		begin_SCAN=disk_queue[tmp];//�����ŵ���ʼλ��
	}
}


void main()
{
	printf("\n           ��ӭ���������Ʊ۵���\n");
	printf("******************************************************\n");
	printf("���̷������г��ȣ�");
	scanf("%d",&len);
	printf("��дͷ��ʼλ�ã�");
	scanf("%d",&begin);
	printf("��������̷������У�");
	for(int i=0;i<len;i++)
	{
		scanf("%d",&disk_queue[i]);
		flag[i]=0;
	}
	printf("******************************************************\n");
	printf("                    *SSTF�㷨*\n");
	printf("                    **********\n\n");
	printf("\t���ʵĴδŵ���\t�ƶ��Ĵŵ���\n");
	SSTF();
	printf("\n\t\tSSTF�Ʊ�������%d\n",sum);
	printf("******************************************************\n");
	printf("                    *SCAN�㷨*\n");
	printf("                    *********\n\n");
	printf("\t���ʵĴδŵ���\t�ƶ��Ĵŵ���\n");
	for(i=0;i<len;i++)
	{
		flag[i]=0;
	}
	SCAN();
	printf("\n\t\tSCAN�Ʊ�������%d\n",sum);
}