#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "link_list.h"

extern unsigned int malloc_count_g;
extern unsigned int free_count_g;

int link_list_insert(LinkNode **head, SearchNode value)
{
    int val = 0;
    LinkNode *pCurrent = NULL;
    LinkNode *pNext = NULL;
    LinkNode *pTmp = NULL;
    
    val = value.fScore;
    pCurrent = *head;
    
    pTmp = (LinkNode *)malloc(sizeof(LinkNode));
    if (pTmp == NULL){
        printf("ERR: malloc failed! function:%s line:%d\n", __FUNCTION__, __LINE__);
        return -1;
    }else {
        malloc_count_g++;
    }
    memcpy(&pTmp->value, &value, sizeof(SearchNode));
    
    if (pCurrent == NULL){ //if head is NULL
        *head = pTmp;
        pTmp->next = NULL;
        //printf("head is NULL\n");
        return 0;
    }
    if (pCurrent->value.fScore >= val){ //if head is biger than value, then insert value before head
        pTmp->next = pCurrent;
        *head = pTmp;
        return 0;
    }

    pNext = pCurrent->next;
    while (pCurrent != NULL) {
        if (pNext == NULL || pNext->value.fScore >= val){
            pTmp->next = pNext;
            pCurrent->next = pTmp;
            return 0;
        }
        pCurrent = pNext;
        pNext = pNext->next;
    }

    return 0;
}

int link_list_delete(LinkNode **head, SearchNode value)
{
    LinkNode *pCurrent = NULL;
    LinkNode *pNext = NULL;
    
    pCurrent = *head;

    if (pCurrent->value.posX == value.posX && pCurrent->value.posY == value.posY){
        *head = pCurrent->next;
        free(pCurrent);
        free_count_g++;
        return 0;
    }

    pNext = pCurrent->next;
    while (pNext != NULL){
        if (pNext->value.posX == value.posX && pNext->value.posY == value.posY){
            pCurrent->next = pNext->next;
            free(pNext);
            free_count_g++;
            return 0;
        }
        pCurrent = pNext;
        pNext = pNext->next;
    }
    return -1;
}

int link_list_search(LinkNode *head, SearchNode **pValue)
{
    LinkNode *pCurrent = NULL;

    pCurrent = head;
    while (pCurrent != NULL){
        if (pCurrent->value.posX == (*pValue)->posX && pCurrent->value.posY == (*pValue)->posY){
            *pValue = &pCurrent->value;
            return 0; //have found the target
        }
        pCurrent = pCurrent->next;
    }
    return -1; //didn't find the node
}

int link_list_destroy(LinkNode **head)
{
    LinkNode *pCurrent = NULL;

    pCurrent = *head;
    while (*head != NULL){
        *head = pCurrent->next;
        free(pCurrent);
        free_count_g++;
        pCurrent = *head;
    }
    *head = NULL;
    return 0;
}

int link_list_resort(LinkNode **head)
{
    LinkNode *tmpHead = NULL;
    LinkNode *pOld = NULL;
    LinkNode *pOldNext = NULL;
    LinkNode *pNew = NULL;
    LinkNode *pNewNext = NULL;

    pOld = (*head)->next;

    pNew = *head;
    tmpHead = pNew;
    pNew->next = NULL;
    pNewNext = NULL;
    
    while (pOld != NULL){
        pOldNext = pOld->next;
        if (pOld->value.fScore <= pNew->value.fScore){
            pOld->next = pNew;
            pNew = pOld;
            pNewNext = pNew->next;
            tmpHead = pNew;
        }else {
            while (pNewNext!=NULL && pNewNext->value.fScore<pOld->value.fScore){
                pNew = pNewNext;
                pNewNext = pNewNext->next;
            }
            pOld->next = pNewNext;
            pNew->next = pOld;
            pNew = tmpHead;
            pNewNext = pNew->next;
        }
        pOld = pOldNext;
    }
    *head = tmpHead;
}

void print_link_list(LinkNode *head)
{
    LinkNode *pCurrent = NULL;

    pCurrent = head;
    while (pCurrent != NULL){
        printf("(%d,%d)(%d-%d-%d)->", pCurrent->value.posX, pCurrent->value.posY
            , pCurrent->value.fScore, pCurrent->value.gScore, pCurrent->value.hScore);
        pCurrent = pCurrent->next;
    }
    printf("NULL\n");
}
/*
int main()
{
    LinkNode *linkList = NULL;
    SearchNode value = {0};
    SearchNode *pValue = NULL;
    
    value.posX = 0;
    value.posY = 1;
    value.fScore = 7;
    link_list_insert(&linkList, value);
    value.posX = 1;
    value.posY = 2;
    value.fScore = 2;
    link_list_insert(&linkList, value);
    value.posX = 4;
    value.posY = 5;
    value.fScore = 5;
    link_list_insert(&linkList, value);
    value.posX = 4;
    value.posY = 11;
    value.fScore = 9;
    link_list_insert(&linkList, value);

    // print 
    print_link_list(linkList);

    // search 
    value.posX = 1;
    value.posY = 2;
    pValue = &value;
    link_list_search(linkList, &pValue);
    printf("search:(%d,%d)(%d-%d-%d)\n", pValue->posX, pValue->posY
        , pValue->fScore, pValue->gScore, pValue->hScore);
    
    // delete 
    value.posX = 1;
    value.posY = 2;
    value.fScore = 2;
    link_list_delete(&linkList, value);
    value.posX = 4;
    value.posY = 5;
    value.fScore = 5;
    link_list_delete(&linkList, value);

    // print 
    print_link_list(linkList);

    // destroy 
    link_list_destroy(&linkList);

    // print 
    print_link_list(linkList);
    printf("malloc count:%d, free count:%d\n", malloc_count_g, free_count_g);
}*/
