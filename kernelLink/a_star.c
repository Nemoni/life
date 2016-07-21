#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "list.h"
#include "a_star.h"

int map[HEIGHT][WIDTH] = {
    {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,0,0,1,1,1,1,0,0,0},
    {0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0}
};

/*****************************************************************************
 * Function      : create_node
 * Description   : create a search node with the given paraments
 * Input         : POSTITION_STRU position  
                int fScore               
                int gScore               
                int hScore               
 * Output        : None
 * Return        : SEARCHNODE_STRU
 * Others        : 
 * Record
 * 1.Date        : 20160720
 *   Author      : Nemo Ni
 *   Modification: Created function

*****************************************************************************/
SEARCHNODE_STRU *create_node(POSTITION_STRU position, int fScore, int gScore, int hScore)
{
    SEARCHNODE_STRU *pNode = NULL;
    pNode = (SEARCHNODE_STRU *)malloc(sizeof(SEARCHNODE_STRU));
    if (pNode == NULL){
        printf("ERR: malloc err! function:%s\n", __FUNCTION__);
    }
    memcpy(&pNode->position, &position, sizeof(POSTITION_STRU));
    pNode->gScore = gScore;
    pNode->hScore = hScore;
    pNode->fScore = fScore;
    pNode->parent = NULL;
    memset(&pNode->list, 0, sizeof(pNode->list));

    return pNode;
}

/*****************************************************************************
 * Function      : compare_position
 * Description   : compare if the given positions are the same, if
                   so return 0, otherwise return -1
 * Input         : POSTITION_STRU a  
                POSTITION_STRU b  
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20160720
 *   Author      : Nemo Ni
 *   Modification: Created function

*****************************************************************************/
int compare_position(POSTITION_STRU a, POSTITION_STRU b)
{
    if (a.posX == b.posX && a.posY == b.posY){
        return 0;
    }
    return -1;
}

