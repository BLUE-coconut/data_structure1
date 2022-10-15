#pragma once
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
int n, m;
const int MAXSIZE=20;
int Map[MAXSIZE][MAXSIZE] = { 0 };

bool judge(int x,int y)
{
	if (Map[x][y])return false;
	if (x<1 || x>n || y<1 || y>m)return false;
	return true;
}
int move[4][2] = { {0,1},{1,0},{0,-1},{-1,0}};

typedef struct stackNode
{
	int x, y, dir;
	stackNode* next;
}SN;
class ChStack_Mazz
{
public:
	
	int size = 0;//��¼ջ����������
	SN* GetTopPre()//����pop
	{
		//��Ҫȷ������
		SN* pre = dummyhead;
		SN* p = pre->next;
		if (!p)
		{
			printf("pop erro,stack empty\n");
			return NULL;
		}
		while (p->next)
		{
			pre = p;
			p = pre->next;
		}
		return pre;
	}
	SN* GetTop()//����push
	{
		return top;
	}


	SN* dummyhead = (SN*)malloc(sizeof(SN));//ͷ�ڵ�Ϊ��
	ChStack_Mazz()
	{
		dummyhead->next = NULL;
	}
	SN* top = dummyhead;

	SN* Top()
	{
		if (empty())
		{
			printf("top erro ,stack empty");
			return NULL;
		}
		return top;
	}
	SN* pop()
	{
		SN* num = (SN*)malloc(sizeof(SN));
		if (empty())
		{
			printf("pop erro\n");
			return NULL;
		}
		SN* prenode = GetTopPre();
		SN* popnode = top;
		num->x = popnode->x;
		num->y = popnode->y;
		num->dir = popnode->dir;

		top = prenode;
		prenode->next = NULL;
		free(popnode);
		size--;

		printf("pop successful\n");
		return num;
	}
	void push(SN* p)
	{
		SN* newnode = (SN*)malloc(sizeof(SN));
		if (!newnode)
		{
			printf("push erro\n");
			return;
		}
		newnode->dir = p->dir;
		newnode->x = p->x;
		newnode->y = p->y;
		newnode->next = NULL;
		top->next = newnode;
		top = top->next;
		size++;
		printf("push successful\n");
	}
	void clear()
	{
		while (!empty())
		{
			pop();
		}
		size = 0;
		printf("clear successful\n");
	}
	void destroy()
	{
		clear();
		free(dummyhead);
		printf("destroy successful\n");
	}
	bool empty()
	{
		return dummyhead == top;
	}
	int getsize()
	{
		return size;
	}
	void showall()//��ջ�׵�ջ��
	{
		SN* p = dummyhead;
		while (p->next)
		{
			printf("(%d,%d,%d)\n", p->next->x, p->next->y, p->next->dir);
			p = p->next;
		}
	}
	void onepath(int sx,int sy,int tx,int ty)
	{
		int flag = 0;//flag==0û�ҵ�
		SN* p = (SN*)malloc(sizeof(SN));
		p->x = sx;
		p->y = sy;
		p->dir = 0;
		push(p);
		while (!empty())
		{
			SN* pre = pop();
			pre->dir+=1;
			if (pre->dir > 4)
			{
				Map[pre->x][pre->y] = 0;
				continue;
			}
			else
			{
				Map[pre->x][pre->y] = 1;
				push(pre);
			}
			//printf("%d %d %d\n", pre->x, pre->y, pre->dir);
			int nx = pre->x + move[pre->dir - 1][0];
			int ny = pre->y + move[pre->dir - 1][1];
			if (nx == tx && ny == ty)
			{
				flag++;
				printf("path%d:\n", flag);
				showall();
				printf("get(%d,%d)\n", tx, ty);
				break;//�ҵ�ֱ��break
			}
			if (judge(nx, ny))
			{
				SN* newp = (SN*)malloc(sizeof(SN));
				newp->x = nx;
				newp->y = ny;
				newp->dir = 0;
				push(newp);
			}
		}
		if (flag==0)
		{
			printf("no path\n");
		}
	}
	void allpath(int sx, int sy, int tx, int ty)
	{
		//���ӻ��ݹ���
		int flag = 0;//flag==0û�ҵ�
		SN* p = (SN*)malloc(sizeof(SN));
		p->x = sx;
		p->y = sy;
		p->dir = 0;
		push(p);
		while (!empty())
		{
			SN* pre = pop();
			pre->dir += 1;
			if (pre->dir > 4)
			{
				//����ʱ��·����ȥ���ĵ�״̬����
				Map[pre->x][pre->y] = 0;
				continue;
			}
			else
			{
				//·�����߹��ĵ���Ϊ1�������ظ���
				Map[pre->x] [pre->y] = 1;
				push(pre);
			}
			//printf("%d %d %d\n", pre->x, pre->y, pre->dir);
			int nx = pre->x + move[pre->dir - 1][0];
			int ny = pre->y + move[pre->dir - 1][1];
			if (nx == tx && ny == ty)
			{
				flag++;
				printf("path %d:\n", flag);
				showall();
				printf("get(%d,%d)\n", tx, ty);
				continue;
			}
			if (judge(nx, ny))
			{
				SN* newp = (SN*)malloc(sizeof(SN));
				newp->x = nx;
				newp->y = ny;
				newp->dir = 0;
				push(newp);
			}
		}
		if (flag == 0)
		{
			printf("no path\n");
		}
	}
};


