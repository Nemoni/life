#include <stdio.h>
#include "list.h"
/* function A*(start,goal)
     closedset := the empty set                 //�Ѿ�������Ľڵ㼯��    
     openset := set containing the initial node //��Ҫ������Ľڵ㼯��
     came_from := empty map
     g_score[start] := 0                        //g(n)
     h_score[start] := heuristic_estimate_of_distance(start, goal)    //h(n)
     f_score[start] := h_score[start]            //f(n)=h(n)+g(n)������g(n)=0�����ԡ���
     while openset is not empty                 //����������Ľڵ����ʱ��ִ��
         x := the node in openset having the lowest f_score[] value   //ȡxΪ��������Ľڵ���f(x)��С��
         if x = goal            //��xΪ�յ㣬ִ��
             return reconstruct_path(came_from,goal)   //���ص�x�����·��
         remove x from openset      //��x�ڵ�ӽ�������Ľڵ���ɾ��
         add x to closedset      //��x�ڵ�����Ѿ�������Ľڵ�
         foreach y in neighbor_nodes(x)  //���ڽڵ�x����������ڵ�y��ִ��
             if y in closedset           //��y�ѱ���ֵ������
                 continue
             tentative_g_score := g_score[x] + dist_between(x,y)    //����㵽�ڵ�y�ľ���
 
             if y not in openset          //��y���ǽ�������Ľڵ�
                 add y to openset         //��y���뽫������Ľڵ���
                 tentative_is_better := true     
             elseif tentative_g_score < g_score[y]         //���y�Ĺ�ֵС��y��ʵ�ʾ���
                 tentative_is_better := true         //��ʱ�ж�Ϊ����
             else
                 tentative_is_better := false           //�����ж�Ϊ����
             if tentative_is_better = true            //����ж�Ϊ����
                 came_from[y] := x                  //��y��Ϊx���ӽڵ�
                 g_score[y] := tentative_g_score
                 h_score[y] := heuristic_estimate_of_distance(y, goal)
                 f_score[y] := g_score[y] + h_score[y]
     return failure
 
 function reconstruct_path(came_from,current_node)
     if came_from[current_node] is set
         p = reconstruct_path(came_from,came_from[current_node])
         return (p + current_node)
     else
         return current_node*/
         
struct node 
{
	struct list_head list;
	int num;
};

typedef struct POSTITION
{
    int posX;
    int posY;
}POSTITION_STRU;

typedef struct SEARCHNODE
{
    struct list_head list;
    POSTITION_STRU position;
    int fScore;
    int gScore;    
    int hScore;
    struct SEARCHNODE *parent;
}SEARCHNODE_STRU;

int compare_position(POSTITION_STRU a, POSTITION_STRU b)
{

}

int compare_fscore(SEARCHNODE_STRU m, SEARCHNODE_STRU n)
{
    
}

int double_list_init(SEARCHNODE_STRU head, SEARCHNODE_STRU node)
{
    
}

int double_list_add(SEARCHNODE_STRU head, SEARCHNODE_STRU node)
{
    
}

int double_list_del(SEARCHNODE_STRU head, SEARCHNODE_STRU node)
{
    
}

int double_list_search(SEARCHNODE_STRU head, SEARCHNODE_STRU node)
{
    
}



int main() 
{
	int i;                     //��ʱ����
	struct node *tem;
	struct list_head *pos, *n;

	struct node mylist;       //����
	INIT_LIST_HEAD(&mylist);  //��̬�����ʼ��

	//����0~9��10��Ԫ��
	for (i = 0; i < 10; i++)
	{
		tem = (struct node*) malloc(sizeof(struct node));
		tem->num = i;
		list_add(&(tem->list), &(mylist.list));
	}

	//��ӡ����
	list_for_each(pos, &mylist.list)
	{
		tem = list_entry(pos, struct node, list);
		printf("%d ", tem->num);
	}
	printf("\n");
	
	//ɾ������ֵΪ5�Ľڵ㣬ʹ��safe�汾����
	list_for_each_safe(pos, n, &mylist.list)
	{
		tem = list_entry(pos, struct node, list);
		if (tem->num == 5)
		{
			list_del_init(pos);
			free(tem);
		}
	}

	//��ӡ����
	list_for_each(pos, &mylist.list)
	{
		tem = list_entry(pos, struct node, list);
		printf("%d ", tem->num);
	}
	printf("\n");

	//�ͷ�����Ԫ��
	list_for_each_safe(pos, n, &mylist.list)
	{
		tem = list_entry(pos, struct node, list);
		list_del_init(pos);
		free(tem);
	}

	return 0;
}