/*****************************************************************************
 * Function      : compare_fscore
 * Description   : compare if the fcore in these two nodes are the same,
                   if m > n then return 1,if m= n return 0, otherwise return
                   -1
 * Input         : SEARCHNODE_STRU *m  
                SEARCHNODE_STRU *n  
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20160720
 *   Author      : Nemo Ni
 *   Modification: Created function

*****************************************************************************/
int compare_fscore(SEARCHNODE_STRU *m, SEARCHNODE_STRU *n)
{
    if (m->fScore == n->fScore){
        return 0;
    }else if (m->fScore > n->fScore){
        return 1;
    }
    return -1;
}
/*****************************************************************************
 * Function      : double_list_init
 * Description   : init customer list and make the pointer point to itself
 * Input         : SEARCHNODE_STRU *head  
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20160720
 *   Author      : Nemo Ni
 *   Modification: Created function

*****************************************************************************/
void double_list_init(SEARCHNODE_STRU *head)
{    
    memset(&head->position, 0, sizeof(POSTITION_STRU));
    head->gScore = 0;
    head->hScore = 0;
    head->fScore = 0;
    head->parent = NULL;
    INIT_LIST_HEAD(&head->list);
}
/*****************************************************************************
 * Function      : double_list_add
 * Description   : add a given node to the list, not create it
 * Input         : SEARCHNODE_STRU *head  
                SEARCHNODE_STRU *node  
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20160720
 *   Author      : Nemo Ni
 *   Modification: Created function

*****************************************************************************/
void double_list_add(SEARCHNODE_STRU *head, SEARCHNODE_STRU *node)
{
    list_add(&(node->list), &(head->list));
}
/*****************************************************************************
 * Function      : double_list_del
 * Description   : delete a node from list but not free it
 * Input         : SEARCHNODE_STRU *node  
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20160721
 *   Author      : Nemo Ni
 *   Modification: Created function

*****************************************************************************/
void double_list_del(SEARCHNODE_STRU *node)
{
    list_del_init(&(node->list));
}
/*****************************************************************************
 * Function      : double_list_search
 * Description   : find a node by it's position in the list and return the node's pointer,
                   if didn't find return NULL
 * Input         : SEARCHNODE_STRU *head  
                SEARCHNODE_STRU *node  
 * Output        : None
 * Return        : SEARCHNODE_STRU
 * Others        : 
 * Record
 * 1.Date        : 20160721
 *   Author      : Nemo Ni
 *   Modification: Created function

*****************************************************************************/
SEARCHNODE_STRU *double_list_search(SEARCHNODE_STRU *head, SEARCHNODE_STRU *node)
{
	struct list_head *pos;
    SEARCHNODE_STRU *pNodeTmp = NULL;
	list_for_each(pos, &head->list)
	{
		pNodeTmp = list_entry(pos, SEARCHNODE_STRU, list);
		if (compare_position(node->position, pNodeTmp->position) == 0){
            return pNodeTmp;
		}
	}
    return NULL;
}
/*****************************************************************************
 * Function      : get_min_fscore_node
 * Description   : find the minimum fscore node in the list and return it's
                   pointer
 * Input         : SEARCHNODE_STRU *head  
 * Output        : None
 * Return        : SEARCHNODE_STRU
 * Others        : 
 * Record
 * 1.Date        : 20160721
 *   Author      : Nemo Ni
 *   Modification: Created function

*****************************************************************************/
SEARCHNODE_STRU *get_min_fscore_node(SEARCHNODE_STRU *head)
{
	struct list_head *pos;
    SEARCHNODE_STRU *pNodeTmp = NULL;
    SEARCHNODE_STRU *pMinNode = NULL;

    pMinNode = list_entry(head->list.next, SEARCHNODE_STRU, list);
	list_for_each(pos, &head->list)
	{
		pNodeTmp = list_entry(pos, SEARCHNODE_STRU, list);
		if (compare_fscore(pNodeTmp, pMinNode) < 0){
            pMinNode = pNodeTmp;
		}
	}
    return pMinNode;
}
/*****************************************************************************
 * Function      : dist_between
 * Description   : the actual distance between node A and node B
 * Input         : SEARCHNODE_STRU *nodeA  
                SEARCHNODE_STRU *nodeB  
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20160721
 *   Author      : Nemo Ni
 *   Modification: Created function

*****************************************************************************/
int dist_between(SEARCHNODE_STRU *nodeA, SEARCHNODE_STRU *nodeB)
{
    return ESTIMATE_DISTANCE(nodeA->position, nodeB->position);
}
/*****************************************************************************
 * Function      : within_map
 * Description   : check if  the width and height of the node's position is correct
 * Input         : POSTITION_STRU node  
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20160721
 *   Author      : Nemo Ni
 *   Modification: Created function

*****************************************************************************/
bool within_map(POSTITION_STRU node)
{
	if (node.posX >= 0 && node.posX < WIDTH && node.posY >= 0 && node.posY < HEIGHT){
		return true;
	}else {
		return false;
	}
}
/*****************************************************************************
 * Function      : getNeighbors
 * Description   : get the neighbors of the given node and create it if
                   it is correct
 * Input         : SEARCHNODE_STRU *head          
                SEARCHNODE_STRU *pNodeCurrent  
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20160721
 *   Author      : Nemo Ni
 *   Modification: Created function

*****************************************************************************/
void getNeighbors(SEARCHNODE_STRU *head, SEARCHNODE_STRU *pNodeCurrent)
{
	int i = -1, j = -1;
    POSTITION_STRU tmp;
    SEARCHNODE_STRU *pNode = NULL;
    
    for (j=-1; j<=1; j=j+1){
		for (i=-1; i<=1; i=i+1) {
			if (i == 0 && j == 0){
				continue;
			}
			memset(&tmp, 0, sizeof(POSTITION_STRU));
			tmp.posX = pNodeCurrent->position.posX + i;
			tmp.posY = pNodeCurrent->position.posY + j;
			if (within_map(tmp) && map[tmp.posY][tmp.posX]!=1){
                pNode = create_node(tmp, 0, 0, 0);
                double_list_add(head, pNode);
			}
		}
    }
}
/*****************************************************************************
 * Function      : on_the_path
 * Description   : check if the node is on the path that find out finally
 * Input         : SEARCHNODE_STRU *pStart  
                SEARCHNODE_STRU *pDest   
                POSTITION_STRU node      
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20160721
 *   Author      : Nemo Ni
 *   Modification: Created function

*****************************************************************************/
int on_the_path(SEARCHNODE_STRU *pStart, SEARCHNODE_STRU *pDest, POSTITION_STRU node)
{
    SEARCHNODE_STRU *pCurrent = pDest;
    
    if (compare_position(node, pStart->position) == 0){
        return 0;
    }
    while (compare_position(pStart->position, pCurrent->position) != 0){
        if (compare_position(node, pCurrent->position) == 0){
            return 0;
        }
        pCurrent = pCurrent->parent;
    }
	return -1;
}

void print_map()
{
    int i = 0, j = 0;
    printf(" \\");
    
    for (i=0; i< WIDTH; i++){
        printf("%2d", i);
    }
    printf("\n");
    for (j=0; j< HEIGHT; j++){
        printf("%2d", j);
        for (i=0; i< WIDTH; i++){
            if (map[j][i] == 1){
                printf(" &");
            }else {
                printf(" -");
            }
        }
        printf("\n");
    }
}

