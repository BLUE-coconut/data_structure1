#pragma once
#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>
#include"sqstack.h"
#include"cirlist.h"
using namespace std;
const int N = 12;

void basic_operation()
{
	SqStack_int sqs;
	int ele;
	int n;
	printf("输入数据个数：");
	scanf_s("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		printf("输入数据：");
		scanf_s("%d", &ele);
		sqs.push(ele);
	}
	int ans;
	ans=sqs.GetTop();
	printf("%d\n", ans);
	sqs.pop_get(ans);
	ans=sqs.GetTop();
	printf("%d\n", ans);
	sqs.destroy();
}

int priority_judge(char a,char b)
{
	if (b == ')')
	{
		if (a == '(')return 2;
		else return 3;
	}
	switch (a)
	{
	case '+':
		if (b == '+' || b=='-')
		{
			return 1;//表示先运算a
		}
		return 0;//'(' 或 '*' 或 '/'
	case '-':
		if (b == '+' || b == '-' )
		{
			return 1;//表示先运算a
		}
		return 0;
	case '*':
		if (b == '(')
			return 0;
		else
			return 1;
	case '/':
		if (b == '(')
			return 0;
		else
			return 1;
	case '(':
		return 0;

	default:
		break;
	}
	return 3;//a==')'
}

int calculate(int a,int b,char op)
{
	int res;
	if (op == '+')
	{
		res = a + b;
	}
	else if (op == '-')
	{
		res = a - b;
	}
	else if (op == '*')
	{
		res = a * b;
	}
	else if (op == '/')
	{
		res = a / b;
	}
	else
	{
		cout << "calculate erro" << endl;
		return 0;
	}
	return res;
}

void line_editor(char input[])//行编辑器(#表示退格，@表示清空，=表示运算)
{
	SqStack_int num;
	SqStack_char op;
	int res;
	char inc;//要计算的式子
	int stat=0;//1表示前面一个输入为num，2表示前面一个为op
	for (int i=0;i<strlen(input);i++)
	{
		inc = input[i];
		if (inc == '=')
		{
			while (!num.finish())
			{
				char cur = op.pop();
				
				num.push(calculate(num.pop(), num.pop(), cur));
				//printf("%c\n", cur);
			}
			res = num.GetTop();
			break;
		}
		if (inc == '#')
		{
			if (stat == 1)
			{
				num.pop();
			}
			else if(stat == 2)
			{
				op.pop();
			}
			else
			{
				cout << "del erro ,already empty" << endl;
			}
			continue;
		}
		else if (inc == '@')
		{
			op.clear();
			num.clear();
			stat = 0;
			continue;
		}
		if (inc >= '0' && inc <= '9')
		{
			num.push((int)inc - '0');
			//printf("%d\n", num.GetTop());
			stat = 1;

		}
		else if(inc =='-'||inc=='+'||inc=='*'||inc=='/'||inc=='('||inc==')')
		{
			if (op.empty())//前面没有符号，一定是直接放入
			{
				op.push(inc);
				continue;
			}
			else
			{
				int pd = priority_judge(op.GetTop(), inc);
				if (pd == 1)
				{
					char cur = op.pop();
					int ans = calculate(num.pop(), num.pop(), cur);
					num.push(ans);
					printf("%d\n",ans);
					if (inc != ')')op.push(inc);
				}
				else if (pd == 0)
				{
					op.push(inc);
				}
				else if (pd == 2)//消除括号
				{
					op.pop();
				}
				else if (pd == 3)
				{
					while (!num.finish())
					{
						char cur = op.pop();
						if (cur == '(')
						{
							break;
						}
						int ans = calculate(num.pop(), num.pop(), cur);
						num.push(ans);
					}
				}
				stat = 2;
			}
		}
		else
		{
			//输入无效错误
			continue;
		}
		
	}
	num.destroy();
	op.destroy();
	printf("答案：%d", res);
}


/*简单的编辑器
int main()
{
	char hhlstr[30];
	gets_s(hhlstr);
	line_editor(hhlstr);
	return 0;
}*/

/*就地逆置（循环）
int main()
{
	CircularStack cs;
	cs.CreateBasicCircle();
	cs.showall();
	cs.TurnAround();
	cs.showall();
	cs.destroy();
	return 0;
}*/
