#pragma once
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include"chlist.h"

const int FixMAXSPACE = 100;
//以下两种都是顺序存储（一个定长，一个动态），好处是定位方便
class FixString
{
private:
	int Space = FixMAXSPACE;
public:
	char Fstring[FixMAXSPACE + 1];
	void StrAssign(char p[])
	{
		Fstring[0] = (char)strlen(p);
		memcpy(Fstring + 1, p, sizeof(p));
	}
	int StrCompare(char p[])//若S<p返回1，若S=p返回0，若S>p返回-1
	{
		int flag = 0,num= strlen(p);
		if (strlen(p) > (int)Fstring[0])flag = 1,num= (int)Fstring[0];
		else if (strlen(p) < (int)Fstring[0])flag = -1;
		for (int i = 1; i <= num; i++)
		{
			if (p[i - 1] > Fstring[i])return 1;
			else if (p[i - 1] < Fstring[i])return -1;
		}
		return flag;
	}
	int StrLength()
	{
		return (int)Fstring[0];
	}
	void Concat(char p[])
	{
		int size = StrLength();
		for (int i = 0; i < strlen(p);i++)
		{
			if (size + 1>Space)break;
			Fstring[++size] = p[i];
		}
		Fstring[0] = (char)size;
	}
	char* subStr(int pos,int len)
	{
		char sub[FixMAXSPACE];
		int tail = pos + len;
		if (pos + len > Space)tail = Space;//超出字符串长度，则截取到字符串尾
		for (int i = pos; i < tail; i++)
		{
			sub[i - pos] = Fstring[i + 1];
		}
		return sub;
	}
	void clear()
	{
		for (int i = 1; i <= StrLength(); i++)
		{
			Fstring[i] = 0;
		}
		Fstring[0] = (char)0;
	}
	//会被自动回收，不需要destroy
};

class DynamicString
{
private:
	const int INITSPACE = 100;
	const int INCREMENT = 50;
	struct charnode
	{
		char* cn;
		int len;
		int space;
	};
public:
	charnode* dummyhead = (charnode*)malloc(sizeof(charnode));
	DynamicString()
	{
		dummyhead->cn = (char*)malloc(sizeof(char)*INITSPACE);
		dummyhead->len = 0;//字符串实际长度
		dummyhead->space = INITSPACE;//字符串现有空间
	}
	void StrAssign(char p[])//输入初始字符串
	{
		dummyhead->len = strlen(p);
		while (dummyhead->len > dummyhead->space)
		{
			dummyhead->space += INCREMENT;
			dummyhead->cn = (char*)realloc(dummyhead->cn, sizeof(char) * dummyhead->space);
		}
		for (int i = 0;i< strlen(p); i++)
		{
			*(dummyhead->cn+i) = p[i];
		}

	}
	int StrCompare(char p[])//若S<p返回1，若S=p返回0，若S>p返回-1(从前往后比较，有字符大的即为大)
	{
		int flag = 0, num = strlen(p);
		if (strlen(p) > dummyhead->len)flag = 1, num = dummyhead->len;
		else if (strlen(p) < dummyhead->len)flag = -1;
		for (int i = 1; i <= num; i++)
		{
			if (p[i - 1] > *(dummyhead->cn+i))return 1;
			else if (p[i - 1] < *(dummyhead->cn + i))return -1;
		}
		return flag;
	}
	int StrLength()
	{
		return dummyhead->len;
	}
	void Concat(char p[])
	{
		int size = StrLength();//concat前字符串长度
		dummyhead->len += strlen(p);
		while (dummyhead->len >= dummyhead->space)
		{
			dummyhead->space += INCREMENT;
			dummyhead->cn = (char*)realloc(dummyhead->cn,sizeof(char) * dummyhead->space);
		}
		for (int i = 0; i < strlen(p); i++)
		{
			*(dummyhead->cn+size) = p[i];
			size++;
		}
		printf("concat successful\n");
	}
	char* subStr(int pos, int len)//从索引为pos的字符截取len个字符
	{
		char* sub;
		int tail = pos + len;
		if (pos + len >= dummyhead->len)
		{
			tail = dummyhead->len;//超出字符串长度，则截取到字符串尾
			printf("substring get to the tail ,len: %d\n", tail- pos);
		}
		for (int i = pos; i < tail; i++)
		{
			*(sub + i) = *(dummyhead->cn+i);
		}
		printf("get substring successfully\n");
		return sub;
	}
	void clear()//只清空内容
	{
		for (int i = StrLength()-1; i >= 0; i++)
		{
			*(dummyhead->cn + i) = 0;
		}
		dummyhead->len = 0;
	}
	void destroy()//释放空间
	{
		free(dummyhead->cn);
		free(dummyhead);
	}
};

