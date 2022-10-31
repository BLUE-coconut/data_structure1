#pragma once
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int readline(FILE* fp)//每次读一行
{
    char* szTest = (char*)malloc(sizeof(char) * 100);
    int len = 0;

    if (!feof(fp))
    {
        memset(szTest, 0, sizeof(szTest));
        fgets(szTest, sizeof(szTest) - 1, fp); // 包含了换行符
        printf("%s", szTest);
    }
    else
    {
        return 0;
    }
    return 1;
}


//实现方式：动态链表+标记所有行首结点指针（用一个链表存），读入时动态分配，输出后释放
//优点：1、动态分配节省空间；2、链表操作方便；3、存储行首指针定位迅速(没有索引那么方便，但行数在100以内总体效率还是比较高的)

class Editor_String 
{
private:
    typedef char eletype;
    typedef struct LinkNode    //使用链表实现
    {
        eletype data;
        struct LinkNode* next;
        LinkNode() : data(0), next(NULL) {}
        LinkNode(eletype v) : data(v), next(NULL) {}
        LinkNode(eletype v, struct LinkNode* x) : data(v), next(x) {}
    }LN;
    int len = 0;//活区内当前总行数

    //dummyhead 仍然是整个动态链表的头节点
    struct header//存储行首的结点（存储行长度方便输出该行），插入行时也插入一个行首
    {
        int line_len;
        LN* Lhead;
        header* next;
        header() :line_len(0), Lhead(NULL), next(NULL) {};
        header(int l, LN* Lhead) :line_len(l), Lhead(Lhead), next(NULL) {};
        header(int l, LN* Lhead, header* nx) :line_len(l), Lhead(Lhead), next(nx) {};

    };
    header* dummy_of_header = new header();
    header* cur_show = dummy_of_header;//当前展示的页面第一行的行首的前驱
    int cur_id = 0;//当前展示的页面第一行的行号

public:
    void insert_line(int line_id,char in_string[])//是否合法在activate_block中进行判断(插在)
    {
        header *p = dummy_of_header;
        while (line_id--)//找到第line_id行的行首
        {
            p = p->next;
        }

        /*本来是想所有数据练成一条链的，后来想想只要header链着就好，每个head包含一条存储每行的链
        LN* cur = p->Lhead;
        for (int i = 1; i < p->line_len; i++)//找到第line_id行的行尾(行首也存数据)
        {
            cur = cur->next;
        }

        header* hnew = new header();
        for (int i = 0; i < strlen(in_string); i++)
        {
            LN *pnew = new LN(in_string[i]);
            if (i == 0)
            {
                hnew->line_len = strlen(in_string);
                hnew->Lhead = pnew;
            }
            cur->next = pnew;
            cur = cur->next;
        }
        //cur->next = p->next->Lhead;           //要不要接起来呢（思索），先不接了（嗯不接了）
        */

        header* hnew = new header();
        LN* pcur;//建立新行
        if (strlen(in_string) > 0)//假如输入字符串为空则插入失败
        {
            pcur = new LN(in_string[0]);
            hnew->line_len = strlen(in_string);
            hnew->Lhead = pcur;
        }
        else
        {
            printf("insert empty\n");
            return;
        }
        for (int i = 1; i < strlen(in_string); i++)
        {
            LN* pnew = new LN(in_string[i]);
            pcur->next = pnew;
            pcur = pcur->next;
        }

        //增加一个换行符
        LN* pnew = new LN('\n');
        pcur->next = pnew;
        pcur = pcur->next;


        hnew->next = p->next;//插入新行
        p->next = hnew;
        len++;
    }

    void add_line(char in_string[])//at tail
    {
        insert_line(len, in_string);
    }

    header* get_to_line(int line_id)
    {
        header* p = dummy_of_header;
        while (line_id--)
        {
            p = p->next;
        }
        return p;
    }

