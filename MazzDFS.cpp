#include<stdio.h>
#include<stdlib.h>
#include<iostream>
//�ݹ鷽��
using namespace std;
int r, c;//�Թ���ģ
int start[2], endend[2];//����յ�
char mass[120][120];//��ʼ���Թ�
int step[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };//��������

int pos_check(int x, int y)
{
	if (x <= 0 || x > r || y <= 0 || y > c)return 0;
	if (mass[x][y] == '.')return 1;
	else return 0;
}

void print_mass()
{
	for (int i = 1; i <= r; i++)
	{
		for (int j = 1; j <= c; j++)
		{
			printf("%c ", mass[i][j]);
		}
		printf("\n");
	}
}

int ans = 0;
void dfs(int x, int y)
{
	if (pos_check(x, y))
	{
		mass[x][y] = 'o';
		if (x == endend[0] && y == endend[1])
		{
			ans++;
			printf("��%d������·����\n", ans);
			print_mass();
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				int nx = x + step[i][0];
				int ny = y + step[i][1];
				dfs(nx, ny);
			}
		}

		mass[x][y] = '.';
	}
	return;
}
/*
int main()
{
	printf("�������Թ��������������ո������\n");
	cin >> r >> c;
	printf("�����Թ�\n");
	//�Թ������ӣ�1��1����ʼ
	for (int i = 1; i <= r; i++)
	{
		for (int j = 1; j <= c; j++)
		{
			cin >> mass[i][j];
		}
	}
	printf("���������\n");
	cin >> start[0] >> start[1];
	printf("�������յ�\n");
	cin >> endend[0] >> endend[1];
	dfs(start[0], start[1]);
	printf("һ��%d��·��", ans);
}*/