/*
int main()
{
	printf("map size n*m:\n");
	printf("n=");
	scanf_s("%d", &n);
	printf("m=");
	scanf_s("%d", &m);
	printf("������%d*%d�ľ���(1Ϊ�ϰ���0Ϊ�յ�)", n, m);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			scanf_s("%d", &Map[i][j]);
		}
	}
	int sx, sy, tx, ty;
	printf("�������x,y:");
	scanf_s("%d%d", &sx, &sy);
	printf("�����յ�x,y:");
	scanf_s("%d%d", &tx, &ty);
	ChStack_Mazz hhlMazz;
	hhlMazz.clear();
	hhlMazz.allpath(sx, sy, tx, ty);
	hhlMazz.destroy();
	return 0;
}*/

/*
//�ݹ鷽��
#include<stdio.h>
#include<stdlib.h>
int r,c;//�Թ���ģ
int start[2],end[2];//����յ�
char mass[120][120];//��ʼ���Թ�
int step[4][2]={{1,0},{0,1},{-1,0},{0,-1}};//��������

int pos_check(int x,int y)
{
	if(x<0||x>r-1||y<0|| y>c-1)return 0;
	if(mass[x][y]=='.')return 1;
	else return 0;
}

int forward(int x,int y)
{
	int curx=x,cury=y;
	for(int i=0;i<4;i++)
	{
		curx=x+step[i][0];
		cury=y+step[i][1];
		if(curx==end[0] && cury==end[1])
		{
			mass[curx][cury]='*';
			return 1;
		}
		if(pos_check(curx,cury))
		{
			mass[curx][cury]='*';
			if(forward(curx,cury))return 1;//��̽��һ��
		}
	}
	mass[x][y]='o';
	return 0;
}

void print_mass()
{
	 for (int i=0;i<r;i++)
	{
		for (int j=0;j<c;j++)
		{
			printf("%c",mass[i][j]);
			if(j!=c-1)printf(" ");
		}
		 if(i!=r-1)printf("\n");
	}
}

int main()
{
	scanf("%d%d",&r,&c);
	getchar();
	for (int i=0;i<r;i++)
	{
		for (int j=0;j<c;j++)
		{
			mass[i][j]=getchar();
			getchar();
		}
	}
	scanf("%d%d",&start[0],&start[1]);
	scanf("%d%d",&end[0],&end[1]);
	if(forward(start[0],start[1])) print_mass();
	else printf("None\n");
}
*/