    bool del_single_line(int id)//删除单行（第id行）
    {
        header* hcur = dummy_of_header;
        for(int i=1;i<id;i++)
        {
            if (!hcur->next)//第id行不存在
            {
                printf("del erro,line-%d does not exist\n",id);
                return false;
            }
            hcur=hcur->next;
        }//找到第id行的前驱hcur
        header* hdel = hcur->next;
        printf("deling line-%d\n",id);
        show_sigle_line(hdel, id);
        hcur->next = hdel->next;

        int l = hdel->line_len;
        LN* pout = hdel->Lhead;
        while (pout)
        {
            LN* pdel = pout;
            pout = pdel->next;
            delete(pdel);
        }
        len--;
        delete(hdel);
        return true;
    }

    void del_lines(int start, int end)//删除多行（第start行~第end-1行）
    {
        for (int i = start; i < end; i++)
        {
            if (del_single_line(start));
            else
            {
                printf("del to the end ,%d lines have been deleted\n",i-start);//已经删到底了
                return;
            }
        }
    }

    void show_all_lines()//输出活区全部
    {
        header* hcur = dummy_of_header->next;
        int id = 1;
        while (hcur)
        {
            int line_len = hcur->line_len;
            LN* pcur=hcur->Lhead;
            printf("%4d ", id++);//输出行号
            for (int i = 1; i <= line_len; i++)
            {
                printf("%c", pcur->data);
                pcur = pcur->next;
            }
            printf("\n");
            hcur = hcur->next;
        }
    }

    void show_sigle_line(header *cur,int id)
    {
        int l = cur->line_len;
        LN *p = cur->Lhead;
        printf("%4d ", id);//输出行号

        for (int i = 1; i <= l; i++)
        {
            printf("%c", p->data);
            p = p->next;
        }
        printf("\n");
    }

    void show_cur_page(int next)//next==1表示显示下一页，next==0表示结束显示(返回初始值)
    {
        if (next)
        {
            int t = 20;
            int id = cur_id;
            while (t-- && cur_show->next)
            {
                show_sigle_line(cur_show->next, ++cur_id);
                cur_show = cur_show->next;
            }
            if (!cur_show->next)printf("Active_block end\n");
        }
        else
        {
            cur_id = 0;
            cur_show = dummy_of_header;
        }
    }

    void show_part(int start,int end)
    {
        while (start--)//得到cur_show为第start行的首结点
        {
            cur_id++;
            cur_show = cur_show->next;
        }
        for (int i=start;i<=end;i++)
        {
            cur_id++;
            cur_show = cur_show->next;
            show_sigle_line(cur_show, cur_id);
        }
        cur_id = 0;
        cur_show = dummy_of_header;
    }

    void out_line(FILE* outfp)//输出
    {
        if (len == 0)
        {
            printf("active block empty\n");
            return;
        }
        header *fline = dummy_of_header->next;
        dummy_of_header->next = fline->next;
        int l = fline->line_len;
        LN* pout = fline->Lhead;
        while (pout)
        {
            LN* pdel = pout;
            fprintf(outfp,"%c", pout->data);
            pout = pdel->next;
            delete(pdel);
        }
        len--;
        delete(fline);
    }

    void all_out(FILE* outfp)
    {
        while (len)
        {
            out_line(outfp);
        }
    }

    int length()
    {
        return len;
    }
};


class active_block
{
private:
    const int Std_len = 81;//标准行块长（在本实现方式中未用到），一个作为行尾结束符
    const int MAX_LINE = 100;//最大行数
    FILE* fp_in;//输入文件
    FILE* fp_out;//输出文件


public:
    active_block(FILE* fpin, FILE* fpout)
    {
        fp_in = fpin;
        fp_out = fpout;
        get_in();
    }
    char szTest[100];//每次从文件读入的字符串
    Editor_String active;//动态链表：存储当前活区所有字符

