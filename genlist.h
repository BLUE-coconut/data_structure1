#pragma once
#include<iostream>
#include<stdio.h>
#include<stdlib.h>

//两种存储结构：1)头尾链表存储法  2)扩展线性链表存储法
class GenList_ht_int
{
private :
	typedef int eletype;

public:
	typedef struct listnode
	{
		int tag;//0为原子结点，1为列表结点
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