#pragma once
#include<iostream>
#include<stdio.h>
#include<stdlib.h>

//���ִ洢�ṹ��1)ͷβ����洢��  2)��չ��������洢��
class GenList_ht_int
{
private :
	typedef int eletype;

public:
	typedef struct listnode
	{
		int tag;//0Ϊԭ�ӽ�㣬1Ϊ�б���
		union mid
		{
			eletype data;
			struct {
				listnode* hp, * tp;
			}p;
		};
	}LN;
	struct head
	{
		listnode* next = NULL;
	}dummyhead;

	void create(char string[])
	{

		for (int i = 0; i < strlen(string); i++)
		{
			
		}
		
	}
	
};
class GenList_exp_int
{
private:
	typedef int eletype;
public:
	typedef struct listnode
	{
		int tag;
		union mid
		{
			eletype data;
			listnode* ph;
		};
		listnode* pt;
	};
	struct head
	{
		listnode* next = NULL;
	}dummyhead;


};