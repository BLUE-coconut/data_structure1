#include<stdio.h>
#include<stdlib.h>
#include<iostream>
//递归方法
using namespace std;
int r, c;//迷宫规模
int start[2], endend[2];//起点终点
char mass[120][120];//初始化迷宫
int step[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };//东南西北

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
			printf("第%d个可行路径：\n", ans);
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
	printf("请输入迷宫行数和列数（空格隔开）\n");
	cin >> r >> c;
	printf("输入迷宫\n");
	//迷宫索引从（1，1）开始
	for (int i = 1; i <= r; i++)
	{
		for (int j = 1; j <= c; j++)
		{
			cin >> mass[i][j];
		}
	}
	printf("请输入起点\n");
	cin >> start[0] >> start[1];
	printf("请输入终点\n");
	cin >> endend[0] >> endend[1];
	dfs(start[0], start[1]);
	printf("一共%d条路径", ans);
}*/
