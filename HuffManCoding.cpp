#pragma once
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<queue>
#include<string>
using namespace std;
const int MAX_dict = 100;
const int MAX_len = 50;
class HuffTree
{
private:
	typedef char eletype;
	typedef struct Huff_Tree_Node
	{
		eletype data;
		int weight ;
		Huff_Tree_Node* lc;
		Huff_Tree_Node* rc;
		int id = 0;
		int layer = 0;
		char code = '0';
		Huff_Tree_Node() :data(0), weight(0), lc(NULL), rc(NULL) {};
		Huff_Tree_Node(eletype d,int w) :data(d), weight(w), lc(NULL), rc(NULL) {};
		Huff_Tree_Node(eletype d,int w ,Huff_Tree_Node* l, Huff_Tree_Node* r) :data(d), weight(w), lc(l), rc(r) {};

	}HTN;
	struct Tree
	{
		int depth=0;
		int width=0;
		int num_node=0;
		int max_id=0;
		Huff_Tree_Node* root;
	}My_tree;

	struct input_dict {
		Huff_Tree_Node* cur_node;
		int weight;
		int tag;//1表示为叶结点
		input_dict() :cur_node(new Huff_Tree_Node()),weight(0),tag(0){};
		input_dict(Huff_Tree_Node* cn,int weight,int tag) :cur_node(cn), weight(weight),tag(tag) {};
		friend bool operator <(const input_dict& a, const input_dict& b) {
			return a.weight > b.weight;
		}

	};


	priority_queue <input_dict,vector<input_dict>,less<input_dict>> Dict;
	int N;
	void init()
	{
		printf("请输入字符集大小n:\n");
		cin >> N;
		My_tree.num_node = N;
		for (int i = 1; i <= N; i++)
		{
			printf("请输入第%d个 字符-权值 对（以空格分隔）:\n",i);
			int w;
			eletype x;
			cin >> x >> w;
			Huff_Tree_Node* new_node = new Huff_Tree_Node(x,w);

			input_dict *pnew = new input_dict(new_node, w,1);
			Dict.push(*pnew);
		}

	}
	void create()
	{
		while (!Dict.empty())
		{
			if (Dict.empty())
			{
				printf("create erro. Dict empty.\n");
				return;
			}
			input_dict one = Dict.top();
			Dict.pop();

			if (Dict.empty())
			{
				My_tree.root = one.cur_node;
				My_tree.root->layer = 1;
				My_tree.root->id = 1;
				My_tree.root->code = '2';//与后面show的机制有关
				break;
			}

			input_dict two = Dict.top();
			Dict.pop();

			Huff_Tree_Node* new_node = new Huff_Tree_Node(' ',one.weight+two.weight, one.cur_node,two.cur_node);
			//root = new_node;

			input_dict* combine = new input_dict(new_node, one.weight + two.weight,0);
			Dict.push(*combine);
		}
		printf("create successfully\n");

	}
	void build_Tree()//统计width、depth、num_node、各node所在layer、id、以及各结点code（0/1）
	{
		queue<Huff_Tree_Node*>temp;
		temp.push(My_tree.root);
		while (!temp.empty())
		{
			Huff_Tree_Node* cur = temp.front();
			temp.pop();
			if (cur->lc)
			{
				cur->lc->id = cur->id * 2 - 1;
				cur->lc->layer = cur->layer + 1;
				cur->lc->code = '1';
				My_tree.depth = max(My_tree.depth, cur->lc->layer);
				My_tree.width = max(My_tree.width, cur->lc->id);
				My_tree.max_id = max(My_tree.max_id, (int)pow(2, cur->lc->layer - 1));
				printf("%d %c %d\n", cur->lc->layer,cur->lc->data,cur->lc->weight);
				temp.push(cur->lc);
			}
			if (cur->rc)
			{
				cur->rc->id = cur->id * 2;
				cur->rc->layer = cur->layer + 1;
				cur->rc->code = '0';
				My_tree.depth = max(My_tree.depth, cur->rc->layer);
				My_tree.width = max(My_tree.width, cur->rc->id);
				My_tree.max_id = max(My_tree.max_id, (int)pow(2, cur->rc->layer - 1));
				printf("%d %c %d\n", cur->rc->layer, cur->rc->data, cur->rc->weight);
				temp.push(cur->rc);
			}
		}
	}

	struct huff_dict {
		char *code;
		eletype data;
	}hdict[MAX_dict];//从idex=0开始
	int tot=0;


public:
	HuffTree()
	{
		init();
		create();
		build_Tree();
		show();
		char code[MAX_len] = "";
		//into_dict(code,My_tree.root);
	}
	void show()
	{
		int cur_layer = 1;
		int cur_pos = 1;
		queue<pair < Huff_Tree_Node*, int >>temp;
		temp.push(make_pair(My_tree.root, My_tree.max_id-1));//root结点设为code=1，故这里tap_fa*2使得计算的pos为tap_fa

		while (!temp.empty())
		{
			Huff_Tree_Node* cur = temp.front().first;
			int pos = temp.front().second;
			int tap = (temp.front().second+1)/2;
			temp.pop();
			if (cur->layer != cur_layer)
			{
				printf("\n");
				cur_layer = cur->layer;
				cur_pos = 1;
			}
			if (cur->code == '1')//左子树
			{
				pos -= tap;
			}
			else if(cur->code == '0')//右子树
			{
				pos += tap;
			}
			while (cur_pos++ < pos)
			{
				printf("  ");
			}
			printf("%2d", cur->weight);
			if (cur->lc)
			{
				temp.push(make_pair(cur->lc, pos));
			}
			if (cur->rc)
			{
				temp.push(make_pair(cur->rc, pos));
			}
		}

	}

	void into_dict(queue<char>code, Huff_Tree_Node* fa)
	{
		if (!fa->lc && !fa->rc)
		{
			char cur_code[MAX_len];//从idex=0开始
			int i = 0;
			while (!code.empty())
			{
				cur_code[i] = code.front();
				code.pop();
			}
			hdict[tot].code = cur_code;
			hdict[tot++].data = fa->data;
			printf("%d = %c -- %s\n", tot, hdict[tot - 1].data, hdict[tot - 1].code);
		}
		else
		{
			if (fa->lc)
			{
				code.push(fa->lc->code);
				
			}
			if (fa->rc)
			{
				code.push(fa->rc->code);
			}
		}
	}
	
	
};


/*
int main()
{
	HuffTree huffT;
	
	return 0;
}*/


