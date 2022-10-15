#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include"chlist.h"
class hhlSet :public LinkList_char
{
private :
	char name;
public :
	hhlSet(char set_name)//子类定义了构造函数，先执行父类，再执行子类
	{
		name = set_name;

	}
	void set_add_element(eletype ch)
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
		if (op == '&')  //交集
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
		else if (op == '|')  //并集
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
		else if (op == '-')  //差集
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
		else
		{
			printf("operate erro");
			return NULL;
		}

		//show answer
		LN* p = ans->next;
		if (p == NULL)printf("空集");
		while (p != NULL)
		{
			printf("%c ", p->data);
			p = p->next;
		}
		printf("\n");
		return ans;
	}

	int relation(LN* setB)
	{
		// A包含B = 2、A包含于B = 1、AB相等 = 0、AB没特定关系 = -1
		LN* pa = dummyhead;
		LN* pb = setB;
		int flag = 0;//起始状态AB相同
		// A 包含 B没有的元素 flag=1，else flag = -1
		while (pa->next && pb->next)
		{
			if (pa->next->data < pb->next->data)// A 包含 B没有的元素
			{
				if (flag < 0)
				{
					if (flag == -1)printf("A B不相交\n");
					else printf("A B相交\n");
					return -1;
				}
				if(flag==0)flag = 1;
				pa = pa->next;
			}
			else if (pa->next->data > pb->next->data)// B 包含 A没有的元素
			{
				if (flag > 0)
				{
					if (flag == 1)printf("A B不相交\n");
					else printf("A B相交\n");
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
				if(flag==1)printf("A B不相交\n");
				else printf("A B相交\n");
				return -1;
			}
			printf("A包含于B\n");
			return 1;
		}
		else if (pa->next)
		{
			if (flag < 0)
			{
				if (flag == -1)printf("A B不相交\n");
				else printf("A B相交\n");
				return -1;
			}
			printf("A包含B\n");
			return 2;
		}
		else
		{
			printf("A=B\n");
			return 0;
		}

	}

	void help()
	{
		printf("& 表示求交集\n | 表示求并集\n - 表示求差集\n");
	}
};


/*int main()
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
	A.help();//运算符号说明
	printf("opertor:");
	char op;
	op=getchar();
	A.calculate(B.dummyhead,op);
	A.relation(B.dummyhead);
	A.destroy()
	return 0;
}*/