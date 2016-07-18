#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#include "link_list.h"

int map[HEIGHT][WIDTH] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

LinkNode *openSetList = NULL;
LinkNode *closedSetList = NULL;

bool within_map(SearchNode node)
{
	if (node.posX >= 0 && node.posX < WIDTH && node.posY >= 0 && node.posY < HEIGHT){
		return true;
	}else {
		return false;
	}
}

int get_neighbors(SearchNode neighbors[], SearchNode node)
{
	SearchNode tmp;
	SearchNode (*p)[NEIGHBORS_NUM] = NULL;
	int i = -1, j = -1;
	int n = 0;
	
    for (j=-1; j<=1; j=j+1){
		for (i=-1; i<=1; i=i+1) {
			//printf("i:%d,j:%d\n", i, j);
			if (i == 0 && j == 0){
				continue;
			}
			memset(&tmp, 0, sizeof(SearchNode));
			tmp.posX = node.posX + i;
			tmp.posY = node.posY + j;
			//printf("tmp.posX:%d,tmp.posY:%d\n", tmp.posX, tmp.posY);
			if (within_map(tmp) && map[tmp.posY][tmp.posX]!=1){
				tmp.available = 1;
				//printf("%p, n:%d\n", neighbors, n);
				memcpy(neighbors+n, &tmp, sizeof(SearchNode));
				n++;
			}
		}
    }
}

int dis_between(SearchNode *src, SearchNode *dst)
{
	return ESTIMATE_DISTANCE((*src), (*dst));
}

int on_the_path(SearchNode start, SearchNode dest, SearchNode node)
{
	SearchNode *pCurrent = &dest;

	while (pCurrent != NULL){
		if (node.posX == pCurrent->posX && node.posY == pCurrent->posY){
			return 1;
		}
		pCurrent = pCurrent->parent;
	}
	return 0;
}
int get_the_path(SearchNode start, SearchNode *pCurrent)
{
	SearchNode node;

	int i = 0, j = 0;
	printf(" \\");
	for (i=0; i<= WIDTH; i++){
		printf("%2d", i);
	}
	printf("\n");
	for (j=0; j<= HEIGHT; j++){
		printf("%2d", j);
		for (i=0; i<= WIDTH; i++){
			node.posX = i;
			node.posY = j;
			if (on_the_path(start, *pCurrent, node) == 1){
				printf(" +");
			}else{
				printf("%2d", map[j][i]);
			}
		}
		printf("\n");
	}
	return 0;
}

int a_star_func(SearchNode start, SearchNode dest)
{
    SearchNode *pCurrent;
    SearchNode *pNeighbor;
    SearchNode neighbors[NEIGHBORS_NUM];
    int i = 0;
    int tentative_g_score = 0;
    bool tentative_is_better = false;
	
    openSetList = NULL;
    closedSetList = NULL;
    start.gScore = 0;
    start.hScore = ESTIMATE_DISTANCE(start, dest);
    start.fScore = start.hScore;
    link_list_insert(&openSetList, start);
    while (openSetList != NULL){
        pCurrent = &openSetList->value; //get the first node who has smaller fscore
        //printf("current:(%d,%d)\n", pCurrent->posX, pCurrent->posY);
        if (pCurrent->posX == dest.posX && pCurrent->posY == dest.posY){
            //
            get_the_path(start, pCurrent);
			return 0;
        }
        link_list_insert(&closedSetList, *pCurrent);
		link_list_search(closedSetList, &pCurrent);
		memset(neighbors, 0, sizeof(SearchNode)*NEIGHBORS_NUM);
        get_neighbors(neighbors, *pCurrent);
        link_list_delete(&openSetList, *pCurrent);
        for (i=0; i<NEIGHBORS_NUM; i++){
            pNeighbor = &neighbors[i];
			if (pNeighbor->available != 1){
				break;
			}
            if (link_list_search(closedSetList, &pNeighbor) == 0){
                continue;
            }
            tentative_g_score = pCurrent->gScore + dis_between(pCurrent, pNeighbor);
            if (link_list_search(openSetList, &pNeighbor) != 0){
                link_list_insert(&openSetList, *pNeighbor);
				link_list_search(openSetList, &pNeighbor);
                tentative_is_better = true;
            }else if (tentative_g_score < pNeighbor->gScore){
                tentative_is_better = true;
            }else {
                tentative_is_better = false;
            }
            if (tentative_is_better == true){
                pNeighbor->parent = pCurrent;
                pNeighbor->gScore = tentative_g_score;
                pNeighbor->hScore = ESTIMATE_DISTANCE((*pNeighbor), dest);
                pNeighbor->fScore = pNeighbor->gScore + pNeighbor->hScore;
            }
        }
    }
    return -1;
}

int main()
{
	SearchNode start, dest;
	
	memset(&start, 0, sizeof(SearchNode));
	memset(&dest, 0, sizeof(SearchNode));
	start.posX = 0;
	start.posY = 0;
	dest.posX = 15;
	dest.posY = 15;
    if (a_star_func(start, dest) < 0){
		printf("no path\n");
    }
}
