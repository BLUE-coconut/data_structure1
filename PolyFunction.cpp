#pragma once
#include<iostream>
#include<stdio.h>
#include<stdlib.h>

class hhl_function
{
public:

	int len;
	typedef int eletype;
	typedef struct LinkNode
	{
		eletype exp;
		eletype coe;
		struct LinkNode* next;
		LinkNode() : exp(0),coe(0), next(NULL) {}
		LinkNode(eletype a, eletype b) : exp(a),coe(b), next(NULL) {}
		LinkNode(eletype a, eletype b, struct LinkNode* x) : exp(a), coe(b), next(x) {}
	}LN;

	LN* dummyhead;
	hhl_function()
	{
		dummyhead = new LN();//使用new进行分配 
		len = 0;
	}
	void create_function(char ch[])
	{
		int pre = 0;//记录前一个状态(字母前0，字母后1)
		int fh = 1;//记录符号
		int cur = 0;//当前数
		int coe=0, exp=0;//当前项系数和指数
		for (int i = 0; i < strlen(ch); i++)
		{
			if (pre)
			{
				if (ch[i] == '+')
				{
					if (cur)
					{
						exp = cur * fh;
						add_element(exp, coe);
						exp = 0;
						pre = 0;
						cur = 0;
					}
					fh = 1;
				}
				else if (ch[i] == '-')
				{
					if (cur)
					{
						exp = cur * fh;
						add_element(exp, coe);
						cur = 0;
						exp = 0;
						pre = 0;
					}
					fh = -1;
				}
				else if (ch[i] == '=')
				{
					exp = cur * fh;
					if (exp)add_element(exp, coe);
					break;
				}
				else if (ch[i] >= '0' && ch[i] <= '9')
				{
					cur = cur * 10 + ch[i] - '0';
				}
				else
				{
					printf("input erro1\n");
				}
			}
			else
			{
				if (ch[i] == '+')
				{
					if (cur)
					{
						coe = cur * fh;
						if (coe)add_element(exp, coe);
						cur = 0;
						pre = 0;
					}
					fh = 1;
				}
				else if (ch[i] == '-')
				{
					
					if (cur)
					{
						coe = cur * fh;
						if (coe)add_element(exp, coe);
						cur = 0;
						pre = 0;
					}
					fh = -1;
				}
				else if (ch[i] == '=')
				{
					coe = cur * fh;
					if(coe)add_element(exp,coe);
					break;
				}
				else if (ch[i] >= '0' && ch[i] <= '9')
				{
					cur = cur * 10 + ch[i] - '0';
				}
				else if (ch[i]=='x')
				{
					coe = cur * fh;
					fh = 1;
					cur = 0;
					pre = 1;
					exp = 1;
				}
				else
				{
					printf("input erro1\n");
				}
			}
		}
	}
	void add_element(eletype exp, eletype coe)
	{
		LN* pre = dummyhead;
		LN* p = dummyhead->next;
		LN* pnew = new LN(exp,coe);
		while (p)
		{
			if (p->exp > exp)
			{
				pnew->next = p;
				pre->next = pnew;
				printf("add element %d successfully\n", p->exp);
				return;
			}
			else if (p->exp == exp)
			{
				p->coe += coe;
				printf("add element %d\n",p->coe);
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
		printf("add element %d successfully\n", pnew->exp);
	}
	LN* copy()
	{
		LN* cp_dummy = new LN();
		LN* p = dummyhead;
		LN* cp_p = cp_dummy;
		while (p->next)
		{
			p = p->next;
			LN* cp_new = new LN(p->exp,p->coe);
			cp_p->next = cp_new;
			cp_p = cp_p->next;
		}
		return cp_dummy;
	}
	void calculate(LN* funB,char op)
	{
		LN* ans = copy();
		LN* pa = ans;
		LN* pb = funB;
		if (op == '+')
		{
			while (pa->next && pb->next)
			{
				if (pa->next->exp > pb->next->exp)
				{
					LN* pnew = new LN(pb->next->exp, pb->next->coe);
					pnew->next = pa->next;
					pa->next = pnew;
				}
				else if (pa->next->exp == pb->next->exp)
				{
					pa->next->coe += pb->next->coe;
					if (pa->next->coe == 0)
					{
						pa->next = pa->next->next;
					}
					pa = pa->next;
					pb = pb->next;
				}
				else
				{
					pa = pa->next;
				}
				if (pb->next)
				{
					pa->next = pb->next;
				}
			}
		}
		else if (op == '-')
		{
			while (pa->next && pb->next)
			{
				if (pa->next->exp > pb->next->exp)
				{
					LN* pnew = new LN(pb->next->exp, -pb->next->coe);
					pnew->next = pa->next;
					pa->next = pnew;
				}
				else if (pa->next->exp == pb->next->exp)
				{
					pa->next->coe -= pb->next->coe;
					if (pa->next->coe == 0)
					{
						pa->next = pa->next->next;
					}
					pa = pa->next;
					pb = pb->next;
				}
				else
				{
					pa = pa->next;
				}
				if (pb->next)
				{
					pa->next = pb->next;
				}
			}
		}
		else
		{
			printf("synex erro");
		}
		LN* p = ans->next;
		if (p == NULL)printf("空集");
		while (p != NULL)
		{
			if (p->next)printf("%dx^%d +", p->coe, p->exp);
			else printf("%dx^%d", p->coe, p->exp);
			p = p->next;
		}
		printf("\n");
	}
	//insert element(insert after a)
	bool insert(int a, eletype exp, eletype coe)
	{
		LN* p = dummyhead;
		for (int i = 1; i <= a; i++)
		{
			p = p->next;
			if (p == NULL)
			{
				printf("insert erro\n");
				return false;
			}
		}
		LN* newp = new LN(exp,coe, p->next);
		p->next = newp;
		len++;
		printf("insert successfully\n");
		return true;
	}
	//del element(according to index)
	bool del(int a)
	{
		LN* p = dummyhead;
		for (int i = 1; i <= a; i++)
			//p is the node before a
		{
			if (p->next == NULL)//a does not exist 
			{
				printf("del erro\n");
				return false;
			}
		}
		LN* pdel = p->next;
		p->next = pdel->next;
		delete pdel;//与new配套使用 
		len--;
		printf("del successfully\n");
		return true;
	}
	//find element(according to index)
	bool findi(int a)//return bool
	{
		LN* p = dummyhead;
		for (int i = 1; i <= a; i++)
		{
			p = p->next;
			if (p == NULL)
			{
				printf("cannot find\n");
				return false;
			}
		}
		printf("find node successfully\n");
		return true;
	}
	//get element data(according to index)
	eletype get(int a)//return data
	{
		LN* p = dummyhead;
		for (int i = 1; i <= a; i++)
		{
			p = p->next;
			if (p == NULL)
			{
				printf("cannot find\n");
				return 0;
			}
		}
		printf("find successfully %d %d\n", p->exp,p->coe);
		return p->exp,p->coe;
	}
	//get length
	int get_len()
	{
		return len;
	}
	//clear & destroy
	void clear()//只剩头节点 
	{
		LN* p = dummyhead;
		LN* pcur = p->next;
		while (pcur != NULL)
		{
			LN* pnx = pcur->next;
			delete(pcur);
			pcur = pnx;
		}
		len = 0;
		printf("finish clearing\n");
	}

	void showall()
	{
		LN* p = dummyhead->next;
		if (p == NULL)printf("nothing to show");
		while (p != NULL)
		{
			if(p->next)printf("%dx^%d +", p->coe,p->exp);
			else printf("%dx^%d", p->coe, p->exp);
			p = p->next;
		}
		printf("\n");
	}



};


/*
int main()
{
	char funA[30], funB[30];
	printf("输入funA:");
	gets_s(funA);
	hhl_function A;
	A.create_function(funA);
	A.showall();
	printf("输入funB:");
	gets_s(funB);
	hhl_function B;
	B.create_function(funB);
	B.showall();
	printf("A+B = ");
	A.calculate(B.dummyhead, '+');
	printf("A-B = ");
	A.calculate(B.dummyhead, '-');
	return 0;
}
*/