    bool readline()//每次读一行到szTest字符串中
    {
        if (!feof(fp_in))
        {
            memset(szTest, 0, sizeof(szTest));
            fgets(szTest, sizeof(szTest) - 1, fp_in); // 包含了换行符
            printf("get input line %s", szTest);
        }
        else
        {
            return false;
        }
        return true;
    }
    
    void get_in()//读入
    {
        int t = MAX_LINE - 20;
        while (t--)//（尽可能多地读入，每次不超过MAX_LINE-20）
        {
            if (active.length() >= MAX_LINE)//是否超出活区最大行数
            {
                active.out_line(fp_out);
                printf("超出活区space,输出活区顶部行\n");
            }


            if (readline())//读入到szTest，并判断是否读到底
            {
                active.add_line(szTest);
            }
            else//输入文件读到底了
            {
                printf("input file end\n");
                break;
            }
            
            
        }
        
    }


    void insert_line(int id,char in_string[])//行插入
    {
        if (active.length() == MAX_LINE)
        {
            active.out_line(fp_out);
        }
        active.insert_line(id, in_string);
    }

    void del_line(int id)//行删除
    {
        active.del_single_line(id);
    }

    void del_lines(int start, int end)
    {
        active.del_lines(start, end);
    }

    void show()//活区显示（每次20行）
    {
        int op = 1;
        while (1)
        {
            active.show_cur_page(op);
            if (op == 0)break;
            printf("是否显示下一页（1是 0否）\n");
            scanf_s("%d", &op);
        }
    }

    void shift()//活区切换
    {
        active.all_out(fp_out);//输出当前页
        get_in();//读入新页
    }

    void temp_out()
    {
        active.all_out(fp_out);
    }
};


void help()
{
    FILE* fp;
    fopen_s(&fp, "Editor_helper.txt", "r");
    while (readline(fp));
    fclose(fp);
    printf("\n");
}

void get_op(int *op)
{
    printf("输入操作编号（0-3）:\n");
    scanf_s("%d", op);
}
/*
int main()
{
    //文件打开
    char fdir1[50] = "1.txt";
    char fdir2[50] = "2.txt";
    FILE* fp1;//输入文件
    FILE* fp2;//输出文件

    int errojudge1 = fopen_s(&fp1, fdir1, "r");
    if (errojudge1 != 0)
    {
        perror("failed to open \n");
        return 0;
    }

    int errojudge2 = fopen_s(&fp2, fdir2, "w");
    if (errojudge2 != 0)
    {
        perror("failed to open \n");
        return 0;
    }

    active_block AB(fp1,fp2);

    int op = 1;
    while (1)
    {
        if (op == 1)
        {
            printf("文件编辑系统：\n");
            printf("输入0：退出\n");
            printf("输入1：主页面\n");
            printf("输入2：显示帮助\n");
            printf("输入3：进入编辑状态\n");
            get_op(&op);
        }
        else if (op == 2)
        {
            help();
            get_op(&op);
        }
        else if (op == 0)
        {
            break;
        }
        else if (op == 3)
        {
            printf("editing:\n");
            printf("please input command\n");
            getchar();//去除换行
            char edit;
            scanf_s("%c", &edit);

            if (edit == 'i')//行插入
            {
                int id;
                scanf_s("%d\n",&id);
                char in_string[100];
                gets_s(in_string);
                AB.insert_line(id, in_string);

            }
            else if (edit == 'd')//行删除
            {
                int id;
                scanf_s("%d", &id);

                AB.del_line(id);
            }
            else if (edit == 'n')//切换活区
            {
                AB.shift();
            }
            else if (edit == 'p')//按页显示活区
            {
                AB.show();
            }
            else
            {
                printf("wrong command ,try again\n");
            }
            get_op(&op);
            if (op ==1||op==0)
            {
                AB.temp_out();
                printf("the data in active block has been saved into output file\n");
            }
        }
        else
        {
            printf("op erro,try again\n");
            get_op(&op);
        }
        

    }
    

    fclose(fp1);     //文件关闭
    fclose(fp2);     //文件关闭

    return 0;
}*/