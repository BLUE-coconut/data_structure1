#pragma once
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include"chlist.h"

const int FixMAXSPACE = 100;
//�������ֶ���˳��洢��һ��������һ����̬�����ô��Ƕ�λ����
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
	int StrCompare(char p[])//��S<p����1����S=p����0����S>p����-1
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
		if (pos + len > Space)tail = Space;//�����ַ������ȣ����ȡ���ַ���β
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
	//�ᱻ�Զ����գ�����Ҫdestroy
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
		dummyhead->len = 0;//�ַ���ʵ�ʳ���
		dummyhead->space = INITSPACE;//�ַ������пռ�
	}
	void StrAssign(char p[])//�����ʼ�ַ���
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
	int StrCompare(char p[])//��S<p����1����S=p����0����S>p����-1(��ǰ����Ƚϣ����ַ���ļ�Ϊ��)
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
		int size = StrLength();//concatǰ�ַ�������
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
	char* subStr(int pos, int len)//������Ϊpos���ַ���ȡlen���ַ�
	{
		char* sub;
		int tail = pos + len;
		if (pos + len >= dummyhead->len)
		{
			tail = dummyhead->len;//�����ַ������ȣ����ȡ���ַ���β
			printf("substring get to the tail ,len: %d\n", tail- pos);
		}
		for (int i = pos; i < tail; i++)
		{
			*(sub + i) = *(dummyhead->cn+i);
		}
		printf("get substring successfully\n");
		return sub;
	}
	void clear()//ֻ�������
	{
		for (int i = StrLength()-1; i >= 0; i++)
		{
			*(dummyhead->cn + i) = 0;
		}
		dummyhead->len = 0;
	}
	void destroy()//�ͷſռ�
	{
		free(dummyhead->cn);
		free(dummyhead);
	}
};

