#pragma once
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include"chlist.h"
#include<queue>
using namespace std;

class hhlSet :public LinkList_char
{
private :
	char name;
	char* S;
	int dict_len = 0;
	void get_S()
	{
		printf("����ȫ����Сn������0��ȫ����ΪĬ�ϡ���26��Сд��ĸ����\n");
		scanf_s("%d",&dict_len);
		if (dict_len > 0)
		{
			printf("����ȫ����\n");
			scanf_s("%s", S);
		}
		else//Ĭ��
		{
			char x[] = "abcdefghijklmnopqrstuvwxyz";
			S = x;
		}
		
	}
public :
	hhlSet(char set_name)//���ඨ���˹��캯������ִ�и��࣬��ִ������
	{
		name = set_name;
		get_S();
	}
	void set_add_element(eletype ch)//���ϵĹ�����������ģ����ֵ���
	{
		LN* pre = dummyhead;
		LN* p = dummyhead->next;
		LN* pnew = new LN(ch);
		while (p)
		{
			if (p->data>ch)
			{
				pnew->next = p;
				pre->next = pnew;
				printf("add element %c successfully\n",ch);
				return;
			}
			else if (p->data == ch)
			{
				printf("%c already exist in set%c\n",ch,name);
				return;
			}
			else
			{
				pre = p;
				p = p->next;
			}
		}
		pnew->next = pre->next;
		pre->next = pnew;
		printf("add element %c successfully\n",ch);
	}

	void create_set(eletype str[])
	{
		for (int i = 0; i < strlen(str); i++)
		{
			if(str[i]<='z'&&str[i]>='a')
				set_add_element(str[i]);
		}
	}

	LN* copy()
	{
		LN* cp_dummy = new LN();
		LN* p = dummyhead;
		LN* cp_p = cp_dummy;
		while (p->next)
		{
			p = p->next;
			LN* cp_new = new LN(p->data);
			cp_p->next = cp_new;
			cp_p = cp_p->next;
		}
		return cp_dummy;
	}

	LN* calculate(LN* setB , char op)
	{
		LN* ans = copy();
		LN* pa = ans;
		LN* pb = setB;
		if (op == '&')  //����
		{
			while (pa->next && pb->next)
			{
				if (pb->next->data < pa->next->data)
				{
					pb = pb->next;
				}
				else if (pb->next->data == pa->next->data)
				{
					pa = pa->next;
					pb = pb->next;
				}
				else
				{
					pa->next = pa->next->next;
				}
			}
			if (pa->next)
			{
				pa->next = NULL;
			}
			
		}
		else if (op == '|')  //����
		{
			while (pa->next && pb->next)
			{
				if (pb->next->data < pa->next->data)
				{
					LN* pnew = new LN(pb->next->data);
					pnew->next = pa->next;
					pa->next = pnew;
					printf("add element %c successfully\n", pb->next->data);
				}
				else if (pb->next->data == pa->next->data)
				{
					pa = pa->next;
					pb = pb->next;
				}
				else
				{
					pa = pa->next;
				}
			}
			if(pb->next)
			{
				pa->next = pb->next;
			}
		}
		else if (op == '-')  //�
		{
			while (pa->next && pb->next)
			{
				if (pb->next->data < pa->next->data)
				{
					pb = pb->next;
				}
				else if (pb->next->data == pa->next->data)
				{
					pa->next = pa->next->next;
				}
				else
				{
					pa = pa->next;
				}
			}
		}
		else if (op == 'U')//Ĭ�ϼ����ڵ�Ԫ�ط�����ȫ����
		{
			LN* cur = dummyhead->next;
			int i = 0;
			queue<char> U_res;
			for (; i < dict_len; i++)
			{
				if (!cur ||*(S + i) != cur->data)
				{
					U_res.push(*(S + i));
				}
				else
				{
					cur = cur->next;
				}
			}
			if (U_res.empty())
			{
				printf("����Ϊ��\n");
			}
			else
			{
				while (!U_res.empty())
				{
					char out = U_res.front();
					printf("%c ", out);
					U_res.pop();
				}
				printf("\n");
			}
			
			
		}
		else
		{
			printf("operate erro");
			return NULL;
		}

		//show answer
		LN* p = ans->next;
		if (p == NULL)printf("�ռ�");
		while (p != NULL)
		{
			printf("%c ", p->data);
			p = p->next;
		}
		printf("\n");
		return ans;
	}

	int relation(LN* setB)//���Ϲ�ϵ
	{
		// A����B = 2��A������B = 1��AB��� = 0��ABû�ض���ϵ = -1
		LN* pa = dummyhead;
		LN* pb = setB;
		int flag = 0;//��ʼ״̬AB��ͬ
		// A ���� Bû�е�Ԫ�� flag=1��else flag = -1
		while (pa->next && pb->next)
		{
			if (pa->next->data < pb->next->data)// A ���� Bû�е�Ԫ��
			{
				if (flag < 0)
				{
					if (flag == -1)printf("A B���ཻ\n");
					else printf("A B�ཻ\n");
					return -1;
				}
				if(flag==0)flag = 1;
				pa = pa->next;
			}
			else if (pa->next->data > pb->next->data)// B ���� Aû�е�Ԫ��
			{
				if (flag > 0)
				{
					if (flag == 1)printf("A B���ཻ\n");
					else printf("A B�ཻ\n");
					return -1;
				}
				if(flag==0)flag = -1;
				pb = pb->next;
			}
			else
			{
				if (flag >= 0)
				{
					flag = 2;
				}
				if(flag <= 0)
				{
					flag = -2;
				}
				pa = pa->next;
				pb = pb->next;
			}
		}
		if (pb->next)
		{
			if (flag > 0)
			{
				if(flag==1)printf("A B���ཻ\n");
				else printf("A B�ཻ\n");
				return -1;
			}
			printf("A������B\n");
			return 1;
		}
		else if (pa->next)
		{
			if (flag < 0)
			{
				if (flag == -1)printf("A B���ཻ\n");
				else printf("A B�ཻ\n");
				return -1;
			}
			printf("A����B\n");
			return 2;
		}
		else
		{
			printf("A=B\n");
			return 0;
		}

	}

	int relation_ele(char ele)//������Ԫ�صĹ�ϵ
	{
		LN* head = dummyhead;
		while (head->next)
		{
			if (head->next->data == ele)//Ԫ�����ڵ�ǰ����
			{
				return 1;
			}
			head = head->next;
		}
		return 0;
	}

	void help()
	{
		printf(" & ��ʾ�󽻼�\n | ��ʾ�󲢼�\n - ��ʾ��\n U ��ʾ�󲹼�\n");
	}
};


/*
int main()
{
	char setA[30],setB[30];
	printf("setA=");
	gets_s(setA);
	printf("setB=");
	gets_s(setB);
	hhlSet A('A');
	hhlSet B('B');
	A.create_set(setA);
	B.create_set(setB);
	printf("setA:");
	A.showall();
	printf("setB:");
	B.showall();
	A.help();//�������˵��
	printf("opertor:");
	char op;
	op=getchar();
	A.calculate(B.dummyhead,op);
	A.relation(B.dummyhead);
	A.destroy();
	B.destroy();
	return 0;
}*/