void print_path(SEARCHNODE_STRU *pStart, SEARCHNODE_STRU *pDest)
{
    POSTITION_STRU node;
    int i = 0, j = 0;

    printf(" \\");
    for (i=0; i< WIDTH; i++){
        printf("%2d", i);
    }
    printf("\n");
    for (j=0; j< HEIGHT; j++){
        printf("%2d", j);
        for (i=0; i< WIDTH; i++){
            node.posX = i;
            node.posY = j;
            if (compare_position(pStart->position, node) == 0){
                printf(" #");
            }else if (compare_position(pDest->position, node) == 0){
                printf(" @");
            }else if (on_the_path(pStart, pDest, node) == 0){
                printf(" +");
            }else{
                if (map[j][i] == 1){
                    printf(" &");
                }else {
                    printf(" -");
                }
            }
        }
        printf("\n");
    }
    
//	    SEARCHNODE_STRU *pCurrent = pDest;
//	    while (compare_position(pStart->position, pCurrent->position) != 0){
//	          printf("(%d,%d)%d,%d,%d->", pCurrent->position.posX,pCurrent->position.posY
//	              ,pCurrent->fScore,pCurrent->gScore,pCurrent->hScore);
//	        pCurrent = pCurrent->parent;
//	    }

}
/*****************************************************************************
 * Function      : a_star_func
 * Description   : find a path from start to destination with the a star
                   algorithm
 * Input         : POSTITION_STRU start  
                POSTITION_STRU dest   
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20160720
 *   Author      : Nemo Ni
 *   Modification: Created function

*****************************************************************************/
int a_star_func(POSTITION_STRU start, POSTITION_STRU dest)
{
    SEARCHNODE_STRU openList, closeList, neighborList;
    
    SEARCHNODE_STRU *pOpenList = &openList;
    SEARCHNODE_STRU *pCloseList = &closeList;
    SEARCHNODE_STRU *pNeighborList = &neighborList;
    
    SEARCHNODE_STRU *pStart = NULL;
    int GScoreStart, HScoreStart, FScoreStart;
    int tentativeGScore;

    SEARCHNODE_STRU *pNodeCurrent = NULL, *pNodeNeighbor = NULL, *pNodeSearch = NULL;
    
    double_list_init(pOpenList);
    double_list_init(pCloseList);
    double_list_init(pNeighborList);
    GScoreStart = 0;
    HScoreStart = ESTIMATE_DISTANCE(start, dest);
    FScoreStart = GScoreStart + HScoreStart;
    
    pStart = create_node(start, FScoreStart, GScoreStart, HScoreStart);
    double_list_add(pOpenList, pStart);
    /* foreach the open set list */
    while (pOpenList->list.next != &pOpenList->list){
        pNodeCurrent = get_min_fscore_node(pOpenList);
        if (compare_position(pNodeCurrent->position, dest) == 0){
            print_path(pStart, pNodeCurrent); //arrive at the destination
            return 0;
        }
        double_list_del(pNodeCurrent);
        double_list_add(pCloseList, pNodeCurrent);
        getNeighbors(pNeighborList, pNodeCurrent);
        /* foreach the current node's neighbor nodes */
        while (pNeighborList->list.next != &pNeighborList->list){
    		pNodeNeighbor = list_entry(pNeighborList->list.next, SEARCHNODE_STRU, list);
            /* if this neighbor node has been calculated then skip */
            if ((pNodeSearch = double_list_search(pCloseList, pNodeNeighbor)) != NULL){
                double_list_del(pNodeNeighbor);
                free(pNodeNeighbor);
                continue;
            }
            /* calculate the distance between this neighbor node and start node */
            tentativeGScore = pNodeCurrent->gScore + dist_between(pNodeNeighbor, pNodeCurrent);
            /* if this neighbor node is in open set list */
            if ((pNodeSearch = double_list_search(pOpenList, pNodeNeighbor)) != NULL){
                double_list_del(pNodeNeighbor);
                free(pNodeNeighbor);
                pNodeNeighbor = pNodeSearch;
                /* if node is in open set list and the cost is more than before then skip */
                if (tentativeGScore >= pNodeNeighbor->gScore){
                    continue;
                }
            /* if the node is not in open set list then add it */
            }else{
                double_list_del(pNodeNeighbor);
                double_list_add(pOpenList, pNodeNeighbor);
            }
            pNodeNeighbor->parent = pNodeCurrent;
            pNodeNeighbor->gScore = tentativeGScore;
            pNodeNeighbor->hScore = ESTIMATE_DISTANCE(pNodeNeighbor->position, dest);
            pNodeNeighbor->fScore = pNodeNeighbor->gScore + pNodeNeighbor->hScore;
    	}
    }
    return -1;
}

int main()
{
    POSTITION_STRU startNode, destNode;
    
	startNode.posX = -1;
	startNode.posY = -1;
	destNode.posX = -1;
	destNode.posY = -1;
    
    //init_map();
    print_map();
    while (scanf("%d %d %d %d", &startNode.posX, &startNode.posY, &destNode.posX, &destNode.posY) != EOF)
    {
        if (within_map(startNode) && within_map(destNode)){
            if (a_star_func(startNode, destNode) < 0){
        		printf("no path!\n");
            }
        }else{
            printf("error input!\n");
        }
    }
    return 0;
}

