#include <stdio.h>
#include <math.h>

#include "link_list.h"

int map[WIDTH][HEIGHT]{
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
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
}

LinkNode *openSetList = NULL;
LinkNode *closedSetList = NULL;

int get_neighbors(SearchNode *neighbors, SearchNode node)
{
    
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
        if (pCurrent->posX == dest.posX && pCurrent->posY == dest.posY){
            //
        }
        link_list_insert(&closedSetList, *pCurrent);
        get_neighbors(neighbors, *pCurrent);
        link_list_delete(&openSetList, *pCurrent);
        for (i=0; i<NEIGHBORS_NUM; i++){
            pNeighbor = &neighbors[i];
            if (link_list_search(closedSetList, &pNeighbor) == 0){
                continue;
            }
            tentative_g_score = pCurrent->gScore + dis_between(pCurrent, pNeighbor);//
            if (link_list_search(openSetList, &pNeighbor) != 0){
                link_list_insert(&openSetList, *pNeighbor);
                tentative_is_better = true;
            }else if (tentative_g_score < pNeighbor->gScore){
                tentative_is_better = true;
            }else {
                tentative_is_better = false;
            }
            if (tentative_is_better == true){
                pNeighbor->parent = pCurrent;
                pNeighbor->gScore = tentative_g_score;
                pNeighbor->hScore = ESTIMATE_DISTANCE(*pNeighbor, dest);
                pNeighbor->fScore = pNeighbor->gScore + pNeighbor->hScore;
            }
        }
    }
    return -1;
}

int main()
{
    
}
